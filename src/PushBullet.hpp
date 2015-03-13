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


#define API_URL        "https://api.pushbullet.com/v2/"
#define API_URL_PUSHES "https://api.pushbullet.com/v2/pushes"

using namespace std;

class PushBullet
{
private:
    const char* _tokenKey;

public:

    /**
     * @brief Default constructor of class PushBullet.
     * @details This constructor create an default object that cannot be used.
     */
    PushBullet();

    /**
     * @brief Constructor of class PushBullet.
     * @details This method is a constructor of the class.
     * Its argument tokenKey allow the developer to access the PushBullet API.
     *
     * @param tokenKey Access Token given by the PushBullet website in the rubric "Account Settings"
     */
    PushBullet(const char* tokenKey);

    /**
     * @brief Default destructor of the class.
     * @details This destructor is automatically called after the destruction of an object PushBullet.
     */
    ~PushBullet();

    /**
     * @brief Getter of the Token key
     * @details [long description]
     * @return A string containing the Access Token
     */
    const char* getToken();

    /**
     * @brief Display the Token key
     * @details Display in the terminal the Token key of the user
     */
    void display();


    short pushing(char* data);

};

#endif //PUSHBULLET_HPP_