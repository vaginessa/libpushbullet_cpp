# LIBPUSHBULLET #

C++ library for Pushbullet API

## DEPENDENCIES ##

You have to install JsonCpp from GitHub:

```bash
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
```

## Contributors ##
Henri Buyse (henri.buyse@gmail.com)