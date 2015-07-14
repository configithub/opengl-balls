#include "tile.h"
#include "entity.h"
#include <iostream>
#include <base64.h>

// component factories
ComponentFactory<Position> tposition_factory;
ComponentFactory<Rectangle> tshape_factory;
ComponentFactory<AABB> tmask_factory;


void Tile::remove() {
  flags = VOID;
  if(position != NULL) {
    tposition_factory.remove(position);
    position = NULL;
  }
  if(shape != NULL) {
    tshape_factory.remove(shape);
    shape = NULL;
  }
  if(mask != NULL) {
    tmask_factory.remove(mask);
    mask = NULL;
  }
}


void Map::render(const Entity& camera) {
  for(std::vector<Tile>::iterator itt = tiles.begin(); 
    itt != tiles.end(); ++itt) { 
    render_tile(*itt, camera);
  }  
}


void Area::render(const Entity& camera) {
  // TODO: only render what is visible
  for(std::vector<Map>::iterator ittm = tilemaps.begin(); 
    ittm != tilemaps.end(); ++ittm) { 
    ittm->render(camera);
  }  
}


Area::Area(int w, int h) {
  width = w; height = h;
  printf("creating area of size: %d, %d x %d\n", width*height, width, height);
  tilemaps.reserve(width*height);
  default_solid_tile.flags = SOLID;
  default_void_tile.flags = VOID;
}


Area::Area() {
  default_solid_tile.flags = SOLID;
  default_void_tile.flags = VOID;
}


const Tile& Area::get_tile(int tx, int ty) const {
  if(tilemaps.empty()) { return default_void_tile; }
  // find the tilemap
  int tm_x = tx / screen_width;
  int tm_y = ty / screen_height;
  if(tm_y*width + tm_x >= width*height) {
    // position is out of area
    return default_solid_tile;
    printf("fall back on default solid tile\n");
  }

  const Map& tm = tilemaps[tm_y*width + tm_x];
  // find the tile in this tilemap
  return tm.tiles[ty*screen_width+tx];
}


const Tile& Area::get_tile(const Position& pos) const {
  if(tilemaps.empty()) { return default_solid_tile; }
  // find the tilemap
  int tm_x = pos.x / WWIDTH;
  int tm_y = pos.y / WHEIGHT;
  const Map& tm = tilemaps[tm_y*width + tm_x];
  // find the tile in this tilemap
  return tm.tiles[((pos.y%WHEIGHT)/tile_size)*screen_width
                          +((pos.x%WWIDTH)/tile_size) ];
}


bool Area::valid_map_position(int x, int y, Entity& entity) const {
  // assert mask is not null ?
  int tile_top_left_X = (x - entity.mask->w / 2) / tile_size;
  int tile_top_left_Y = (y - entity.mask->h / 2) / tile_size;
  tile_top_left_X = tile_top_left_X < 0 ? 0 : tile_top_left_X;
  tile_top_left_Y = tile_top_left_Y < 0 ? 0 : tile_top_left_Y;
  int tile_bottom_right_X = (x + entity.mask->w / 2) / tile_size;
  int tile_bottom_right_Y = (y + entity.mask->h / 2) / tile_size;
  for(int j = tile_top_left_Y; j <= tile_bottom_right_Y; j++) {
    for(int i = tile_top_left_X; i <= tile_bottom_right_X; i++) {
      if(get_tile(i, j).flags == SOLID) { return false; }
    }
  }
  return true;
}

