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
#endif



short PushBullet::post_request(std::string url_request, std::string *result, std::string data) {
    /*  Documentation on CURL for C can be found at http://curl.haxx.se/libcurl/c/
     */

    /*  Start a libcurl easy session
    */
    CURL *s = curl_easy_init();

    result->clear();

    if (s) {
        CURLcode r;
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

        return 0;
    }
    else {
        #ifdef _DEBUG_
        std::cerr << "curl_easy_init() could not be initiated." << std::endl;
        #endif
        return -1;
    }
}



short PushBullet::get_request(std::string url_request, std::string *result) {
    /*  Documentation on CURL for C can be found at http://curl.haxx.se/libcurl/c/
     */

    /*  Start a libcurl easy session
    */
    CURL *s = curl_easy_init();

    result->clear();

    if (s) {
        CURLcode r;
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

        return 0;
    }
    else {
        #ifdef _DEBUG_
        std::cerr << "curl_easy_init() could not be initiated." << std::endl;
        #endif
        return -1;
    }
}



short PushBullet::note(const std::string title, const std::string body) {
    std::stringstream data;
    std::string result;

    data << "{"
         << "\"type\":\"note\" , "
         << "\"title\":\"" << title << "\" , "
         << "\"body\":\""  << body  << "\""
         << "}";

    if (this->post_request(API_URL_PUSHES, &result, data.str()) != 0){
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

    if (this->post_request(API_URL_PUSHES, &result, data.str()) != 0){
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

    if (this->post_request(API_URL_PUSHES, &result, data.str()) != 0){
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

    if (this->post_request(API_URL_PUSHES, &result, data.str()) != 0){
        return -1;
    }

    #ifdef _DEBUG_
    std::cout << "Data send: "     << std::endl << data.str()   << std::endl;
    std::cout << "Response CURL: " << std::endl << result << std::endl;
    #endif

    return 0;

}


short PushBullet::get_all_devices(void) {
    std::string result;
    std::stringstream conversion;
    Json::Value json;               // will contain the root value after parsing.

    if (this->get_request(API_URL_DEVICES, &result) != 0){
        return -1;
    }

    /* Convert the string 'result' to be understand by the Json parser
    */
    conversion << result;
    conversion >> json;

    #ifdef _DEBUG_
    std::cout << "Response CURL: " << std::endl << result << std::endl;
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