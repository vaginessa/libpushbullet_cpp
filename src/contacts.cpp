/**
 * @file contacts.cpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 *
 * @brief Methods relative to the contacts
 */

#include "PushBullet.hpp"



short PushBullet::download_contacts(void) {
    std::string result;
    std::stringstream conversion;
    Json::Value json;               // will contain the root value after parsing.

    /* Free the device map
     */
    this->_contacts.clear();

    if (this->get_request(API_URL_CONTACTS, &result) != 0) {
#ifdef _DEBUG_
        std::cerr << "GET_REQUEST > Impossible to ask for the user's contacts" << std::endl;
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
    const Json::Value contacts = json["contacts"];
    for (int index = 0; index < (int)contacts.size(); ++index) {
        /* Check if the device is still active
         * If it is, we add it in the list of devices.
         */
        if (contacts[index].get("active", false).asBool()) {
            this->_contacts.insert(std::make_pair(contacts[index].get("name",  "null").asString(),
                                   std::make_pair(contacts[index].get("email", "null").asString(),
                                                  contacts[index].get("iden", "null").asString())));
        }
    }

    return 0;
}



short PushBullet::create_contact(const std::string name, const std::string email) {
    std::stringstream data;
    std::string result;

    data << "{"
         << "\"name\" : \""  << name  << "\", "
         << "\"email\" : \"" << email << "\""
         << "}";

    if (this->post_request(API_URL_CONTACTS, &result, data.str()) != 0) {
#ifdef _DEBUG_
        std::cerr << "POST_REQUEST > Impossible to add the contact" << name << std::endl;
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