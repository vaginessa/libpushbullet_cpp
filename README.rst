=============
LIBPUSHBULLET
=============

C++ library for Pushbullet API


Why no list or address pushes ?
===============================

Since `Pushbullet API v4 <https://docs.pushbullet.com/#changelog>`_ (February 13, 2015): removed list and address from push types, since they are no longer supported by the official clients.

DEPENDENCIES
============

JsonCpp
-------

You have to install JsonCpp from GitHub:

.. code:: bash

    # Clone the repository
    git clone https://github.com/open-source-parsers/jsoncpp.git

    # Checkout to a stable version
    cd jsoncpp
    git checkout 1.6.0

    # Create and compile the library
    mkdir -p build/release
    cd build/release
    cmake -DCMAKE_BUILD_TYPE=release -DJSONCPP_LIB_BUILD_STATIC=ON -DJSONCPP_LIB_BUILD_SHARED=ON -G "Unix Makefiles" ../..
    make
    sudo make install/local


Boost
-----

You can use Boost if you want.

Just do :

.. code:: bash

    make BOOST=1



TESTS
=====

I use Boost Test framework for my unitary tests.

If you want to test my project, launch

.. code:: bash

    make -f mk.test launch


Contributors
============

Henri Buyse