/**
 * @file pushes.cpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 *
 * @brief Methods relative to pushes
 */

#include "PushBullet.hpp"



short PushBullet::note(const std::string    title,
                       const std::string    body
                       )
{
    std::stringstream       data;
    std::string             result;


    data    << "{"
            << "\"type\":\"note\" , "
            << "\"title\":\"" << title << "\" , "
            << "\"body\":\"" << body << "\""
            << "}";

    if ( this->post_request(API_URL_PUSHES, &result, data.str() ) != 0 )
    {
        #ifdef __DEBUG__
        std::cerr << "POST_REQUEST > Impossible to send a note" << std::endl;
        #endif

        return (-1);
    }

    #ifdef __DEBUG__
    Json::Value     json;

    data >> json;
    std::cout << "Data send: " << std::endl << json << std::endl;
    std::stringstream(result) >> json;
    std::cout << "Response CURL: " << std::endl << json << std::endl;
    #endif

    return (0);
}



short PushBullet::note(const std::string    title,
                       const std::string    body,
                       const std::string    iden
                       )
{
    std::stringstream       data;
    std::string             result;


    // If the user tries to use a empty iden, we send to all the devices.
    if ( iden.empty() )
    {
        return (this->note(title, body) );
    }

    data    << "{"
            << "\"device_iden\":\"" << iden << "\", "
            << "\"type\":\"note\", "
            << "\"title\":\"" << title << "\", "
            << "\"body\":\"" << body << "\""
            << "}";

    if ( this->post_request(API_URL_PUSHES, &result, data.str() ) != 0 )
    {
        #ifdef __DEBUG__
        std::cerr << "POST_REQUEST > Impossible to send a note" << std::endl;
        #endif

        return (-1);
    }

    #ifdef __DEBUG__
    Json::Value     json;

    data >> json;
    std::cout << "Data send: " << std::endl << json << std::endl;
    std::stringstream(result) >> json;
    std::cout << "Response CURL: " << std::endl << json << std::endl;
    #endif

    return (0);
}



short PushBullet::link(const std::string    title,
                       const std::string    body,
                       const std::string    url
                       )
{
    std::stringstream       data;
    std::string             result;


    data    << "{"
            << "\"type\":\"link\", "
            << "\"title\":\"" << title << "\", "
            << "\"body\":\"" << body << "\", "
            << "\"url\":\"" << url << "\""
            << "}";

    if ( this->post_request(API_URL_PUSHES, &result, data.str() ) != 0 )
    {
        #ifdef __DEBUG__
        std::cerr << "POST_REQUEST > Impossible to send a link" << std::endl;
        #endif

        return (-1);
    }

    #ifdef __DEBUG__
    Json::Value     json;

    data >> json;
    std::cout << "Data send: " << std::endl << json << std::endl;
    std::stringstream(result) >> json;
    std::cout << "Response CURL: " << std::endl << json << std::endl;
    #endif

    return (0);
}



short PushBullet::link(const std::string    title,
                       const std::string    body,
                       const std::string    url,
                       const std::string    iden
                       )
{
    std::stringstream       data;
    std::string             result;


    // If the user tries to use a empty iden, we send to all the devices.
    if ( iden.empty() )
    {
        return (this->link(title, body, url) );
    }

    data    << "{"
            << "\"device_iden\":\"" << iden << "\", "
            << "\"type\":\"link\", "
            << "\"title\":\"" << title << "\", "
            << "\"body\":\"" << body << "\", "
            << "\"url\":\"" << url << "\""
            << "}";

    if ( this->post_request(API_URL_PUSHES, &result, data.str() ) != 0 )
    {
        #ifdef __DEBUG__
        std::cerr << "POST_REQUEST > Impossible to send a link" << std::endl;
        #endif

        return (-1);
    }

    #ifdef __DEBUG__
    Json::Value     json;

    data >> json;
    std::cout << "Data send: " << std::endl << json << std::endl;
    std::stringstream(result) >> json;
    std::cout << "Response CURL: " << std::endl << json << std::endl;
    #endif

    return (0);
}



