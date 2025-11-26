#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


#include "num_vector.h"

TEST_CASE("Default constructor (always passes)")
{
    INFO("This test always passes.");
    num::NumericVector v{};
    CHECK(v.size() == 0);
    CHECK(v.empty());
}

SCENARIO("Copy constructor")
{
    GIVEN("A vector with two elements")
    {
        num::NumericVector v{1.0, 2.0};
    
        WHEN("A copy is made")
        {
            num::NumericVector copy{v};
            THEN("The copy has the same size and elements")
            {
                CHECK(copy.size() == 2);
                CHECK(copy[0] == 1.0);
                CHECK(copy[1] == 2.0);
            }
        }
    }
}

SCENARIO("Copy assignment operator")
{
    GIVEN("A vector with five elements")
    {
        num::NumericVector v{1.0, 2.0, 3.0, 4.0, 5.0};
    
        WHEN("A copy is made")
        {
            num::NumericVector copy{};
            copy = v;
            THEN("The copy has the same size and elements")
            {
                CHECK(copy.size() == 5);
                CHECK(copy[0] == 1.0);
                CHECK(copy[1] == 2.0);
                CHECK(copy[2] == 3.0);
                CHECK(copy[3] == 4.0);
                CHECK(copy[4] == 5.0);
            }
        }
    }
}


SCENARIO("at function")
{
    GIVEN("A vector with three elements")
    {
        num::NumericVector v{1.0, 2.0, 3.0};
    
        WHEN("The elements are accessed with at")
        {
            THEN("The elements are 1.0, 2.0, and 3.0")
            {
                CHECK(v.at(0) == 1.0);
                CHECK(v.at(1) == 2.0);
                CHECK(v.at(2) == 3.0);
            }
        }
        WHEN("An out-of-bounds index is accessed")
        {
            THEN("An exception is thrown")
            {
                CHECK_THROWS_AS(v.at(3), std::out_of_range);
            }
        }
    }
}

SCENARIO("Push back")
{
    GIVEN("An empty vector")
    {
        num::NumericVector v{};
        REQUIRE(v.size() == 0);
        REQUIRE(v.empty());

        WHEN("Two elements are pushed back")
        {
            v.push_back(1.0);
            v.push_back(2.0);
            THEN("The size is 2 and the elements are 1.0 and 2.0")
            {
                CHECK(v.size() == 2);
                CHECK(v[0] == 1.0);
                CHECK(v[1] == 2.0);
            }
        }
    }
}


SCENARIO("Pop back")
{
    GIVEN("A vector with three elements")
    {
        num::NumericVector v{1.0, 2.0, 3.0};
        REQUIRE(v.size() == 3);

        WHEN("One element is popped back")
        {
            v.pop_back();
            THEN("The size is 2 and the elements are 1.0 and 2.0")
            {
                CHECK(v.size() == 2);
                CHECK(v[0] == 1.0);
                CHECK(v[1] == 2.0);
            }
        }
    }

    GIVEN("An empty vector")
    {
        num::NumericVector v{};
        REQUIRE(v.size() == 0);

        WHEN("pop_back is called")
        {
            THEN("An exception is thrown")
            {
                CHECK_THROWS_AS(v.pop_back(), std::out_of_range);
            }
            AND_THEN("The vector is still empty")
            {
                try{ v.pop_back(); }catch(...){}
                CHECK(v.size() == 0);
                CHECK(v.empty());
            }
        }
    }

    GIVEN("A vector with one element")
    {
        num::NumericVector v{1.0};
        REQUIRE(v.size() == 1);

        WHEN("pop_back is called")
        {
            v.pop_back();
            THEN("The vector is empty")
            {
                CHECK(v.size() == 0);
                CHECK(v.empty());
            }
        }

        WHEN("pop_back is called twice")
        {
            v.pop_back();
            THEN("An exception is thrown")
            {
                CHECK_THROWS_AS(v.pop_back(), std::out_of_range);
            }
        }
    }
}


SCENARIO("Sum")
{
    GIVEN("A vector with 10 elements")
    {
        num::NumericVector v{1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 11.0};
        REQUIRE(v.size() == 10);

        WHEN("The sum is calculated")
        {
            double sum = v.sum();
            THEN("The sum is 60.5")
            {
                CHECK(sum == 60.5);
            }
        }
    }

    GIVEN("An empty vector")
    {
        num::NumericVector v{};
        REQUIRE(v.size() == 0);

        WHEN("The sum is calculated")
        {
            double sum = v.sum();
            THEN("The sum is 0.0")
            {
                CHECK(sum == 0.0);
            }
        }
    }
}

