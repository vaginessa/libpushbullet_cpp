/**
 * @file devices.cpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 *
 * @brief Methods relative to the devices
 */

#include "PushBullet.hpp"



short PushBullet::download_all_devices(void) {
    std::string result;
    std::stringstream conversion;
    Json::Value json;               // will contain the root value after parsing.

    /* Free the device map
     */
    this->_devices.clear();

    if (this->get_request(API_URL_DEVICES, &result) != 0) {
#ifdef _DEBUG_
        std::cerr << "GET_REQUEST > Impossible to ask for all devices" << std::endl;
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
    const Json::Value devices = json["devices"];
    for (int index = 0; index < (int)devices.size(); ++index) {
        /* Check if the device is still active
         * If it is, we add it in the list of devices.
         */
        if (devices[index].get("active", false).asBool()) {
            this->_devices.insert(std::make_pair(devices[index].get("nickname", "null").asString(),
                                                 devices[index].get("iden", "null").asString()));
        }
    }

    return 0;
}


/* curl --header 'Authorization: Bearer <your_access_token_here>' -X POST
 * https://api.pushbullet.com/v2/devices -d nickname=stream_device -d type=stream
 */
short PushBullet::create_device_if_not_existing(void) {
    /* Structure that will contain informations about the computer.
    */
    struct utsname buffer;

    std::stringstream data;
    std::string result;

    /* File that contains informations about the Linux distribution and its distribution.
    */
    std::ifstream lsb_release("/etc/lsb-release", std::ifstream::in);
    std::string line;
    std::string model, nickname, type;

    /* REGEXS
    */
    boost::regex regex(DISTRIB_DESCRIPTION_PATTERN, boost::regex::extended);
    boost::match_results<std::string::const_iterator> sm;

    /*  Get informations about the computer
    */
    if (uname(&buffer) != 0) {
#ifdef _DEBUG_
        std::cerr << "UNAME > Impossible to get the informations about the computer!" << std::endl;
#endif
        return -2;
    }


    /* Store the strings
    */
    nickname = std::string(buffer.nodename);
    type = std::string(buffer.sysname);
    std::transform(type.begin(), type.end(), type.begin(), ::tolower); // Convert to lower
    model = std::string(buffer.sysname) + '-' + std::string(buffer.release);


    /* Try to open the file /etc/release to get the model (OS Version)
     */
    if (lsb_release.is_open()) {
        while (getline(lsb_release, line)) {
            if (boost::regex_match(line, sm, regex)) {
                model = sm[1];
            }
        }
        lsb_release.close();
    }

    if (this->_devices.count(nickname)) {
#ifdef _DEBUG_
        std::cerr << "FIND > This device already exists in your account. No need to create a new one." << std::endl;
#endif
        return 1;
    }

    data << "{"
         << "\"nickname\" : \"" << nickname << "\", "
         << "\"model\" : \""    << model    << "\", "
         << "\"type\" : \""     << type     << "\", "
         << "\"icon\" : \"desktop\""
         << "}";

    if (this->post_request(API_URL_DEVICES, &result, data.str()) != 0){
#ifdef _DEBUG_
        std::cerr << "POST_REQUEST > Impossible to create a new device." << std::endl;
#endif
        return -1;
    }

    /* Refresh the list of devices
     */
    this->download_all_devices();

    return 0;
}


/* curl --header 'Authorization: Bearer <your_access_token_here>'
 * -X DELETE https://api.pushbullet.com/v2/devices/u1qSJddxeKwOGuGW
 */
short PushBullet::delete_device(const std::string nickname) {
    std::stringstream request_url;
    std::string result;
    std::string iden;

    if (!this->_devices.count(nickname)) {
#ifdef _DEBUG_
        std::cerr << "SELECT_DEVICE > No device that is named " << nickname << "." << std::endl;
#endif
        return -1;
    }

    /* Get the identification number from the _devices map.
    */
    iden = this->_devices.at(nickname);

    request_url << API_URL_DEVICES << "/" << iden;
    if (this->delete_request(request_url.str(), &result) != 0) {
#ifdef _DEBUG_
        std::cerr << "DELETE > Impossible to create a new device." << std::endl;
#endif
        return -2;
    }

    /* Refresh the list of devices
     */
    this->download_all_devices();

    return 0;
}