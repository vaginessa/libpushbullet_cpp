#ifndef PUSHBULLET_HPP_
#define PUSHBULLET_HPP_

/**
 * @file PushBullet.hpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 * 
 * @brief Header will be the connection to the API PushBullet
 */

#include <iostream>
#include <curl/curl.h>


class PushBullet
{
private:
    char * _token;

public:
    PushBullet();
    ~PushBullet();
    
};

#endif //PUSHBULLET_HPP_