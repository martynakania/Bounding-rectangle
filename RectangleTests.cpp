#include "rectangle.h"
#include <boost/test/unit_test.hpp>

using namespace Projekt;

BOOST_AUTO_TEST_SUITE (RectangleTests)

BOOST_AUTO_TEST_CASE (constructes_Rectangle_Set_smaller_x_and_y_as_left_uppon_corner_and_bigger_as_top_right)
{
    Point <int>p1(3,6), p2(1,4), p3(1,2), p4(3,4);
    Rectangle<int> r1(p1,p2), r2(p3,p4);
    BOOST_CHECK_EQUAL(r1.get_x_left(), 1);
    BOOST_CHECK_EQUAL(r1.get_x_right(), 3);
    BOOST_CHECK_EQUAL(r1.get_y_bottom(), 4);
    BOOST_CHECK_EQUAL(r1.get_y_top(), 6);

    BOOST_CHECK_EQUAL(r2.get_x_left(), 1);
    BOOST_CHECK_EQUAL(r2.get_x_right(), 3);
    BOOST_CHECK_EQUAL(r2.get_y_bottom(), 2);
    BOOST_CHECK_EQUAL(r2.get_y_top(), 4);
}


BOOST_AUTO_TEST_CASE (getting_width_of_rectangle)
{
    Point <int> p1(1,2), p2(3,4);
    Rectangle<int> rectangleTemp(p1,p2);
    BOOST_CHECK( rectangleTemp.get_width()==2 );
}

BOOST_AUTO_TEST_CASE (getting_width_of_rectangle_which_is_a_point)
{
    Point <int> p1(1,2);
    Rectangle<int> rectangleTemp(p1,p1);
    BOOST_CHECK( rectangleTemp.get_width()==0 );
}

BOOST_AUTO_TEST_CASE (getting_length_of_rectangle)
{
    Point <int> p1(1,2), p2(3,4);
    Rectangle<int> rectangleTemp(p1,p2);
    BOOST_CHECK( rectangleTemp.get_length()==2 );
}

BOOST_AUTO_TEST_CASE (geting_length_of_rectangle_which_is_a_point)
{
    Point <int> p1(1,2);
    Rectangle<int> rectangleTemp(p1,p1);
    BOOST_CHECK( rectangleTemp.get_length()==0 );
}

BOOST_AUTO_TEST_CASE (setting_x_coordinates)
{
    Point <int> p1(1,2), p2(3,4), p3(3,4), p4(2,2), p5(5,2);
    Rectangle<int> rectangleTemp(p1,p2);
    rectangleTemp.set_x(5,3);//3,2,5,4
    BOOST_CHECK( rectangleTemp==Rectangle<int>(p3,p5) );

    rectangleTemp.set_x(2,3);//3,2,2,4
    BOOST_CHECK( rectangleTemp==Rectangle<int>(p3,p4) );
}

BOOST_AUTO_TEST_CASE( setting_y_coordinates)
{
    Point <int> p1(1,2), p2(3,4), p4(3,3), p5(1,5);
    Rectangle<int> rectangleTemp(p1,p2);
    rectangleTemp.set_y(5,3);
    BOOST_CHECK( rectangleTemp==Rectangle<int>(p4,p5) );

    rectangleTemp.set_y(2,3);
    BOOST_CHECK( rectangleTemp==Rectangle<int>(p1,p4) );
}


BOOST_AUTO_TEST_CASE( comparing_the_same_rectangles)
{
    Point <int> p1(1,4), p2(3,6);
    Rectangle<int> r1(p2,p1), r2(p1,p2);
    BOOST_CHECK(r1==r1);
    BOOST_CHECK_EQUAL(r1!=r1, 0);
    BOOST_CHECK(r2==r1);
}

BOOST_AUTO_TEST_CASE( comparing_different_rectangles)
{
    Point <int> p1(1,4), p2(3,6), p3(0,-3), p4(1,5);
    Rectangle<int> r1(p1,p2), r2(p4,p3);
    BOOST_CHECK(r1!=r2);
    BOOST_CHECK_EQUAL(r2==r1, 0);
}


