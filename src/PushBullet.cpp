#include "PushBullet.hpp"


PushBullet::PushBullet() {
    this->_tokenKey = "00000000000000000000000000000000";
}



PushBullet::PushBullet(const std::string tokenKey) {
    this->_tokenKey = tokenKey;
}



PushBullet::~PushBullet(void) {
}



const std::string PushBullet::get_token_key(void) {
    return this->_tokenKey;
}


#ifdef _DEBUG_
void PushBullet::display_token_key(void) {
    std::cout << "Token Key : " << this->get_token_key() << std::endl;
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


short PushBullet::link(std::string title, std::string body, std::string url) {
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


short PushBullet::list_devices(void) {
    std::string result;

    if (this->get_request(API_URL_DEVICES, &result) != 0){
        return -1;
    }

    #ifdef _DEBUG_
    std::cout << "Response CURL: " << std::endl << result << std::endl;
    // std::cout << "Accounts: " << d["devices"].GetString() << std::endl;
    #endif



    return 0;
}