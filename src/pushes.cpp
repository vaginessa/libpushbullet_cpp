/**
 * @file pushes.cpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 *
 * @brief Methods relative to pushes
 */

#include "PushBullet.hpp"



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
    Json::Value json;

    data >> json;
    std::cout << "Data send: "     << std::endl << json << std::endl;
    std::stringstream(result) >> json;
    std::cout << "Response CURL: " << std::endl << json << std::endl;
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
    Json::Value json;

    data >> json;
    std::cout << "Data send: "     << std::endl << json << std::endl;
    std::stringstream(result) >> json;
    std::cout << "Response CURL: " << std::endl << json << std::endl;
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
    Json::Value json;

    data >> json;
    std::cout << "Data send: "     << std::endl << json << std::endl;
    std::stringstream(result) >> json;
    std::cout << "Response CURL: " << std::endl << json << std::endl;
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
    Json::Value json;

    data >> json;
    std::cout << "Data send: "     << std::endl << json << std::endl;
    std::stringstream(result) >> json;
    std::cout << "Response CURL: " << std::endl << json << std::endl;
#endif

    return 0;
}



short PushBullet::file_request(const std::string path, Json::Value *json_request) {
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



short PushBullet::file(const std::string path) {
    Json::Value json_request;

    if (this->file_request(path, &json_request) < 0) {
#ifdef _DEBUG_
        std::cerr << "Could not get a reply from " << std::endl;
#endif
        return -1
    }

    return 0;
}