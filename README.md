cxxcompat
=========

C++ compatibility header-only library. Implements as much of C++11/14 as is possible without compiler help.

Implemented C++ version
-----------------------
The plan is to always implement the latest working draft of C++. Currently, this is [N3690](http://isocpp.org/files/papers/N3690.pdf) - C++14 committee draft from 2013-05-15.

Supported compilers
-------------------
- clang 3.2+
- gcc 4.6+

How to use?
-----------
Probably the easiest way to use it is to add an git submodule to your project, and then add -Icxxcompat/include to the CXXFLAGS.

How to build tests?
-------------------
	mkdir build
	cd build
	cmake ..
	make
	make test

If you want to test under another compiler, simply remove your `build` directory,
	export CXX=/usr/bin/compiler-binary
and follow listed steps once more.
