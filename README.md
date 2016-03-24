# minitasks

Infrastructure to load small tasks and manage them 

![Summary](image/summary.png)
<!-- java -jar /opt/plantuml/plantuml.jar README.md -o images -->
<!--
@startuml summary.png
top to bottom direction
skinparam packageStyle rect
rectangle "Launch\ndifferent tasks" {
}
@enduml
-->

## Requirements

*Doxygen/Latex/Graphviz/Plantuml* tools are needed to generate documentation. If you are not interested in that step, just do not execute **make doc** or **make image** optional targets.

This project is based on **C++14** standard (g++ >= 5.2, clang++ >= 3.8, apple clang++ >= 7xx), latest **boost** libraries (>=1.58) and expected as well a modern *cmake* (>=3.5) so if you work on an updated develop environment, i.e, *Debian sid*, you are supposed to get by default the correct versions:

       rm -rf build && mkdir build && cd build && cmake ..
       
But if you're working on a more stale but robust box, i.e. *RedHat 7*, don't forget to launch **cmake** with enough information to get to latest compilers/libraries (provided specifically compiled boost libraries at /opt/gcc/boost):

       rm -rf build && mkdir build && cd build && cmake -DBOOST_ROOT=/opt/gcc/boost -DCMAKE_C_COMPILER=/opt/gcc/bin/gcc -DCMAKE_CXX_COMPILER=/opt/gcc/bin/g++ ..

If you happen to compile a specific version of **boost** libraries for a *clang* compiler, but remember that they could depend on *libc++* and *libc++abi* when you deploy on a vanilla box. Hence a forced *RUN_PATH* compilation (rpath) will take place to hardcode libc++ & libc++abi path to */opt/clang/lib*:

       rm -rf build && mkdir build && cd build && cmake -DBOOST_ROOT=/opt/clang/boost -DCMAKE_C_COMPILER=/opt/clang/bin/clang -DCMAKE_CXX_COMPILER=/opt/clang/bin/clang++ ..

Something similar if you work on *OSX* (provided Homebrew installed boost libraries at /usr/local/Cellar/boost/1.60.0_1). In this case no need to worry about *llvm/libc++*; on **Apple** platfomrs is the stardard choice (it seems that Google Android & Windows are following that path as well):

       rm -rf build && mkdir build && cd build && cmake -DBOOST_ROOT=/usr/local/Cellar/boost/1.60.0_1 -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ .. 

**Note:** Default flags are defined to statically link as much as possible depending on different systems in order not to require latest development compilers/libraries on deployment machines:

       set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wno-unused-local-typedefs -static-libstdc++ -static-libgcc -g")
       set(Boost_USE_STATIC_LIBS ON CACHE BOOL "use static libraries from Boost")
       set(Boost_USE_STATIC_RUNTIME ON CACHE BOOL "use static runtime from Boost")       