short PushBullet::file(const std::string    title,
                       const std::string    body,
                       const std::string    path
                       )
{
    Json::Value     json_request;
    std::string     result;
    std::stringstream     data;


    if ( this->upload_request(path, &json_request) < 0 )
    {
        #ifdef __DEBUG__
        std::cerr << "UPLOAD_REQUEST > Could not get an upload URL and all datas needed to upload the file." <<
        std::endl;
        #endif

        return (-1);
    }

    /* Get the dictionary 'data'
     */
    const Json::Value     data_json = json_request["data"];

    if ( this->form_request(json_request["upload_url"].asString(), data_json, path, &result) < 0 )
    {
        #ifdef __DEBUG__
        std::cerr << "Could not get a reply from " << json_request["upload_url"].asString() << std::endl;
        #endif

        return (-1);
    }

    data    << "{"
            << "\"type\":\"file\", "
            << "\"file_name\":\"" << json_request["file_name"].asString() << "\", "
            << "\"file_type\":\"" << json_request["file_type"].asString() << "\", "
            << "\"title\":\"" << title << "\", "
            << "\"body\":\"" << body << "\", "
            << "\"file_url\":\"" << json_request["file_url"].asString() << "\""
            << "}";

    if ( this->post_request(API_URL_PUSHES, &result, data.str() ) != 0 )
    {
        #ifdef __DEBUG__
        std::cerr << "POST_REQUEST > Impossible to send a file" << std::endl;
        #endif

        return (-1);
    }

    #ifdef __DEBUG__
    Json::Value     json;

    data >> json;
    std::cout << "Data send: " << std::endl << json << std::endl;
    std::stringstream(result) >> json;
    std::cout << "Response CURL: " << std::endl << json << std::endl;
    #endif

    return (0);
}



short PushBullet::list_pushes(void)
{
    std::string     result;


    if ( this->get_request(API_URL_PUSHES, &result) != 0 )
    {
        #ifdef __DEBUG__
        std::cerr << "GET_REQUEST > Impossible to ask for all pushes" << std::endl;
        #endif

        return (-1);
    }

    #ifdef _JSON_
    Json::Value     json;
    std::stringstream(result) >> json;

    std::cout << "Json Document: " << std::endl << json["pushes"] << std::endl;
    #endif

    return (0);
}



short PushBullet::update_push(const std::string push_iden,
                              const bool        dismissed
                              )
{
    std::stringstream       data;
    std::string             result;
    std::stringstream       url_request;


    data    << "{"
            << "\"dismissed\" : " << ( (dismissed) ? "true" : "false")
            << "}";

    url_request << API_URL_PUSHES << "/" << push_iden;

    if ( this->post_request(url_request.str(), &result, data.str() ) != 0 )
    {
        #ifdef __DEBUG__
        std::cerr << "POST_REQUEST > Impossible to modify the push " << push_iden << "." << std::endl;
        #endif

        return (-1);
    }

    #ifdef _JSON_
    Json::Value     json;
    std::stringstream(result) >> json;

    std::cout << "Json Document: " << std::endl << json << std::endl;
    #endif

    return (0);
}



short PushBullet::delete_push(const std::string push_iden)
{
    std::stringstream       url_request;
    std::string             result;


    url_request << API_URL_PUSHES << "/" << push_iden;

    if ( this->delete_request(url_request.str(), &result) != 0 )
    {
        #ifdef __DEBUG__
        std::cerr << "POST_REQUEST > Impossible to delete the push " << push_iden << "." << std::endl;
        #endif

        return (-1);
    }

    return (0);
}



short PushBullet::delete_all_pushes(void)
{
    std::string     result;


    if ( this->delete_request(API_URL_PUSHES, &result) != 0 )
    {
        #ifdef __DEBUG__
        std::cerr << "POST_REQUEST > Impossible to delete all pushes." << std::endl;
        #endif

        return (-1);
    }

    return (0);
}