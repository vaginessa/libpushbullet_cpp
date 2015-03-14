#ifndef PUSHBULLET_HPP_
#define PUSHBULLET_HPP_

/**
 * @file PushBullet.hpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 *
 * @brief Header will be the connection to the API PushBullet
 */

#include <iostream>         // std::cout
#include <curl/curl.h>      // Whole librairy
#include <string>           // string
#include <sstream>          // stringstream
#include <map>              // map
#include <json/json.h>      // Json::Value
#include <sys/utsname.h>    // int uname(struct utsname *buf);

/**
 * @def API_URL
 */
#define API_URL         "https://api.pushbullet.com/v2/"

/**
 * @def API_URL_PUSHES
 */
#define API_URL_PUSHES  "https://api.pushbullet.com/v2/pushes"

/**
 * @def API_URL_DEVICES
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
     * @brief User Access Token
     * @details This Access Token grants full access to the user account.
     *          Don't share this lightly.
     */
    std::string _tokenKey;

    /**
     * @brief List of devices
     * @details This list contains all the devices that the user has connected to its PushBullet Account.
     */
    std::map<std::string, std::string> _devices;

public:

    /**
     * @brief Default constructor of class PushBullet.
     * @details This constructor create an default object that cannot be used.
     */
    PushBullet();

    /**
     * @brief Constructor of class PushBullet.
     * @details This method is a constructor of the class.
     *          Its argument tokenKey allow the developer to access the PushBullet API.
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
     *
     * @return A string containing the Access Token
     */
    std::string get_token_key(void) const;

    #ifdef _DEBUG_
    /**
     * @brief Display the Token key
     * @details Display in the terminal the Token key of the user
     */
    void display_token_key(void) const;

    /**
     * @brief Display the list of devices
     */
    void display_devices(void);
    #endif

    /**
     * @brief Do a POST request to the specific URL given by request_url
     *
     * @param request_url URL which you want to POST
     * @param result String that contains the result and that can be reused
     * @param data Data you are going to POST
     *
     * @return Error code
     */
    short post_request(std::string request_url, std::string *result, std::string data);

    /**
     * @brief Do a GET request to the specific URL given by request_url
     *
     * @param request_url URL which you want to GET
     * @param result String that contains the result and that can be reused
     *
     * @return Error code
     */
    short get_request(std::string request_url, std::string *result);

    /**
     * @brief Send a note to all devices or a specific device
     *
     * @param title Title of the note
     * @param body Body of the note
     *
     * @return Error code
     */
    short note(const std::string title, const std::string body);

    /**
     * @see PushBullet::note()
     *
     * @param iden The identification of the specific device you want to push to.
     */
    short note(const std::string title, const std::string body, const std::string iden);

    /**
     * @brief Send a link
     * @details [long description]
     *
     * @param title Title of the URL push
     * @param body Body of the URL push
     * @param url The URL given
     *
     * @return Error code
     */
    short link(const std::string title, const std::string body, const std::string url);

    /**
     * @see PushBullet::link()
     *
     * @param iden The identification of the specific device you want to push to.
     */
    short link(const std::string title, const std::string body, const std::string url, const std::string iden);

    /**
     * @brief Get all the devices
     * @details Get all the active devices and stock them in the list devices.
     *          GET https://api.pushbullet.com/v2/devices
     * @return Error code
     */
    short get_all_devices(void);

};

#endif //PUSHBULLET_HPP_