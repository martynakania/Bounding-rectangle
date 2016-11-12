#include "collection.h"
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(CollectionTests)



std::vector<Point<int>> vectp = {{1,2}, {2,3}};

BOOST_AUTO_TEST_CASE(creating_empty_collection)
{
    Collection<int> collection1(5);
    BOOST_CHECK_EQUAL( collection1.get_size(),5 );
    BOOST_CHECK_EQUAL( collection1.get_amount(),0);
    BOOST_CHECK_EQUAL(collection1.get_index_of_last(), -1);
}
BOOST_AUTO_TEST_CASE(create_filled_collection_without_size)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}}, {{-2,2},{4,3}} };
    Collection<int> collection1(vect);
    BOOST_CHECK_EQUAL( collection1.get_size(),   4);
    BOOST_CHECK_EQUAL( collection1.get_amount(), 4);
    BOOST_CHECK_EQUAL( collection1.get_index_of_last(), 3);
    BOOST_CHECK_EQUAL( collection1.get_last_rectangle(), Rectangle<int>({ {-2,2},{4,3} }) );
    BOOST_CHECK_EQUAL( collection1.get_rectangle(1), Rectangle<int>({ {2,2},{3,3} }) );
}

BOOST_AUTO_TEST_CASE(create_filled_collection_with_size)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}}, {{2,2},{3,3}} };
    Collection<int> collection1(3,vect);
    BOOST_CHECK_EQUAL( collection1.get_size(),   3);
    BOOST_CHECK_EQUAL( collection1.get_amount(), 3);
    BOOST_CHECK_EQUAL( collection1.get_index_of_last(), 2);
    BOOST_CHECK_EQUAL( collection1.get_last_rectangle(), Rectangle<int>({ {4,4},{4,4} }) );
    BOOST_CHECK_EQUAL( collection1.get_rectangle(1), Rectangle<int>({ {2,2},{3,3} }) );
}

BOOST_AUTO_TEST_CASE(create_unfilled_collection_with_size)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}} };
    Collection<int> collection1(4,vect);
    BOOST_CHECK_EQUAL( collection1.get_size(),4 );
    BOOST_CHECK_EQUAL( collection1.get_amount(), 3);
    BOOST_CHECK_EQUAL( collection1.get_index_of_last(), 2);
}

BOOST_AUTO_TEST_CASE(create_collection_with_negative_size)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}} };

    BOOST_CHECK_THROW( Collection<int>(-1,vect), error_negative_size );
    BOOST_CHECK_THROW( Collection<int>(-5), error_negative_size);
}

BOOST_AUTO_TEST_CASE(create_collection_with_zero)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}} };

    BOOST_CHECK_THROW( Collection<int>(0,vect), error_negative_size );
    BOOST_CHECK_THROW( Collection<int>(0), error_negative_size);
}

BOOST_AUTO_TEST_CASE(get_rectangle_from_collection)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}} };
    Collection<int> collection1(4,vect);
    BOOST_CHECK_EQUAL( collection1.get_rectangle(1), Rectangle<int>({ {2,2},{3,3} }) );
}

BOOST_AUTO_TEST_CASE(get_last_rectangle)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}} };
    Collection<int> collection1(4,vect);
    BOOST_CHECK_EQUAL( collection1.get_last_rectangle(), Rectangle<int>( {{4,4},{4,4}} ) );
}

BOOST_AUTO_TEST_CASE(get_amount_of_collection)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}} };
    Collection<int> collection1(4,vect);
    BOOST_CHECK_EQUAL( collection1.get_amount(), 3 );
}

BOOST_AUTO_TEST_CASE(get_index_of_last)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}} };
    Collection<int> collection1(4,vect);
    BOOST_CHECK_EQUAL( collection1.get_index_of_last(), 2);
}

BOOST_AUTO_TEST_CASE(get_index_of_last_after_adding_rectange_to_filled_collection)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}} };
    Collection<int> collection1(vect);
    collection1.add_rectangle(Rectangle<int>( {{1,4},{4,5}} ));
    collection1.add_rectangle(Rectangle<int>( {{1,4},{4,5}} ));
    BOOST_CHECK_EQUAL( collection1.get_index_of_last(), 1);
}

BOOST_AUTO_TEST_CASE(get_index_of_last_after_deleting_rectange)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}} };
    Collection<int> collection1(4,vect);
    collection1.delete_last_rectangle();
    BOOST_CHECK_EQUAL( collection1.get_index_of_last(), 1);
}

BOOST_AUTO_TEST_CASE(delete_rectangle)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}} };
    Collection<int> collection1(vect);
    collection1.delete_last_rectangle();
    BOOST_CHECK_EQUAL( collection1.get_amount(), 2 );
    BOOST_CHECK_EQUAL( collection1.get_index_of_last(), 1 );
}


BOOST_AUTO_TEST_CASE(add_rectangle_to_unfilled_collection)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}} };
    Collection<int> collection1(4,vect);
    collection1.add_rectangle(Rectangle<int>( {{3,4},{4,8}} ));
    BOOST_CHECK_EQUAL( collection1.get_last_rectangle(), Rectangle<int>({ {3,4},{4,8} }) );
    BOOST_CHECK_EQUAL( collection1.get_index_of_last(),3);
}

