#define BOOST_TEST_MAIN
#define BOOST_TEST_STATIC_LINK
#define BOOST_TEST_MODULE testMain
#include <boost/test/unit_test.hpp>
#include "../src/version.hpp"

BOOST_AUTO_TEST_CASE( testMain ) {
    BOOST_TEST_MESSAGE( "TEST_CASE testMain " << VERSION_INFO );
    BOOST_CHECK_EQUAL(1, 1);
}
