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
#include <string>
#include <sstream>
#include <map>
#include <vector>

/**
 * @def API_URL
 */
#define API_URL         "https://api.pushbullet.com/v2/"

/**
 * @def API_URL_PUSHES
 */
#define API_URL_PUSHES  "https://api.pushbullet.com/v2/pushes"

/**
 * @def
 */
#define API_URL_DEVICES "https://api.pushbullet.com/v2/devices"


/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param contents [description]
 * @param size [description]
 * @param nmemb [description]
 * @param userp [description]
 * @return [description]
 */
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


/**
 * @brief [brief description]
 * @details [long description]
 * 
 */
class PushBullet
{
private:
    /**
     * @brief [brief description]
     * @details [long description]
     */
    std::string _tokenKey;

    std::vector<std::string> devices;

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
    PushBullet(const std::string tokenKey);

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
    const std::string get_token_key(void);

    #ifdef _DEBUG_
    /**
     * @brief Display the Token key
     * @details Display in the terminal the Token key of the user
     */
    void display_token_key(void);
    #endif

    /**
     * @brief [brief description]
     * @details [long description]
     * 
     * @param data [description]
     * @return [description]
     */
    short post_request(std::string request_url, std::string *result, std::string data);

    /**
     * @brief [brief description]
     * @details [long description]
     * 
     * @param request_url [description]
     * @return [description]
     */
    short get_request(std::string request_url, std::string *result);

    /**
     * @brief [brief description]
     * @details [long description]
     * 
     * @param title [description]
     * @param body [description]
     * 
     * @return [description]
     */
    short note(std::string title, std::string body);

    /**
     * @brief [brief description]
     * @details [long description]
     * 
     * @param title [description]
     * @param body [description]
     * @param url [description]
     * @return [description]
     */
    short link(std::string title, std::string body, std::string url);

    /**
     * @brief [brief description]
     * @details [long description]
     * @return [description]
     */
    short list_devices(void);

};

#endif //PUSHBULLET_HPP_