# Status of C++11 in `libes`

`libes` is written in C++11. But compilers that support a subset of C++11 and that are in current use [may](https://www.ietf.org/rfc/rfc2119.txt) be supported. This includes:

- latest [Debian stable distribution](https://www.debian.org/releases/stable/): currently _wheezy_ with [GCC 4.7.2](https://packages.debian.org/wheezy/gcc) and [Clang 3.0](https://packages.debian.org/wheezy/clang)
- latest [Ubuntu LTS](https://wiki.ubuntu.com/LTS): currently _precise (12.04)_ with [GCC 4.6.3](http://packages.ubuntu.com/precise/gcc) and [Clang 3.0](http://packages.ubuntu.com/precise/clang)
- [MSVC](http://en.wikipedia.org/wiki/Visual_C++) of year _current_ - 2: current MSVC 2012.

In order to keep the code clean, a preprocessor variable named `COMPILER_IS_NOT_CXX11_READY` is defined when the compiler does not support the full C++11 standard. There is no fine-grain feature selection, just a rough binary choice. This variable (and the support for non C++11 compilers) should disappear in a mid-term future.
