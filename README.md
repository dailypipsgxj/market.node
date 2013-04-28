Market.Node
============

An open source financial exchange toolkit from [Furosys Solutions](http://www.furosys.com/).

## Goals
* Facilitate rapid development and deployment of high-performance, scalable exchanges.
* Provide FAST1.2, FIX5.0SP2/FIXT1.1, and JSON-RPC reference gateways.

## Build Dependencies
* Clang 3.2+ or gcc 4.8+ with a C++11 compliant libc++
* [CMake](http://www.cmake.org) 2.8.x

## Supported Platforms
Development is done on MacOS X Mountain Lion with FreeBSD 10 as the primary deployment target.

Modern Linux distributions should also work, but are relatively untested. 

Windows is unsupported. 

## Build instructions

Out-of-tree builds are recommended. 

    git clone git://github.com/furosys/market.node.git
    mkdir build
    cmake ../market.node
    make 

## Credits


In particular, enormous thanks to [Object Computing, Inc.](http://www.ociweb.com/) for their excellent, liberally licensed libraries:

* [Liquibook](https://github.com/objectcomputing/liquibook): an incredibly fast order matching engine.
* [QuickFIX](http://www.quickfixengine.org/): a FIX message parser. 
* [QuickFAST](https://code.google.com/p/quickfast/): a FAST message parser.

Without their hard work, this project would not be possible. 

## Donate

Send bitcoins to 1EMqiyr8twB8v13aeqhfLp95EDkhAvVs4H to support this project.
