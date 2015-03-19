/**
 * @file PushBullet.cpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 *
 * @brief Methods of the class PushBullet
 */

#include "PushBullet.hpp"



PushBullet::PushBullet() {
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini(PUSHBULLET_INI, pt);

    this->_tokenKey = pt.get<std::string>(TOKEN_NODE);
}



PushBullet::PushBullet(const PushBullet& p) {
    /* Copy the principal thing : token key
     */
    this->_tokenKey = p.get_token_key();
}



PushBullet::~PushBullet(void) {
}



std::string PushBullet::get_token_key(void) const {
    return this->_tokenKey;
}



std::string PushBullet::get_user_name(void) const {
    return this->_name;
}



std::string PushBullet::get_user_email(void) const {
    return this->_email;
}



std::string PushBullet::get_user_url_photo(void) const {
    return this->_url_photo;
}



void PushBullet::display_token_key(void) const {
    std::cout << "Token Key : " << this->get_token_key() << std::endl;
}



void PushBullet::display_devices(void) {
    std::cout << std::endl
              << "Device: " << std::endl
              << "    " << this->_all_iden.first << " [" << this->_all_iden.second << "]" << std::endl;

    for (auto& x: this->_devices) {
        std::cout << "    " << x.first << " [" << x.second << "]" << std::endl;
    }
}



void PushBullet::display_contacts(void) {
    std::pair<std::string, std::string> val;

    std::cout << "Contact: " << std::endl;
    for (auto& x: this->_contacts) {
        val = this->_contacts[x.first];
        std::cout << "    " << x.first << " - " << val.first << " [" << val.second << "]" << std::endl;
    }
}



void PushBullet::display_user_informations(void) const {
    std::cout << std::endl
              << "User informations:" << std::endl
              << "    Name:      " << this->get_user_name() << std::endl
              << "    API token: " << this->get_token_key() << std::endl
              << "    Email:     " << this->get_user_email() << std::endl
              << "    URL photo: " << this->get_user_url_photo() << std::endl;
}