void Area::load_from_tmx(const char* tmx_filename) {
  // load tilemaps 
  TMX::Parser tmx;
  tmx.load(tmx_filename);
  printf("loading tmx file %s, number of tilesets %d\n", tmx_filename, 
    tmx.tilesetList.size());

  // set the area size, warning : the width and height must be multiples
  //  of screen_width and screen_height respectively
  //  which are the width and height of one screen in tiles
  width = tmx.mapInfo.width / screen_width;
  height = tmx.mapInfo.height / screen_height;
  tilemaps.reserve(width*height);
  printf("loading area of size %d x %d\n", width, height);
  for(int k = 0; k < width*height; ++k) {
    Map tm; tm.tiles.reserve(height*width);
    tilemaps.push_back(tm);
  }

  for( std::map<std::string, TMX::Parser::TileLayer>::iterator it = 
        tmx.tileLayer.begin(); it != tmx.tileLayer.end(); ++it ) {
    // decode (base64) and decompress (zlib) raw tile layer data
    std::string& raw_tlayer = tmx.tileLayer[it->first].data.contents;
    raw_tlayer = trim(raw_tlayer);
    std::string decoded = base64_decode(raw_tlayer);
    std::string tile_layer = decompress_string(decoded);
    std::vector<int> tile_ids;
    // look for tile ids
    int idx = 0;
    for(std::string::iterator it = tile_layer.begin(); 
      it != tile_layer.end(); ++it) {
      if(idx%4 == 0) {
        tile_ids.push_back( (int)(*it) );
      } ++idx;
    }
    // build the maps composing the area from tile ids
    idx = 0;
    int half_tile = tile_size / 2;
    for(std::vector<int>::iterator itTileId = tile_ids.begin(); 
      itTileId != tile_ids.end(); ++itTileId) { 
      // pick the correct map (screen sized) 
      int tm_x = (idx / screen_width) % width;
      int tm_y = idx / (screen_width * screen_height * width);
      int k = tm_y * width + tm_x;
      Map& tm = tilemaps[k];
      // calculate tile coordinates 
      int i = idx % screen_width;
      int j = idx / (screen_width * screen_height) % width;
      Tile tile;  
      // set all tile params
      tile.flags = *itTileId != 0 ? SOLID : VOID;
      tile.position = tposition_factory.create();
      tile.position->x = ((k%width)*screen_width+i)*tile_size+half_tile;
      tile.position->y = ((k/width)*screen_height+j)*tile_size+half_tile;
      if(tile.flags == SOLID) { 
        tile.shape = tshape_factory.create();       
        tile.mask = tmask_factory.create();       
        tile.shape->w = tile_size;
        tile.shape->h = tile_size;
        tile.mask->w = tile_size;
        tile.mask->h = tile_size;
      }
      tm.tiles.push_back(tile);
      ++idx;
    }  
  }

  // load tilesets
  for( int i = 0; i < tmx.tilesetList.size(); i++ ) {
    TSX::Parser tileset;
    tilesets.push_back(tileset);
    TSX::Parser& tsx = tilesets.back();
    //tsx.load( tmx.tilesetList[i].source.c_str() );
    tsx.load("data/tileset/simple.tsx");
  }
}


