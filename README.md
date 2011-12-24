Restnotifier
============
Restnotifier is application that reminds you to rest after given intervals.
It is written using C++ and Qt.

[Oxygen icons](http://www.oxygen-icons.org/) are used.

Platforms
---------
Currently supported platforms:

- Linux
- Windows

License
-------
Restnotifier is released under the MIT license.

Installation (Linux)
--------------------
    
    git clone git://github.com/swarmer/restnotifier.git
    cd restnotifier
    mkdir build 
    cd build
    cmake ../restnotifier -DCMAKE_BUILD_TYPE=Release
    make
    sudo make install

