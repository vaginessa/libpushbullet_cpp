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

#define USER_NAME_TRUE  "Henri Buyse"
#define USER_NAME_FALSE "Henri Henri"


BOOST_AUTO_TEST_CASE(test_apikey) {
    /* Set up a PushBullet account
     */
    PushBullet pb(APIKEY_TRUE);

    BOOST_CHECK(pb.get_token_key() != APIKEY_FALSE);
    BOOST_CHECK(pb.get_token_key() == APIKEY_TRUE);
}


BOOST_AUTO_TEST_CASE(test_user_name) {
    /* Set up a PushBullet account
     */
    PushBullet pb(APIKEY_TRUE);
    pb.get_user_informations();

    BOOST_CHECK(pb.get_user_name() != USER_NAME_FALSE);
    BOOST_CHECK(pb.get_user_name() == USER_NAME_TRUE);
}