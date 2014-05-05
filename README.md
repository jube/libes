# `libes`, an Entity System library

`libes` is a library for managing an [entity system](http://en.wikipedia.org/wiki/Entity_component_system) written in C++.

## Entity systems

If you do not know what an entity system is, you should read the following blog entries:

* [Evolve your hierarchy](http://cowboyprogramming.com/2007/01/05/evolve-your-heirachy/), Mick West, Jan 2007
* [Entity Systems are the future of MMOG development](http://t-machine.org/index.php/2007/09/03/entity-systems-are-the-future-of-mmog-development-part-1/), Adam Martin, Sep 2007
* [What is an entity system framework for game development?](http://www.richardlord.net/blog/what-is-an-entity-framework), Richard Lord, Jan 2012
* (in French) [Les systèmes à entités](http://linuxfr.org/news/je-cree-mon-jeu-video-e01-les-systemes-a-entites), Julien Bernard, Sep 2013

You can also check the [Entity Systems Wiki](http://entity-systems.wikidot.com/).

## Requirements

`libes` is written in C++11 so you need a C++11 compiler like [Clang](http://clang.llvm.org/) or [GCC](http://gcc.gnu.org/). There is no other dependency.

## Build and install

You can download the sources directly from github:

    git clone https://github.com/jube/libes.git

Then you have to use [CMake](http://www.cmake.org/) to build the project:

    cd libes
    mkdir build
    cd build
    cmake ../src
    make

Finally, you can install the files (you may need root permissions):

    make install

## Use

`libes` provides a [pkg-config](http://www.freedesktop.org/wiki/Software/pkg-config/) file so you can use it to configure your project.

    pkg-config --cflags --libs libes0

Then you can check the [libes tutorial](https://github.com/jube/libes/blob/master/doc/tutorial.md) to learn how to use the library.


## Authors

- Julien Bernard, julien dot bernard at univ dash fcomte dot fr

## Contributors

- [Sébastien Rombauts](https://github.com/SRombauts), sebastien dot rombauts at gmail dot com
- [Pierre Marijon](https://github.com/natir), pierre at marijon dot fr

## ChangeLog

See [ChangeLog.md](https://github.com/jube/libes/blob/master/ChangeLog.md).

## Copyright

This library is open source and is distributed under the [ISC licence](http://opensource.org/licenses/isc-license).
