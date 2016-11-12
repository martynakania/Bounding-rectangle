#include "point.h"
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(PointTests)

BOOST_AUTO_TEST_CASE(getting_x)
{
    Point<int> p1(1,2);
    BOOST_CHECK( p1.get_x()==1 );
}
BOOST_AUTO_TEST_CASE(getting_y)
{
    Point <int>point1(1,2);
    BOOST_CHECK( point1.get_y()==2 );
}

BOOST_AUTO_TEST_CASE(setting_x)
{
    Point <int>point1(0,0);
    point1.set_x(1);
    BOOST_CHECK( point1.get_x()==1 );
}

BOOST_AUTO_TEST_CASE(seting_y)
{
    Point <int>point1(0,0);
    point1.set_y(2);
    BOOST_CHECK( point1.get_y()==2 );
}


BOOST_AUTO_TEST_SUITE_END()