BOOST_AUTO_TEST_CASE( overlaping_rectangles_which_have_a_comman_part)
{
    Point <int> p1(0,4), p2(3,6), p3(1,2), p4(1,5);
    BOOST_CHECK( Rectangle<int>(p1,p2).overlap( Rectangle<int>(p3,p4) ));
}

BOOST_AUTO_TEST_CASE( overlaping_rectangles_which_touch_each_other_with_horisontal_sides )
{
    Point <int> p1(0,4), p2(3,7), p3(-1,2), p4(4,4);
    BOOST_CHECK( Rectangle<int>(p1,p2).overlap( Rectangle<int>(p3,p4) ));
}

BOOST_AUTO_TEST_CASE( overlaping_rectangles_which_touch_each_other_with_vertical_sides )
{
    Point <int> p1(0,4), p2(3,7), p3(3,5), p4(4,6);
    BOOST_CHECK( Rectangle<int>(0,4,3,7).overlap( Rectangle<int>(p3,p4) ));
}

BOOST_AUTO_TEST_CASE( overlaping_rectangles_which_share_a_corner )
{
    Point <int> p1(0,4), p2(3,7), p3(3,7), p4(4,8);
    BOOST_CHECK( Rectangle<int>(p1,p2).overlap( Rectangle<int>(p3,p4) ));
}

BOOST_AUTO_TEST_CASE( overlaping_rectangles_which_do_not_have_a_comman_part_Should_return_false)
{
    Point <int> p1(0,4), p2(3,6), p3(0,1), p4(10,3);
    BOOST_CHECK_EQUAL( Rectangle<int>(p1,p2).overlap( Rectangle<int>(p3,p4) ), 0 );
    //BOOST_CHECK_EQUAL(Rectangle<int>(4,0,6,3).overlap( Rectangle<int>(1,0,3,10) ), 0);
}


BOOST_AUTO_TEST_CASE( union_rectangle_with_the_one_which_cointains_it_)
{
    Point <int> p1(1,4), p2(3,6), p3(0,1), p4(10,12);
    BOOST_CHECK( Rectangle<int>(p1,p2)+Rectangle<int>(p3,p4)==Rectangle<int>(p4,p3));
}

BOOST_AUTO_TEST_CASE( union_of_the_same_ractangles_Result_should_be_the_same_rectangle)
{
    Point <int> p1(0,-2), p2(-3,-4);
    BOOST_CHECK( Rectangle<int>(p1,p2)+Rectangle<int>(p1,p2)==Rectangle<int>(p1,p2) );
}

BOOST_AUTO_TEST_CASE( union_of_separated_rectangles)
{
    Point <int> p1(0,2), p2(3,4), p3(5,2), p4(7,6);
    BOOST_CHECK( Rectangle<int>(p1,p2)+Rectangle<int>(p3,p4)==Rectangle<int>(p1,p4));
}

BOOST_AUTO_TEST_CASE( union_of_two_points_Result_is_a_line)
{
    Point <int> p1(0,0), p2(0,5);
    BOOST_CHECK( Rectangle<int>(p1,p1)+Rectangle<int>(p2,p2)==Rectangle<int>(p1,p2));
}


BOOST_AUTO_TEST_CASE( adding_with_assignment_an_rectangle_which_is_outside)
{
    Point <int> p1(1,6), p2(3,4), p3(0,1), p4(10,12);
    Rectangle <int>rectangle1(p1,p2);
    rectangle1+=Rectangle<int>(p3,p4);
    BOOST_CHECK( rectangle1==Rectangle<int>(p3,p4) );
}

BOOST_AUTO_TEST_CASE( adding_with_assignment_an_rectangle_which_is_inside)
{
    Point <int> p1(1,2), p2(4,5), p3(2,3), p4(3,4);
    Rectangle<int> rectangle1(p1,p2);
    rectangle1+=Rectangle<int>(p3,p4);
    BOOST_CHECK( rectangle1==Rectangle<int>(p1,p2) );
}

