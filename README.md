opengl-balls
==========

simple stuff based on opengl+sdl, contains a very simple entity component system

[![opengl balls](http://img.youtube.com/vi/9qFXidEn7So/0.jpg)](http://www.youtube.com/watch?v=9qFXidEn7So)


mkdir bin

make

to execute, go in bin dir, then: 

./app

then press space to do stuff and m to switch mode


The branch named "alternative" contains code with a different memory layout for entity and components

## Audit process with perf :

perf stat -d ./bin/app

perf record -g -F 199 ./bin/app

perf report -G --stdio --sort=comm,dso --dsos=app,libc-2.19.so
