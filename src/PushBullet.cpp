/**
 * @file PushBullet.cpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 *
 * @brief Methods of the class PushBullet
 */

#include "PushBullet.hpp"



PushBullet::PushBullet() {
    this->_tokenKey = "00000000000000000000000000000000";
}



PushBullet::PushBullet(const std::string tokenKey) {
    this->_tokenKey = tokenKey;
}



PushBullet::~PushBullet(void) {
}



std::string PushBullet::get_token_key(void) const {
    return this->_tokenKey;
}



std::string PushBullet::get_user_name(void) const {
    return this->_name;
}



std::string PushBullet::get_user_email(void) const {
    return this->_email;
}



std::string PushBullet::get_user_url_photo(void) const {
    return this->_url_photo;
}



#ifdef _DEBUG_
void PushBullet::display_token_key(void) const {
    std::cout << "Token Key : " << this->get_token_key() << std::endl;
}



void PushBullet::display_devices(void) {
    std::cout << "Device: " << std::endl;

#ifdef _CPP_11_
    for (auto& x: this->_devices) {
        std::cout << "- " << x.first << " : " << x.second << '\n';
    }
#else
    for (std::map<std::string, std::string>::iterator it=this->_devices.begin(); it!=this->_devices.end(); ++it){
        std::cout << "- " << it->first << " : " << it->second << '\n';
    }
#endif
}



void PushBullet::display_user_informations(void) const {
    std::cout << "User informations:" << std::endl
              << "Name:      " << this->get_user_name() << std::endl
              << "API token: " << this->get_token_key() << std::endl
              << "Email:     " << this->get_user_email() << std::endl
              << "URL photo: " << this->get_user_url_photo() << std::endl;
}
#endif