BOOST_AUTO_TEST_CASE( adding_with_assignment_the_same_ractangle_It_should_not_change)
{
    Point <int> p1(0,-2), p2(3,4);
    Rectangle<int> rectangle1(p1,p2);
    rectangle1+=Rectangle<int>(p1,p2);
    BOOST_CHECK( rectangle1==Rectangle<int>(p1,p2) );
}

BOOST_AUTO_TEST_CASE( adding_with_assignment_separated_rectangle)
{
    Point <int> p1(0,2), p2(3,4), p3(5,2), p4(7,6);
    Rectangle<int> rectangle1(p1,p2);
    rectangle1+=Rectangle<int>(p3,p4);
    BOOST_CHECK( rectangle1==Rectangle<int>(p1,p4) );
}


BOOST_AUTO_TEST_CASE( itersection_of_rectangles_which_overlap_each_other_Result_is_a_rectangle)
{
    Point <int> p1(0,2), p2(5,6), p3(3,0), p4(10,12), p5(3,2);
    BOOST_CHECK( Rectangle<int>(p1,p2)-Rectangle<int>(p3,p4)==Rectangle<int>(p5,p2) );
}

BOOST_AUTO_TEST_CASE( itersection_of_rectangle_with_the_one_which_it_cointains)
{
    Point <int> p1(0,2), p2(3,4), p3(0,1), p4(10,12);
    BOOST_CHECK( Rectangle<int>(p1,p2)-Rectangle<int>(p3,p4)==Rectangle<int>(p1,p2) );
}

BOOST_AUTO_TEST_CASE( itersection_of_rectangles_which_do_not_overlap_each_other_Should_cought_exception_Intersection_does_not_exist)
{
    Point <int> p1(0,2), p2(5,6), p3(3,4), p4(2,7);
    BOOST_CHECK_THROW(Rectangle<int>(p1,p3)-Rectangle<int>(p2,p4), Error_intersection_does_not_exist);
}

BOOST_AUTO_TEST_CASE( itersection_which_result_is_a_line )
{
    Point <int> p1(0,0), p2(3,2), p3(1,2), p4(4,6), p5(3,2);
    BOOST_CHECK(Rectangle<int>(p1,p2)-Rectangle<int>(p3,p4)==Rectangle<int>(p3,p5));
}

BOOST_AUTO_TEST_CASE( itersection_which_result_is_a_point )
{
    Point <int> p1(0,0), p2(3,2), p3(1,2), p4(4,6), p5(3,2);
    BOOST_CHECK(Rectangle<int>(p1,p2)-Rectangle<int>(p2,p4)==Rectangle<int>(p5,p2));
}


BOOST_AUTO_TEST_CASE( subtract_with_assignment_a_rectangles_which_overlap_it)
{
    Point <int> p1(0,2), p2(3,0), p3(10,12), p4(5,6), p5(3,2);
    Rectangle<int> rectangle1(p1,p4);
    rectangle1-=Rectangle<int>(p2,p3);
    BOOST_CHECK( rectangle1==Rectangle<int>(p4,p5) );
}

BOOST_AUTO_TEST_CASE( subtract_with_assignment_a_rectangle_which_is_outside)
{
    Point <int> p1(0,2), p2(3,4), p3(10,12), p4(0,1);
    Rectangle<int> rectangle1(p1,p2);
    rectangle1-=Rectangle<int>(p3,p4);
    BOOST_CHECK( rectangle1==Rectangle<int>(p1,p2) );
}

BOOST_AUTO_TEST_CASE( subtract_with_assignment_a_rectangle_which_is_inside)
{
    Point <int> p1(0,2), p2(3,4), p3(10,12), p4(0,1);
    Rectangle<int> rectangle1(p3,p4);
    rectangle1-=Rectangle<int>(p1,p2);
    BOOST_CHECK( rectangle1==Rectangle<int>(p1,p2) );
}

