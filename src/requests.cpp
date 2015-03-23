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



short PushBullet::upload_request(const std::string path, Json::Value *json_request) {
    char buff[SIZE_BUFF];
    FILE* fp;
    std::stringstream data;
    std::string file_name, file_type, result;       // file_type corresponds to MIME type

    /* REGEXS
     */
    boost::regex regex(MIME_TYPE_PATTERN, boost::regex::extended);
    boost::match_results<std::string::const_iterator> sm;

    /* Get the name of the file
     */
    file_name = basename( strdup(path.c_str()) );

    /* Get the MIME type of the file
     * using the system command `file`
     */
    data << "file -i " << path;

    fp = popen(data.str().c_str(), "r");
    if (fp == NULL) {
#ifdef _DEBUG_
        std::cerr << "Failed to run command \"" << data.str() << "\"."<< std::endl;
#endif
        return -2;
    }

    if ( (fgets(buff, sizeof(buff), fp) != NULL) && (boost::regex_match(std::string(buff), sm, regex)) ) {
        file_type = sm[1];
    }
    else {
        file_type = "text/plain";
    }

    pclose(fp);

    data.str(std::string());
    data << "{"
         << "\"file_name\" : \"" << file_name << "\", "
         << "\"file_type\" : \"" << file_type << "\""
         << "}";

    if (this->post_request(API_URL_FILE_REQUEST, &result, data.str()) != 0) {
#ifdef _DEBUG_
        std::cerr << "POST_REQUEST > Impossible to send a file request" << std::endl;
#endif
        return -1;
    }

    /* Need to return the dictionary
     */
    std::stringstream(result) >> *json_request;

#ifdef _DEBUG_
    Json::Value json;

    data >> json;
    std::cout << "Data send: "     << std::endl << json << std::endl;
    std::stringstream(result) >> json;
    std::cout << "Response CURL: " << std::endl << json << std::endl;
#endif

    return 0;
}


/*
curl -i -X POST https://s3.amazonaws.com/pushbullet-uploads \
  -F awsaccesskeyid=AKIAJJIUQPUDGPM4GD3W \
  -F acl=public-read \
  -F key=ubd-CWb1dP5XrZzvHReWHCycIwPyuAMp2R9I/image.png \
  -F signature=UX5s1uIy1ov6+xlj58JY7rGFKcs= \
  -F policy=eyKjb25kaXRpb25z6MzcuMjM0MTMwWiJ9 \
  -F content-type=image/png
  -F file=@test.txt
 */
short PushBullet::form_request(const std::string url_request, const Json::Value data, const std::string path,
                               std::string *result ) {
    /*  Documentation on CURL for C can be found at http://curl.haxx.se/libcurl/c/
     */

    /*  Start a libcurl easy session
    */
    CURL *s;
    CURLcode res;

    struct curl_httppost *formpost=NULL;
    struct curl_httppost *lastptr=NULL;
    struct curl_slist *headerlist=NULL;

    curl_global_init(CURL_GLOBAL_ALL);

    /* Fill in all form datas
    //  */
    // for( Json::ValueIterator itr = data.begin() ; itr != data.end() ; itr++ ) {
    //     std::stringstream tmp;
    //     tmp << "\"" << itr.key().asString() << "\"";

    //     curl_formadd(&formpost,
    //                  &lastptr,
    //                  CURLFORM_COPYNAME, tmp.str().c_str(),
    //                  CURLFORM_COPYCONTENTS, std::string(itr->asString()).c_str(),
    //                  CURLFORM_END);
    // }

    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "awsaccesskeyid",
                 CURLFORM_COPYCONTENTS, std::string(data["awsaccesskeyid"].asString()).c_str(),
                 CURLFORM_END);

    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "acl",
                 CURLFORM_COPYCONTENTS, std::string(data["acl"].asString()).c_str(),
                 CURLFORM_END);

    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "key",
                 CURLFORM_COPYCONTENTS, std::string(data["key"].asString()).c_str(),
                 CURLFORM_END);

    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "signature",
                 CURLFORM_COPYCONTENTS, std::string(data["signature"].asString()).c_str(),
                 CURLFORM_END);

    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "policy",
                 CURLFORM_COPYCONTENTS, std::string(data["policy"].asString()).c_str(),
                 CURLFORM_END);

    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "content-type",
                 CURLFORM_COPYCONTENTS, std::string(data["content-type"].asString()).c_str(),
                 CURLFORM_END);

    /* Fill in the file upload field
     */
    std::stringstream tmp;
    tmp << "@" << path;
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "file",
                 CURLFORM_FILE, tmp.str().c_str(),
                 CURLFORM_FILE, path.c_str(),
                 CURLFORM_END);


    /* Initialize the session
     */
    s = curl_easy_init();
    if (s) {
        CURLcode r = CURLE_OK;
        curl_slist *http_headers = NULL;

        http_headers = curl_slist_append(http_headers, "Expect:");
        curl_easy_setopt(s, CURLOPT_URL, url_request.c_str());
        curl_easy_setopt(s, CURLOPT_HTTPPOST, formpost);

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
        curl_formfree(formpost);
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