short PushBullet::post_request(const std::string url_request, std::string *result, const std::string data) {
    /*  Documentation on CURL for C can be found at http://curl.haxx.se/libcurl/c/
     */

    /*  Start a libcurl easy session
    */
    CURL *s = curl_easy_init();

    result->clear();

    if (s) {
        CURLcode r = CURLE_OK;
        curl_slist *http_headers = NULL;

        http_headers = curl_slist_append(http_headers, "Content-Type: application/json");


        /*  Specify URL to get
         *  Specify the user using the token key
         *  Specify that we are going to post
         *  Specify the data we are about to send
         *  Specify the HTTP header
         *  Send all data to the WriteMemoryCallback method
         */
        curl_easy_setopt(s, CURLOPT_URL, url_request.c_str());
        curl_easy_setopt(s, CURLOPT_USERPWD, this->get_token_key().c_str());
        curl_easy_setopt(s, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(s, CURLOPT_HTTPHEADER, http_headers);
        curl_easy_setopt(s, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(s, CURLOPT_WRITEDATA, &(*result));

        /* Get data
        */
        r = curl_easy_perform(s);

        /* Checking errors
        */
        if (r != CURLE_OK) {
#ifdef _DEBUG_
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(r) << std::endl;
#endif
            return -2;
        }

        curl_easy_cleanup(s);
        curl_slist_free_all(http_headers);
    }
    else {
#ifdef _DEBUG_
        std::cerr << "curl_easy_init() could not be initiated." << std::endl;
#endif
        return -1;
    }

    return 0;
}



short PushBullet::get_request(const std::string url_request, std::string *result) {
    /*  Documentation on CURL for C can be found at http://curl.haxx.se/libcurl/c/
     */

    /*  Start a libcurl easy session
    */
    CURL *s = curl_easy_init();

    result->clear();

    if (s) {
        CURLcode r = CURLE_OK;
        curl_slist *http_headers = NULL;

        http_headers = curl_slist_append(http_headers, "Content-Type: application/json");

        /*  Specify URL to get
         *  Specify the user using the token key
         *  Specify the data we are about to send
         *  Specify the HTTP header
         *  Send all data to the WriteMemoryCallback method
         */
        curl_easy_setopt(s, CURLOPT_URL, url_request.c_str());
        curl_easy_setopt(s, CURLOPT_USERPWD, this->get_token_key().c_str());
        curl_easy_setopt(s, CURLOPT_HTTPHEADER, http_headers);
        curl_easy_setopt(s, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(s, CURLOPT_WRITEDATA, &(*result));

        /* Get data
        */
        r = curl_easy_perform(s);

        /* Checking errors
        */
        if (r != CURLE_OK) {
#ifdef _DEBUG_
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(r) << std::endl;
#endif
            return -2;
        }

        curl_easy_cleanup(s);
        curl_slist_free_all(http_headers);
    }
    else {
#ifdef _DEBUG_
        std::cerr << "curl_easy_init() could not be initiated." << std::endl;
#endif
        return -1;
    }

    return 0;
}


short PushBullet::delete_request(const std::string url_request, std::string *result) {
    /*  Documentation on CURL for C can be found at http://curl.haxx.se/libcurl/c/
     */

    /*  Start a libcurl easy session
    */
    CURL *s = curl_easy_init();

    if (s) {
        CURLcode r = CURLE_OK;
        curl_slist *http_headers = NULL;

        http_headers = curl_slist_append(http_headers, "Content-Type: application/json");

        /*  Specify URL to get
         *  Specify the user using the token key
         *  Specify the HTTP header
         */
        curl_easy_setopt(s, CURLOPT_URL, url_request.c_str());
        curl_easy_setopt(s, CURLOPT_USERPWD, this->get_token_key().c_str());
        curl_easy_setopt(s, CURLOPT_HTTPHEADER, http_headers);
        curl_easy_setopt(s, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(s, CURLOPT_WRITEDATA, &(*result));

        /* Set the DELETE command
         */
        curl_easy_setopt(s, CURLOPT_CUSTOMREQUEST, "DELETE");

        /* Get data
        */
        r = curl_easy_perform(s);

        /* Checking errors
        */
        if (r != CURLE_OK) {
#ifdef _DEBUG_
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(r) << std::endl;
#endif
            return -2;
        }

        curl_easy_cleanup(s);
        curl_slist_free_all(http_headers);
    }
    else {
#ifdef _DEBUG_
        std::cerr << "curl_easy_init() could not be initiated." << std::endl;
#endif
        return -1;
    }

    return 0;
}



short PushBullet::note(const std::string title, const std::string body) {
    std::stringstream data;
    std::string result;

    data << "{"
         << "\"type\":\"note\" , "
         << "\"title\":\"" << title << "\" , "
         << "\"body\":\""  << body  << "\""
         << "}";

    if (this->post_request(API_URL_PUSHES, &result, data.str()) != 0) {
#ifdef _DEBUG_
        std::cerr << "POST_REQUEST > Impossible to send a note" << std::endl;
#endif
        return -1;
    }

#ifdef _DEBUG_
    std::cout << "Data send: "     << std::endl << data.str()   << std::endl;
    std::cout << "Response CURL: " << std::endl << result << std::endl;
#endif

    return 0;
}


short PushBullet::note(const std::string title, const std::string body, const std::string iden) {
    std::stringstream data;
    std::string result;

    data << "{"
         << "\"device_iden\":\""  << iden  << "\", "
         << "\"type\":\"note\", "
         << "\"title\":\""        << title << "\", "
         << "\"body\":\""         << body  << "\""
         << "}";

    if (this->post_request(API_URL_PUSHES, &result, data.str()) != 0) {
#ifdef _DEBUG_
        std::cerr << "POST_REQUEST > Impossible to send a note" << std::endl;
#endif
        return -1;
    }

#ifdef _DEBUG_
    std::cout << "Data send: "     << std::endl << data.str()   << std::endl;
    std::cout << "Response CURL: " << std::endl << result << std::endl;
#endif

    return 0;
}


short PushBullet::link(const std::string title, const std::string body, const std::string url) {
    std::stringstream data;
    std::string result;

    data << "{"
         << "\"type\":\"link\", "
         << "\"title\":\"" << title << "\", "
         << "\"body\":\""  << body  << "\", "
         << "\"url\":\""   << url   << "\""
         << "}";

    if (this->post_request(API_URL_PUSHES, &result, data.str()) != 0) {
#ifdef _DEBUG_
        std::cerr << "POST_REQUEST > Impossible to send a link" << std::endl;
#endif
        return -1;
    }

#ifdef _DEBUG_
    std::cout << "Data send: "     << std::endl << data.str()   << std::endl;
    std::cout << "Response CURL: " << std::endl << result << std::endl;
#endif

    return 0;
}


short PushBullet::link(const std::string title, const std::string body, const std::string url, const std::string iden) {
    std::stringstream data;
    std::string result;

    data << "{"
         << "\"device_iden\":\"" << iden  << "\", "
         << "\"type\":\"link\", "
         << "\"title\":\""       << title << "\", "
         << "\"body\":\""        << body  << "\", "
         << "\"url\":\""         << url   << "\""
         << "}";

    if (this->post_request(API_URL_PUSHES, &result, data.str()) != 0) {
#ifdef _DEBUG_
        std::cerr << "POST_REQUEST > Impossible to send a link" << std::endl;
#endif
        return -1;
    }

#ifdef _DEBUG_
    std::cout << "Data send: "     << std::endl << data.str()   << std::endl;
    std::cout << "Response CURL: " << std::endl << result << std::endl;
#endif

    return 0;
}



short PushBullet::get_user_informations(void) {
    std::string result;
    std::stringstream conversion;
    Json::Value json;               // will contain the root value after parsing.

    if (this->get_request(API_URL_ME, &result) != 0){
#ifdef _DEBUG_
        std::cerr << "GET_REQUEST > Impossible to ask for all user informations" << std::endl;
#endif
        return -1;
    }

    /* Convert the string 'result' to be understand by the Json parser
    */
    conversion << result;
    conversion >> json;

#ifdef _JSON_
    std::cout << "Json Document: " << std::endl << json   << std::endl;
#endif

    /* Get the identification of the device corresponding to all of them
    */
    this->_devices.insert(std::pair<std::string, std::string>("All devices", json.get("iden", "null").asString()));

    /* Get email of the user
     * Get name of the user
     * Get the url of his profile picture
     *
     */
    this->_email     = json.get("email",     "null").asString();
    this->_name      = json.get("name",      "null").asString();
    this->_url_photo = json.get("image_url", "null").asString();

    return 0;
}


short PushBullet::get_all_devices(void) {
    std::string result;
    std::stringstream conversion;
    Json::Value json;               // will contain the root value after parsing.

    /* Free the device map
     */
    this->_devices.clear();

    if (this->get_request(API_URL_DEVICES, &result) != 0) {
#ifdef _DEBUG_
        std::cerr << "GET_REQUEST > Impossible to ask for all devices" << std::endl;
#endif
        return -1;
    }

    /* Convert the string 'result' to be understand by the Json parser
    */
    conversion << result;
    conversion >> json;

#ifdef _JSON_
    std::cout << "Json Document: " << std::endl << json   << std::endl;
#endif

    /* Get the list of devices
    */
    const Json::Value devices = json["devices"];
    for (int index = 0; index < (int)devices.size(); ++index) {
        /* Check if the device is still active
         * If it is, we add it in the list of devices.
         */
        if (devices[index].get("active", false).asBool()) {
            this->_devices.insert(std::pair<std::string, std::string>(
                                  devices[index].get("nickname", "null").asString(),
                                  devices[index].get("iden", "null").asString()));
        }
    }


    return 0;
}


/* curl --header 'Authorization: Bearer <your_access_token_here>' -X POST
 * https://api.pushbullet.com/v2/devices -d nickname=stream_device -d type=stream
 */
short PushBullet::create_device_if_not_existing(void) {
    /* Structure that will contain informations about the computer.
    */
    struct utsname buffer;

    std::stringstream data;
    std::string result;

    /* File that contains informations about the Linux distribution and its distribution.
    */
    std::ifstream lsb_release("/etc/lsb-release", std::ifstream::in);
    std::string line;
    std::string model, nickname, type;

    /* REGEXS
    */
#ifdef _BOOST_
    boost::regex regex(DISTRIB_DESCRIPTION_PATTERN, boost::regex::extended);
    boost::match_results<std::string::const_iterator> sm;
#else
    std::regex   regex(DISTRIB_DESCRIPTION_PATTERN);
    std::smatch  sm;
#endif


    /*  Get informations about the computer
    */
    if (uname(&buffer) != 0) {
#ifdef _DEBUG_
        std::cerr << "UNAME > Impossible to get the informations about the computer!" << std::endl;
#endif
        return -2;
    }


    /* Store the strings
    */
    nickname = std::string(buffer.nodename);
    type = std::string(buffer.sysname);
    std::transform(type.begin(), type.end(), type.begin(), ::tolower); // Convert to lower
    model = std::string(buffer.sysname) + '-' + std::string(buffer.release);


    /* Try to open the file /etc/release to get the model (OS Version)
     */
    if (lsb_release.is_open()) {
        while (getline(lsb_release, line)) {
#ifdef _BOOST_
            if (boost::regex_match(line, sm, regex)) {
                model = sm[1];
            }
#else
            if (std::regex_match(line, sm, regex)) {
                model = sm[1].str();
                model.erase(std::remove(model.begin(), model.end(), '\"'), model.end());
            }
#endif
        }
        lsb_release.close();
    }

    if (this->_devices.count(nickname)) {
#ifdef _DEBUG_
        std::cerr << "FIND > This device already exists in your account. No need to create a new one." << std::endl;
#endif
        return 1;
    }

    data << "{"
         << "\"nickname\" : \"" << nickname << "\", "
         << "\"model\" : \""    << model    << "\", "
         << "\"type\" : \""     << type     << "\", "
         << "\"icon\" : \"desktop\""
         << "}";

    if (this->post_request(API_URL_DEVICES, &result, data.str()) != 0){
#ifdef _DEBUG_
        std::cerr << "POST_REQUEST > Impossible to create a new device." << std::endl;
#endif
        return -1;
    }

    /* Refresh the list of devices
     */
    this->get_all_devices();

    return 0;
}


/* curl --header 'Authorization: Bearer <your_access_token_here>'
 * -X DELETE https://api.pushbullet.com/v2/devices/u1qSJddxeKwOGuGW
 */
short PushBullet::delete_device(const std::string nickname) {
    std::stringstream request_url;
    std::string result;
    std::string iden;

    if (!this->_devices.count(nickname)) {
#ifdef _DEBUG_
        std::cerr << "SELECT_DEVICE > No device that is named " << nickname << "." << std::endl;
#endif
        return -1;
    }

    /* Get the identification number from the _devices map.
    */
    iden = this->_devices.at(nickname);

    request_url << API_URL_DEVICES << "/" << iden;
    if (this->delete_request(request_url.str(), &result) != 0) {
#ifdef _DEBUG_
        std::cerr << "DELETE > Impossible to create a new device." << std::endl;
#endif
        return -2;
    }

    /* Refresh the list of devices
     */
    this->get_all_devices();

    return 0;
}