SCENARIO("Average")
{
    GIVEN("A vector with 10 elements")
    {
        num::NumericVector v{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
        REQUIRE(v.size() == 10);

        WHEN("The average is calculated")
        {
            double average = v.average();
            THEN("The average is 5.5")
            {
                CHECK(average == 5.5);
            }
        }
    }

    GIVEN("An empty vector")
    {
        num::NumericVector v{};
        REQUIRE(v.size() == 0);

        WHEN("The average is calculated")
        {
           THEN("An exception is thrown")
           {
               CHECK_THROWS_AS(v.average(), std::domain_error);
           }
        }
    }
}


SCENARIO("Operator+= (compound addition)")
{
    GIVEN("Two vectors with three elements")
    {
        num::NumericVector v1{1.0, 2.0, 3.0};
        num::NumericVector v2{4.0, 5.0, 6.0};
        REQUIRE(v1.size() == 3);
        REQUIRE(v2.size() == 3);

        WHEN("The vectors are added")
        {
            v1 += v2;
            THEN("The v1 has the elements 5.0, 7.0, and 9.0")
            {
                CHECK(v1.size() == 3);
                CHECK(v1[0] == 5.0);
                CHECK(v1[1] == 7.0);
                CHECK(v1[2] == 9.0);
            }
        }
    }

    GIVEN("Two vectors with different sizes")
    {
        num::NumericVector v1{1.0, 2.0, 3.0};
        num::NumericVector v2{4.0, 5.0};
        REQUIRE(v1.size() == 3);
        REQUIRE(v2.size() == 2);

        WHEN("The vectors are added")
        {
            THEN("An exception is thrown")
            {
                CHECK_THROWS_AS(v1 += v2, std::invalid_argument);
            }
        }
    }
}

SCENARIO("operator== (comparison)")
{
    GIVEN("Two vectors with the same elements")
    {
        num::NumericVector v1{1.0, 2.0, 3.0};
        num::NumericVector v2{1.0, 2.0, 3.0};
        REQUIRE(v1.size() == 3);
        REQUIRE(v2.size() == 3);

        WHEN("The vectors are compared")
        {
            THEN("The vectors are equal")
            {
                CHECK(v1 == v2);
            }
        }
    }

    GIVEN("Two vectors with different elements")
    {
        num::NumericVector v1{1.0, 2.0, 3.0, 3.0, 2.0, 1.0};
        num::NumericVector v2{6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
        REQUIRE(v1.size() == v2.size());

        WHEN("The vectors are compared")
        {
            THEN("The vectors are not equal")
            {
                CHECK_FALSE(v1 == v2);
            }
        }
    }

    GIVEN("Two vectors with different sizes")
    {
        num::NumericVector v1{1.0, 2.0, 3.0};
        num::NumericVector v2{1.0, 2.0};
        REQUIRE(v1.size() == 3);
        REQUIRE(v2.size() == 2);

        WHEN("The vectors are compared")
        {
            THEN("The vectors are not equal")
            {
                CHECK_FALSE(v1 == v2);
            }
        }
    }
}

SCENARIO("operator+ (addition of two vectors)")
{
    GIVEN("Two vectors with three elements")
    {
        num::NumericVector v1{1.0, 2.0, 3.0};
        num::NumericVector v2{4.0, 5.0, 6.0};
        REQUIRE(v1.size() == 3);
        REQUIRE(v2.size() == 3);

        WHEN("The vectors are added")
        {
            num::NumericVector sum = v1 + v2;
            THEN("The sum has the elements 5.0, 7.0, and 9.0")
            {
                CHECK(sum.size() == 3);
                CHECK(sum[0] == 5.0);
                CHECK(sum[1] == 7.0);
                CHECK(sum[2] == 9.0);
            }
        }
    }

    GIVEN("Two vectors with different sizes")
    {
        num::NumericVector v1{1.0, 2.0, 3.0};
        num::NumericVector v2{4.0, 5.0};
        REQUIRE(v1.size() == 3);
        REQUIRE(v2.size() == 2);

        WHEN("The vectors are added")
        {
            THEN("An exception is thrown")
            {
                CHECK_THROWS_AS(v1 + v2, std::invalid_argument);
            }
        }
    }
}