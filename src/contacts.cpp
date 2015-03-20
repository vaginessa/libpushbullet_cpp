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

    this->download_contacts();

    return 0;
}



short PushBullet::update_contact(const std::string old_name, const std::string new_name) {
    std::stringstream data;
    std::stringstream request_url;
    std::string result;
    std::string iden;

    data << "{"
         << "\"name\" : \""  << new_name  << "\""
         << "}";

    if (!this->_contacts.count(old_name)) {
#ifdef _DEBUG_
        std::cerr << "SELECT_CONTACT > No contact is named \"" << old_name << "\"." << std::endl;
#endif
        return -1;
    }

    /* Get the identification number from the _contacts map.
    */
    iden = this->_contacts.at(old_name).second;

    request_url << API_URL_CONTACTS << "/" << iden;
    if (this->post_request(request_url.str(), &result, data.str()) != 0) {
#ifdef _DEBUG_
        std::cerr << "DELETE_CONTACT > Impossible to update the contact \"" << old_name << "\" to \""
                  << new_name << "\"." << std::endl;
#endif
        return -2;
    }

    /* Refresh the list of devices
     */
    this->download_contacts();
    return 0;
}



short PushBullet::delete_contact(const std::string name) {
    std::stringstream request_url;
    std::string result;
    std::string iden;

    if (!this->_contacts.count(name)) {
#ifdef _DEBUG_
        std::cerr << "SELECT_CONTACT > No contact is named \"" << name << "\"." << std::endl;
#endif
        return -1;
    }

    /* Get the identification number from the _contacts map.
    */
    iden = this->_contacts.at(name).second;


    request_url << API_URL_CONTACTS << "/" << iden;
    if (this->delete_request(request_url.str(), &result) != 0) {
#ifdef _DEBUG_
        std::cerr << "DELETE_CONTACT > Impossible to delete the contact \"" << name << "\"." << std::endl;
#endif
        return -2;
    }

    /* Refresh the list of devices
     */
    this->download_contacts();
    return 0;
}