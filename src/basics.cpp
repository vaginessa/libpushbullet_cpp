/**
 * @file basics.cpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 *
 * @brief Constructors, destructor, getters, setters and displayers
 */

#include "PushBullet.hpp"



PushBullet::PushBullet() : _tokenKey("00000000000000000000000000000000")
{
}



PushBullet::PushBullet(const std::string tokenKey) : _tokenKey(tokenKey)
{
}



PushBullet::PushBullet(const PushBullet& p)
{
    /* Copy the principal thing : token key
     */
    this->_tokenKey = p.get_token_key();
}



PushBullet::~PushBullet(void)
{
}



std::string PushBullet::get_token_key(void) const
{
    return this->_tokenKey;
}



std::string PushBullet::get_user_name(void) const
{
    return this->_name;
}



std::string PushBullet::get_user_email(void) const
{
    return this->_email;
}



std::string PushBullet::get_user_url_photo(void) const
{
    return this->_url_photo;
}



std::string PushBullet::get_iden_from_name(std::string name) const
{
    if (this->_devices.count(name))
    {
        return this->_devices.find(name)->second;
    }
    else if (this->_contacts.count(name))
    {
        return this->_contacts.find(name)->second.second;
    }
    else
    {
        return std::string();
    }
}



void PushBullet::display_token_key(void) const
{
    std::cout << "Token Key : " << this->get_token_key() << std::endl;
}



void PushBullet::display_devices(void)
{
    std::cout   << std::endl
                << "Device:" << std::endl;

    for (auto& x: this->_devices)
    {
        std::cout << "    " << x.first << " [" << x.second << "]" << std::endl;
    }
}



void PushBullet::display_contacts(void)
{
    std::pair<std::string, std::string> val;

    std::cout << std::endl
              << "Contacts:" << std::endl;

    for (auto& x: this->_contacts)
    {
        val = this->_contacts[x.first];
        std::cout << "    " << x.first << " - " << val.first << " [" << val.second << "]" << std::endl;
    }
}



void PushBullet::display_user_informations(void) const
{
    std::cout   << std::endl
                << "User informations:" << std::endl
                << "    Name:      " << this->get_user_name() << std::endl
                << "    API token: " << this->get_token_key() << std::endl
                << "    Email:     " << this->get_user_email() << std::endl
                << "    URL photo: " << this->get_user_url_photo() << std::endl;
}