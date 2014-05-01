# Status of C++11 in `libes`

`libes` is written in C++11. But compilers that support a subset of C++11 and that are in current use [may](https://www.ietf.org/rfc/rfc2119.txt) be supported. This includes:

- latest [Debian stable distribution](https://www.debian.org/releases/stable/): currently _wheezy_ with [GCC 4.7.2](https://packages.debian.org/wheezy/gcc) and [Clang 3.0](https://packages.debian.org/wheezy/clang)
- latest [Ubuntu LTS](https://wiki.ubuntu.com/LTS): currently _trusty (14.04)_ with [GCC 4.8.2](http://packages.ubuntu.com/trusty/gcc) and [Clang 3.4](http://packages.ubuntu.com/trusty/clang)
- [MSVC](http://en.wikipedia.org/wiki/Visual_C++) of year _current_ - 2: current MSVC 2012 (11.0).

In order to keep the code clean, a preprocessor variable named `COMPILER_IS_NOT_CXX11_READY` is defined when the compiler does not support the full C++11 standard. There is no fine-grain feature selection, just a rough binary choice. This variable (and the support for non C++11 compilers) should disappear in a mid-term future.

You can check the [table for C++11 support in compilers](http://en.cppreference.com/w/cpp/compiler_support).