/*
void Area::load_from_tmx(const char* tmx_filename) {
  TMX::Parser tmx;
  tmx.load(tmx_filename);
  printf("loading tmx file %s, number of tilesets %d\n", tmx_filename, 
    tmx.tilesetList.size());

  
  for( int i = 0; i < tmx.tilesetList.size(); i++ ) {
    std::cout << "Tileset[ First GID: " << tmx.tilesetList[i].firstGID << " Source: " << tmx.tilesetList[i].source << " ]" << std::endl;
    //////////////////////
    //TSXParse starts here
    //////////////////////
    TSX::Parser tileset;
    tilesets.push_back(tileset);
    TSX::Parser& tsx = tilesets.back();
    //tsx.load( tmx.tilesetList[i].source.c_str() );
    tsx.load("data/tileset/simple.tsx");

    std::cout << "Name: " << tsx.tileset.name << std::endl;
    std::cout << "Tile Width: " << tsx.tileset.tileWidth << std::endl;
    std::cout << "Tile Height: " << tsx.tileset.tileHeight << std::endl;
    std::cout << "Margin: " << tsx.tileset.margin << std::endl;
    std::cout << "Spacing: " << tsx.tileset.spacing << std::endl;
    std::cout << "Tileset Properties:" << std::endl;

    std::map<std::string,std::string>::iterator iter = tsx.tileset.property.begin();
    std::map<std::string,std::string>::iterator end_iter = tsx.tileset.property.end();

    for(; iter != end_iter; ++iter) {
      std::cout << "->" << iter->first << " : " << iter->second << std::endl;
    }

    std::cout << "Image Path: " << tsx.tileset.image.source << std::endl;
    std::cout << "Image Width: " << tsx.tileset.image.width << std::endl;
    std::cout << "Image Height: " << tsx.tileset.image.height << std::endl;

    for(int i = 0; i < tsx.terrainList.size(); ++i) {
      std::cout << "Terrain: " << tsx.terrainList[i].name << " - " << tsx.terrainList[i].tile << std::endl;

      std::map<std::string,std::string>::iterator iter = tsx.terrainList[i].property.begin();
      std::map<std::string,std::string>::iterator end_iter = tsx.terrainList[i].property.end();

      for(; iter != end_iter; ++iter) {
        std::cout << "->" << iter->first << " : " << iter->second << std::endl;
      }
    }

    for(int i = 0; i < tsx.tileList.size(); ++i) {
      std::cout << "Tile: " << tsx.tileList[i].id << " - ";
      for(int j = 0; j < tsx.tileList[j].terrain.size(); ++j) {
        if( j != 0 ) {
          std::cout << "," << tsx.tileList[i].terrain[j];
        } else if (j == tsx.tileList.size()) {
          std::cout << tsx.tileList[i].terrain[j];
        } else {
          std::cout << tsx.tileList[i].terrain[j];
        }
      }
      std::cout << std::endl;
      std::map<std::string,std::string>::iterator iter = tsx.tileList[i].property.begin();
      std::map<std::string,std::string>::iterator end_iter = tsx.tileList[i].property.end();

      for(; iter != end_iter; ++iter) {
        std::cout << "->" << iter->first << " : " << iter->second << std::endl;
      }
    }
    ////////////////////
    // TSXParse ends here
    ////////////////////
  }

  std::cout << std::endl;
  for( std::map<std::string, TMX::Parser::TileLayer>::iterator it = tmx.tileLayer.begin(); 
        it != tmx.tileLayer.end(); ++it ) {
    std::cout << std::endl;
    std::cout << "Tile Layer Name: " << it->first << std::endl;
    std::cout << "Tile Layer Visibility: " << tmx.tileLayer[it->first].visible << std::endl;
    std::cout << "Tile Layer Opacity: " << tmx.tileLayer[it->first].opacity << std::endl;
    std::cout << "Tile Layer Properties:" << std::endl;
    if( tmx.tileLayer[it->first].property.size() != 0 ) {
      for( std::map<std::string, std::string>::iterator it2 = tmx.tileLayer[it->first].property.begin();
           it2 != tmx.tileLayer[it->first].property.end(); ++it2 ) {
        std::cout << "-> " << it2->first << " : " << it2->second << std::endl;
      }
    }
    std::cout << "Tile Layer Data Encoding: " << tmx.tileLayer[it->first].data.encoding << std::endl;
    if( tmx.tileLayer[it->first].data.compression != "none" ) {
      std::cout << "Tile Layer Data Compression: " << tmx.tileLayer[it->first].data.compression << std::endl;
    }
    std::cout << "Tile Layer Data Contents:" << tmx.tileLayer[it->first].data.contents << std::endl;
    // decode tile layer data content
    //std::string decomp = decompress_string(tmx.tileLayer[it->first].data.contents);
    //std::string tile_layer = base64_decode(decomp);
    // base64
    //std::string tile_layer = base64_decode(tmx.tileLayer[it->first].data.contents);
    // base64 + zlib
    std::string& raw_tlayer = tmx.tileLayer[it->first].data.contents;
    raw_tlayer = trim(raw_tlayer);
    std::string decoded = base64_decode(raw_tlayer);
    std::string tile_layer = decompress_string(decoded);
    // plain csv
    //std::string& tile_layer = tmx.tileLayer[it->first].data.contents;
    std::vector<int> tile_ids;
    //std::cout << "Decoded Tile Layer: " << tile_layer << std::endl;
    for(std::string::iterator it = tile_layer.begin(); it != tile_layer.end(); ++it) {
      tile_ids.push_back( (int)(*it) );
    }
    for(std::vector<int>::iterator itTileId = tile_ids.begin(); 
      itTileId != tile_ids.end(); ++itTileId) { 
      std::cout << *itTileId << ", ";
    }  
    std::cout << std::endl;
    
  }

  for( std::map<std::string, TMX::Parser::ObjectGroup>::iterator it = tmx.objectGroup.begin(); it != tmx.objectGroup.end(); ++it ) {
    std::cout << std::endl;
    std::cout << "Object Group Name: " << it->first << std::endl;
    std::cout << "Object Group Color: " << tmx.objectGroup[it->first].color << std::endl;
    std::cout << "Object Group Visibility: " << tmx.objectGroup[it->first].visible << std::endl;
    std::cout << "Object Group Opacity: " << tmx.objectGroup[it->first].opacity << std::endl;
    std::cout << "Object Group Properties:" << std::endl;
    if( tmx.objectGroup[it->first].property.size() != 0 ) {
      for( std::map<std::string, std::string>::iterator it2 = tmx.objectGroup[it->first].property.begin(); it2 != tmx.objectGroup[it->first].property.end(); ++it2 ) {
        std::cout << "-> " << it2->first << " : " << it2->second << std::endl;
      }
    }
    for( std::map<std::string, TMX::Parser::Object>::iterator it2 = tmx.objectGroup[it->first].object.begin();
         it2 != tmx.objectGroup[it->first].object.end(); ++it2 ) {
      std::cout << std::endl;
      if( it2->second.name != "") { std::cout << "Object Name: " << it2->first << std::endl; }
      if( it2->second.type != "") { std::cout << "Object Type: " << tmx.objectGroup[it->first].object[it2->first].type << std::endl; }
      std::cout << "Object Position X: " << tmx.objectGroup[it->first].object[it2->first].x << std::endl;
      std::cout << "Object Position Y: " << tmx.objectGroup[it->first].object[it2->first].y << std::endl;
      std::cout << "Object Width: " << tmx.objectGroup[it->first].object[it2->first].width << std::endl;
      std::cout << "Object Height: " << tmx.objectGroup[it->first].object[it2->first].height << std::endl;
      if( it2->second.gid != 0) { std::cout << "Object Tile GID: " << tmx.objectGroup[it->first].object[it2->first].gid << std::endl; }
      std::cout << "Object Visible: " << tmx.objectGroup[it->first].object[it2->first].visible << std::endl;
    }
  }

  for( std::map<std::string, TMX::Parser::ImageLayer>::iterator it = tmx.imageLayer.begin();
                       it != tmx.imageLayer.end(); ++it ) {
    std::cout << std::endl;
    std::cout << "Image Layer Name: " << it->first << std::endl;
    std::cout << "Image Layer Visibility: " << tmx.imageLayer[it->first].visible << std::endl;
    std::cout << "Image Layer Opacity: " << tmx.imageLayer[it->first].opacity << std::endl;
    std::cout << "Image Layer Properties:" << std::endl;
    if( tmx.imageLayer[it->first].property.size() != 0 ) {
      for( std::map<std::string, std::string>::iterator it2 = tmx.imageLayer[it->first].property.begin();
                     it2 != tmx.imageLayer[it->first].property.end(); ++it2 ) {
        std::cout << "-> " << it2->first << " : " << it2->second << std::endl;
      }
    }
    std::cout << "Image Layer Source: " << tmx.imageLayer[it->first].image.source << std::endl;
    std::cout << "Image Layer Transparent Color: " << tmx.imageLayer[it->first].image.transparencyColor << std::endl;
  }

}

*/





