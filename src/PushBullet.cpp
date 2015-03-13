#include "PushBullet.hpp"


PushBullet::PushBullet() {
    _tokenKey = "00000000000000000000000000000000";
}



PushBullet::PushBullet(const char* tokenKey) {
    _tokenKey = tokenKey;
}



PushBullet::~PushBullet() {
}



const char* PushBullet::getToken() {
    return _tokenKey;
}



void PushBullet::display() {
    cout << "Token Key : " << _tokenKey << endl;
}


short PushBullet::pushing(char* data) {
    /*  Documentation on CURL for C can be found at http://curl.haxx.se/libcurl/c/
     */

    /*  Start a libcurl easy session
    */
    CURL *s = curl_easy_init();

    if (s) {
        CURLcode r;
        curl_slist *http_headers = NULL;

        http_headers = curl_slist_append(http_headers, "Content-Type: application/json");

        /*  Set options for a curl easy handle
        */
        curl_easy_setopt(s, CURLOPT_URL, API_URL_PUSHES);
        curl_easy_setopt(s, CURLOPT_USERPWD, _tokenKey);
        curl_easy_setopt(s, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(s, CURLOPT_HTTPHEADER, http_headers);

        r = curl_easy_perform(s);

        curl_easy_cleanup(s);
        curl_slist_free_all(http_headers);

        return 0;
    }
    else {
        return -1;
    }
}