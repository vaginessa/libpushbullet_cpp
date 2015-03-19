/**
 * @file PushBullet.cpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 *
 * @brief Methods relative to the different types of request
 *        POST, GET, DELETE
 */

#include "PushBullet.hpp"



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