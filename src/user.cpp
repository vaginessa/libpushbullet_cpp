/**
 * @file user.cpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 *
 * @brief Methods relative to the devices
 */

#include "PushBullet.hpp"



short PushBullet::download_user_informations(void)
{
    std::string result;
    Json::Value json;

    if (this->get_request(API_URL_ME, &result) != 0)
    {
        #ifdef _DEBUG_
        std::cerr << "GET_REQUEST > Impossible to ask for all user informations" << std::endl;
        #endif
        return -1;
    }

    std::stringstream(result) >> json;

    #ifdef _JSON_
    std::cout << "Json Document: " << std::endl << json   << std::endl;
    #endif

    /* Get the identification of the device corresponding to all of them
     */
    this->_all_iden = std::make_pair("All", json.get("iden", "null").asString());

    /* Get email of the user
     * Get name of the user
     * Get the url of his profile picture
     *
     */
    this->_email     = json.get("email", "null").asString();
    this->_name      = json.get("name", "null").asString();
    this->_url_photo = json.get("image_url", "null").asString();

    return 0;
}