BOOST_AUTO_TEST_CASE(add_rectangle_to_filled_collection)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}}, {{3,4},{4,8}} };
    Collection<int> collection1(4,vect);
    collection1.add_rectangle(Rectangle<int>( {{1,4},{4,5}} ));
    BOOST_CHECK_EQUAL( collection1.get_index_of_last(),0);
    BOOST_CHECK_EQUAL( collection1.get_last_rectangle(), Rectangle<int>( {{1,4},{4,5}} ) );
    BOOST_CHECK_EQUAL( collection1.get_rectangle(0), Rectangle<int>( {{1,4},{4,5}} ) );
}

BOOST_AUTO_TEST_CASE(get_rectangle_which_contains_the_whole_collection)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}}, {{5,4},{4,7}} };
    Collection<int> collection1(4,vect);
    Rectangle<int>r1=collection1.get_whole_collection();
    BOOST_CHECK_EQUAL(r1, Rectangle<int>({0,0},{5,7}));
}

BOOST_AUTO_TEST_CASE(extent_collection_size__Last_is_at_the_end__Collection_is_full)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}}, {{3,4},{4,8}} };
    Collection<int> collection1(vect);
    int last_before=collection1.get_index_of_last();
    collection1.change_collection_size(6);
    BOOST_CHECK_EQUAL( collection1.get_size(), 6);
    BOOST_CHECK_EQUAL( collection1.get_index_of_last(), last_before);
    BOOST_CHECK_EQUAL( collection1.get_rectangle(1), Rectangle<int>({{2,2},{3,3}}) );
    BOOST_CHECK_EQUAL( collection1.get_last_rectangle(), Rectangle<int>( {{3,4},{4,8}} ) );
}

BOOST_AUTO_TEST_CASE(extent_collection_size__Last_is_at_the_end__Collection_is_not_full)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}}, {{3,4},{4,8}} };
    Collection<int> collection1(vect);
    collection1.delete_last_rectangle();
    int last_before=collection1.get_index_of_last();
    collection1.change_collection_size(6);
    BOOST_CHECK_EQUAL( collection1.get_size(), 6);
    BOOST_CHECK_EQUAL( collection1.get_index_of_last(), last_before);
    BOOST_CHECK_EQUAL( collection1.get_rectangle(1), Rectangle<int>({{2,2},{3,3}}) );
    BOOST_CHECK_EQUAL( collection1.get_last_rectangle(), Rectangle<int>( {{4,4},{4,4}} ) );
}

BOOST_AUTO_TEST_CASE(extent_collection_size_Last_is_in_the_middle_Collection_is_full)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}} };
    Collection<int> collection1(2,vect);
    collection1.add_rectangle({{3,4},{4,8}});
    collection1.change_collection_size(5);
    BOOST_CHECK_EQUAL( collection1.get_size(), 5);
    BOOST_CHECK_EQUAL( collection1.get_index_of_last(), collection1.get_amount()-1);
    BOOST_CHECK_EQUAL( collection1.get_rectangle(0), Rectangle<int>({{2,2},{3,3}}) );
    BOOST_CHECK_EQUAL( collection1.get_rectangle(1), Rectangle<int>({{3,4},{4,8}}) );
}

BOOST_AUTO_TEST_CASE(extent_collection_size_Last_is_in_the_middle_Collection_is_not_full)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}}, {{3,4},{4,8}} };
    Collection<int> collection1(vect);
        int last_before=collection1.get_index_of_last();
        collection1.add_rectangle({{3,1},{4,7}});
        collection1.add_rectangle({{1,4},{7,8}});
        collection1.add_rectangle({{1,4},{7,8}});
        collection1.delete_last_rectangle();
        collection1.delete_last_rectangle();
        BOOST_CHECK_EQUAL( collection1.get_index_of_last(), 0);
        BOOST_CHECK_EQUAL( collection1.get_amount(), 2);
    collection1.change_collection_size(6);
    BOOST_CHECK_EQUAL( collection1.get_size(), 6);
    BOOST_CHECK_EQUAL( collection1.get_index_of_last(), 1);
    BOOST_CHECK_EQUAL( collection1.get_amount(), 2);
    BOOST_CHECK_EQUAL( collection1.get_rectangle(0), Rectangle<int>({{3,4},{4,8}}) );
    BOOST_CHECK_EQUAL( collection1.get_last_rectangle(), Rectangle<int>( {{3,1},{4,7}} ) );
}


BOOST_AUTO_TEST_CASE(reduce_collection_size_collection)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}}, {{3,4},{4,8}} };
    Collection<int> collection1(6,vect);
    collection1.change_collection_size(3);
    BOOST_CHECK_EQUAL( collection1.get_size(), 3);
    BOOST_CHECK_EQUAL( collection1.get_index_of_last(),  collection1.get_amount()-1);
    BOOST_CHECK_EQUAL( collection1.get_rectangle(0), Rectangle<int>({{2,2},{3,3}}) );
    BOOST_CHECK_EQUAL( collection1.get_rectangle(2), Rectangle<int>({{3,4},{4,8}}) );
}

BOOST_AUTO_TEST_CASE(copy_collection)
{
    std::vector<Rectangle<int>> vect = { {{0,0},{1,1}}, {{2,2},{3,3}}, {{4,4},{4,4}}, {{3,4},{4,8}} };
    Collection<int> collection1(4,vect);
    Collection<int> collection2(6);
    collection2=collection1;
    BOOST_CHECK_EQUAL( collection2.get_size(), 4);
    BOOST_CHECK_EQUAL( collection1.get_rectangle(0), Rectangle<int>({{0,0},{1,1}}) );
    BOOST_CHECK_EQUAL( collection1.get_rectangle(3), Rectangle<int>({{3,4},{4,8}}) );
}

BOOST_AUTO_TEST_SUITE_END()