BOOST_AUTO_TEST_CASE( subtract_with_assignment_a_separated_rectangle_Should_cought_exception_Intersection_does_not_exist)
{
    Point <int> p1(0,2), p2(3,4), p3(5,2), p4(7,6);
    Rectangle<int> rectangle1(p1,p2);
    BOOST_CHECK_THROW(rectangle1-=Rectangle<int>(p3,p4), Error_intersection_does_not_exist);
}

BOOST_AUTO_TEST_CASE( subtraction_assignment_which_result_is_a_line )
{
    Point <int> p1(1,2), p2(3,2), p3(0,0), p4(4,6);
    Rectangle<int> rectangle1(p2,p3);
    rectangle1-=Rectangle<int>(p1,p4);
    BOOST_CHECK( rectangle1==Rectangle<int>(p1,p2) );
}

BOOST_AUTO_TEST_CASE( subtraction_assignment_which_result_is_a_point )
{
    Point <int>  p2(3,2), p3(0,0), p4(4,6);
    Rectangle<int> rectangle1(p2,p3);
    rectangle1-=Rectangle<int>(p2,p4);
    BOOST_CHECK( rectangle1==Rectangle<int>(p2,p2) );
}


BOOST_AUTO_TEST_CASE( containing_a_point_which_is_inside_the_rectangle)
{
    Point <int>  p1(5,5), p2(1,2);
    BOOST_CHECK( Rectangle<int>(p1,p2).cointains_point( Point<int>(2,4) ) );
}

BOOST_AUTO_TEST_CASE( containing_a_point_which_is_in_the_top_right_corner_of_rectangle)
{
    Point <int>  p1(5,5), p2(1,2);
    BOOST_CHECK( Rectangle<int>(p1,p2).cointains_point( Point<int>(5,5) ) );
}

BOOST_AUTO_TEST_CASE( containing_a_point_which_is_in_the_uppon_left_corner_of_rectangle)
{
    Point <int>  p1(5,5), p2(1,2);
    BOOST_CHECK( Rectangle<int>(p1,p2).cointains_point( Point<int>(1,2) ) );
}

BOOST_AUTO_TEST_CASE( containing_a_point_which_is_in_on_the_top_side_of_rectangle)
{
    Point <int>  p1(5,5), p2(1,2);
    BOOST_CHECK( Rectangle<int>(p1,p2).cointains_point( Point<int>(3,5) ) );
}

BOOST_AUTO_TEST_CASE( containing_a_point_which_is_in_on_the_uppon_side_of_rectangle)
{
    Point <int>  p1(5,5), p2(1,2);
    BOOST_CHECK( Rectangle<int>(p1,p2).cointains_point( Point<int>(3,2) ) );
}

BOOST_AUTO_TEST_CASE( containing_a_point_which_is_in_on_the_right_side_of_rectangle)
{
    Point <int>  p1(5,5), p2(1,2);
    BOOST_CHECK( Rectangle<int>(p1,p2).cointains_point( Point<int>(5,4) ) );
}

BOOST_AUTO_TEST_CASE( containing_a_point_which_is_in_on_the_left_side_of_rectangle)
{
    Point <int>  p1(5,5), p2(1,2);
    BOOST_CHECK( Rectangle<int>(p1,p2).cointains_point( Point<int>(1,4) ) );
}

BOOST_AUTO_TEST_CASE( containing_a_point_which_is_the_same_as_rectangle)
{
    Point <int>  p1(5,5), p2(1,2);
    BOOST_CHECK( Rectangle<int>(p1,p2).cointains_point( Point<int>(1,2) ) );
}

BOOST_AUTO_TEST_CASE( containing_a_point_which_is_outside_the_rectangle_Should_return_false)
{
    Point <int>  p1(5,5), p2(1,2);
    BOOST_CHECK_EQUAL( Rectangle<int>(p1,p2).cointains_point(Point<int>(0,0)), 0);
}



BOOST_AUTO_TEST_SUITE_END()
