/**
 * @file PushBullet.cpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 *
 * @brief Tests PushBullet's methods
 */

#include "PushBullet.hpp"

#define BOOST_TEST_MODULE "Test the PushBullet class"
#include <boost/test/included/unit_test.hpp>


#define APIKEY_TRUE "YpiQLDdMfEkhAFabFZbNwAq8FVcBVGWn"
#define APIKEY_FALSE "00000000000000000000000000000000"
BOOST_AUTO_TEST_CASE(test_apikey) {
    /* Set up PushBullet accounts
     */
    PushBullet pb(APIKEY_FALSE);
    PushBullet pb2(APIKEY_TRUE);
    PushBullet pb3 = pb;

    /* Test normal PushBullet Account
     */
    BOOST_CHECK(pb.get_token_key()  != APIKEY_TRUE);
    BOOST_CHECK(pb.get_token_key()  == APIKEY_FALSE);
    BOOST_CHECK(pb2.get_token_key() != APIKEY_FALSE);
    BOOST_CHECK(pb2.get_token_key() == APIKEY_TRUE);
    BOOST_CHECK(pb3.get_token_key() != APIKEY_TRUE);
    BOOST_CHECK(pb3.get_token_key() == APIKEY_FALSE);
}



#define USER_NAME_TRUE  "Henri Buyse"
#define USER_NAME_FALSE "Henri Henri"
BOOST_AUTO_TEST_CASE(test_user_name) {
    /* Set up a PushBullet account
     */
    PushBullet pb(APIKEY_TRUE);

    pb.download_user_informations();

    BOOST_CHECK(pb.get_user_name() != USER_NAME_FALSE);
    BOOST_CHECK(pb.get_user_name() == USER_NAME_TRUE);
}



#define USER_EMAIL_TRUE  "henri.buyse@gmail.com"
#define USER_EMAIL_FALSE "henri.henri@gmail.com"
BOOST_AUTO_TEST_CASE(test_user_mail) {
    /* Set up a PushBullet account
     */
    PushBullet pb(APIKEY_TRUE);

    pb.download_user_informations();

    BOOST_CHECK(pb.get_user_email() != USER_EMAIL_FALSE);
    BOOST_CHECK(pb.get_user_email() == USER_EMAIL_TRUE);
}



#define URL_PHOTO_TRUE  "https://lh4.googleusercontent.com/-c1xHwAnpR8g/AAAAAAAAAAI/AAAAAAAACQo/Mfe5hxqtoJI/photo.jpg"
#define URL_PHOTO_FALSE "https://www.google.fr"
BOOST_AUTO_TEST_CASE(test_user_profile_picture) {
    /* Set up a PushBullet account
     */
    PushBullet pb(APIKEY_TRUE);

    pb.download_user_informations();

    BOOST_CHECK(pb.get_user_email() != USER_EMAIL_FALSE);
    BOOST_CHECK(pb.get_user_email() == USER_EMAIL_TRUE);
}



#define IDEN_ALL         "ujEIL5AaxhY"
#define IDEN_BUYSE       "ujEIL5AaxhYsjAorTPTBtY"
#define IDEN_FIREFOX     "ujEIL5AaxhYsjzWIEVDzOK"
#define IDEN_LGE_NEXUS_4 "ujEIL5AaxhYsjAiVsKnSTs"
BOOST_AUTO_TEST_CASE(test_iden_from_name) {
    /* Set up a PushBullet account
     */
    PushBullet pb(APIKEY_TRUE);

    pb.download_user_informations();
    pb.download_all_devices();

    BOOST_CHECK(pb.get_iden_from_name()              == IDEN_ALL);
    BOOST_CHECK(pb.get_iden_from_name("")            == IDEN_ALL);
    BOOST_CHECK(pb.get_iden_from_name("Test")        == IDEN_ALL);
    BOOST_CHECK(pb.get_iden_from_name("All")         == IDEN_ALL);
    BOOST_CHECK(pb.get_iden_from_name("all")         == IDEN_ALL);
    BOOST_CHECK(pb.get_iden_from_name("BUYSE")       == IDEN_BUYSE);
    BOOST_CHECK(pb.get_iden_from_name("BUYe")        == IDEN_ALL);
    BOOST_CHECK(pb.get_iden_from_name("Firefox")     == IDEN_FIREFOX);
    BOOST_CHECK(pb.get_iden_from_name("firefox")     == IDEN_ALL);
    BOOST_CHECK(pb.get_iden_from_name("LGE Nexus 4") == IDEN_LGE_NEXUS_4);
    BOOST_CHECK(pb.get_iden_from_name("Lge Nexus 4") == IDEN_ALL);
}