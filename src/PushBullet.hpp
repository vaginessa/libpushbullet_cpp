/**
 * @file PushBullet.hpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 *
 * @brief Header will be the connection to the API PushBullet
 */

#ifndef PUSHBULLET_HPP_
#define PUSHBULLET_HPP_

#include <algorithm>        // tolower
#include <curl/curl.h>      // Whole librairy
#include <fstream>          // ifstream
#include <iostream>         // std::cout
#include <json/json.h>      // Json::Value
#include <map>              // map
#include <sstream>          // stringstream
#include <string>           // string
#include <sys/utsname.h>    // int uname(struct utsname *buf);

/* BOOST LIBRARIES
 */
#include <boost/program_options.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/regex.hpp>  // boost::regex


/**
 * Version of the library
 */
#define VERSION "0.0.1"

/**
 * Basic URL for PushBullet API
 */
#define API_URL "https://api.pushbullet.com/v2/"

/**
 * PushBullet API URL for the pushes
 */
#define API_URL_PUSHES API_URL "pushes"

/**
 * PushBullet API URL for the devices
 */
#define API_URL_DEVICES API_URL "devices"

/**
 * PushBullet API URL for the user informations
 */
#define API_URL_ME API_URL "users/me"

/**
 * PushBullet API URL to get contacts from the user account
 */
#define API_URL_CONTACTS API_URL "contacts"

/**
 * Path to the file /etc/lsb-release
 */
#define LSB_RELEASE_PATH "/etc/lsb-release"

/**
 * Regex to get the name of the Linux distribution running the program
 */
#define DISTRIB_DESCRIPTION_PATTERN "DISTRIB_DESCRIPTION=\"(.*)\""


/**
 * @fn WriteMemoryCallback
 * @brief Write the response of the curl session to a variable.
 *
 * @param contents Response from the server
 * @param size Variable that will help counting the number of characters
 * @param nmemb Variable that will help counting the number of characters
 * @param userp Variable that is going to the application
 *
 * @return Number of characters written
 */
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


/**
 * @brief Class that manage an account using the account's API Token.
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
     * @brief User email
     */
    std::string _email;

    /**
     * @brief User name
     */
    std::string _name;

    /**
     * @brief URL of the profile picture of the user
     */
    std::string _url_photo;

    /**
     * @brief List of devices.
     * @details This list contains all the devices that the user has connected to its PushBullet Account.
     *
     * @param n Name of the device on PushBullet
     * @param e Indentification number of the device on PushBullet
     */
    std::map<std::string, std::string> _devices;

    /**
     * @brief All devices.
     * @details This map contains only the identification sequence that can send push notifications to all devices.
     *
     * @param n String containing 'All'
     * @param e Indentification sequence
     */
    std::pair<std::string, std::string> _all_iden;

    /**
     * @brief List of contacts of the user.
     * @details [long description]
     *
     * @param n Name of a contact
     * @param e Email of the contact
     * @param phone Phone number of the contact
     */
    std::map<std::string, std::pair<std::string, std::string> > _contacts;

public:

    // The token key is taken from the file config.ini (section=token, value=personnal)  allow the developer to access the PushBullet API.

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
     * @brief Copy constructor for the class.
     *
     * @param p Class you want to copy.
     */
    PushBullet(const PushBullet& p);

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

    /**
     * @brief Getter of the user name
     *
     * @return A string containing the name of the user
     */
    std::string get_user_name(void) const;

    /**
     * @brief Getter of the user email
     *
     * @return A string containing the email of the user
     */
    std::string get_user_email(void) const;

    /**
     * @brief Getter of the url of the user's pictures
     *
     * @return A string containing the url of the user's pictures
     */
    std::string get_user_url_photo(void) const;

    /**
     * @brief Display the Token key
     * @details Display in the terminal the Token key of the user
     */
    void display_token_key(void) const;

    /**
     * @brief Display the list of devices
     */
    void display_devices(void);

    /**
     * @brief Display user informations
     * @details Display all the user informations that I (Henri BUYSE) think important.
     */
    void display_user_informations(void) const;

    /**
     * @brief Display user informations
     * @details Display all the user informations that I (Henri BUYSE) think important.
     */
    void display_contacts(void);

    /**
     * @brief Do a POST request to the specific URL given by request_url
     *
     * @param request_url URL which you want to POST
     * @param result String that contains the result and that can be reused
     * @param data Data you are going to POST
     *
     * @return Error code
     */
    short post_request(const std::string request_url, std::string *result, const std::string data);

    /**
     * @brief Do a GET request to the specific URL given by request_url
     *
     * @param request_url URL which you want to GET
     * @param result String that contains the result and that can be reused
     *
     * @return Error code
     */
    short get_request(const std::string request_url, std::string *result);

    /**
     * @brief Do a DELETE request to the specific URL given by request_url
     *
     * @param request_url URL which you want to DELETE
     * @param result String that contains the result and that can be reused
     *
     * @return Error code
     */
    short delete_request(const std::string request_url, std::string *result);

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
     * @brief Send a note to all devices or a specific device
     *
     * @param title Title of the note
     * @param body Body of the note
     * @param iden The identification of the specific device you want to push to.
     *
     * @return Error code
     */
    short note(const std::string title, const std::string body, const std::string iden);

    /**
     * @brief Send a link
     *
     * @param title Title of the URL push
     * @param body Body of the URL push
     * @param url The URL given
     *
     * @return Error code
     */
    short link(const std::string title, const std::string body, const std::string url);

    /**
     * @brief Send a link
     *
     * @param title Title of the URL push
     * @param body Body of the URL push
     * @param url The URL given
     * @param iden The identification of the specific device you want to push to.
     *
     * @return Error code
     */
    short link(const std::string title, const std::string body, const std::string url, const std::string iden);

    /**
     * @brief Get informations about the user
     * @details Get all informations about the user.
     *          GET https://api.pushbullet.com/v2/users/me
     *
     * @return Error code
     */
    short download_user_informations(void);

    /**
     * @brief Get all the devices
     * @details Get all the active devices and stock them in the list devices.
     *          GET https://api.pushbullet.com/v2/devices
     *
     * @return Error code
     */
    short download_all_devices(void);

    /**
     * @brief Create a new device if not existing
     * @details Based on the devices that are already registered to the account, if it does not have registered the
     *          device it creates a new one.
     *
     * @return Error code
     */
    short create_device_if_not_existing(void);

    /**
     * @brief Delete a device
     * @details Allow you to delete (deactivate) a device that has been added to your PushBullet account
     *
     * @param iden Identification string of the device you want to delete
     *
     * @return Error code
     */
    short delete_device(const std::string nickname);

    /**
     * @brief Download the list of the user's contacts
     *
     * @return Error code
     */
    short download_contacts(void);

    /**
     * @brief Create a contact
     *
     * @param name Contact's name
     * @param email Contact's email
     *
     * @return Error code
     */
    short create_contact(const std::string name, const std::string email);

};

#endif //PUSHBULLET_HPP_