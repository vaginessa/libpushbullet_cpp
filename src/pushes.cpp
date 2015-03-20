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