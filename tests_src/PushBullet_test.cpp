/**
 * @file PushBullet.cpp
 * @author Henri Buyse <a href="mailto:henri.buyse@gmail.com">henri.buyse@gmail.com</a>
 *
 * @brief Tests PushBullet's methods
 */

#include "PushBullet.hpp"

#define BOOST_TEST_MODULE "Test the PushBullet class"
#include <boost/test/included/unit_test.hpp>

#define APIKEY_TRUE  "YpiQLDdMfEkhAFabFZbNwAq8FVcBVGWn"
#define APIKEY_FALSE "00000000000000000000000000000000"

#define EMPTY_API_KEY_TRUE "00000000000000000000000000000000"
#define EMPTY_API_KEY_FALSE "YpiQLDdMfEkhAFabFZbNwAq8FVcBVGWn"

#define USER_NAME_TRUE  "Henri Buyse"
#define USER_NAME_FALSE "Henri Henri"

 #define USER_EMAIL_TRUE  "henri.buyse@gmail.com"
 #define USER_EMAIL_FALSE "henri.henri@gmail.com"

 #define URL_PHOTO_TRUE  "https://lh4.googleusercontent.com/-c1xHwAnpR8g/AAAAAAAAAAI/AAAAAAAACQo/Mfe5hxqtoJI/photo.jpg"
 #define URL_PHOTO_FALSE "https://www.google.fr"


BOOST_AUTO_TEST_CASE(test_apikey) {
    /* Set up PushBullet accounts
     */
    PushBullet pb(APIKEY_TRUE);
    PushBullet pb2;

    /* Test normal PushBullet Account
     */
    BOOST_CHECK(pb.get_token_key()  != APIKEY_FALSE);
    BOOST_CHECK(pb.get_token_key()  == APIKEY_TRUE);

    /* Test empty PushBullet account
     */
    BOOST_CHECK(pb2.get_token_key() != EMPTY_API_KEY_FALSE);
    BOOST_CHECK(pb2.get_token_key() == EMPTY_API_KEY_TRUE);
}


BOOST_AUTO_TEST_CASE(test_user_name) {
    /* Set up a PushBullet account
     */
    PushBullet pb(APIKEY_TRUE);
    pb.get_user_informations();

    BOOST_CHECK(pb.get_user_name() != USER_NAME_FALSE);
    BOOST_CHECK(pb.get_user_name() == USER_NAME_TRUE);
}



BOOST_AUTO_TEST_CASE(test_user_mail) {
    /* Set up a PushBullet account
     */
    PushBullet pb(APIKEY_TRUE);
    pb.get_user_informations();

    BOOST_CHECK(pb.get_user_email() != USER_EMAIL_FALSE);
    BOOST_CHECK(pb.get_user_email() == USER_EMAIL_TRUE);
}



BOOST_AUTO_TEST_CASE(test_user_profile_picture) {
    /* Set up a PushBullet account
     */
    PushBullet pb(APIKEY_TRUE);
    pb.get_user_informations();

    BOOST_CHECK(pb.get_user_email() != USER_EMAIL_FALSE);
    BOOST_CHECK(pb.get_user_email() == USER_EMAIL_TRUE);
}
