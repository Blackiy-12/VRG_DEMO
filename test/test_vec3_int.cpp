#include <Vector3/Vector3.h>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Vec3 int init with zero arg", "[vec3][vec3_int]")
{
    Vector3<int> Vector{};

    REQUIRE(Vector.x == 0);
    REQUIRE(Vector.y == 0);
    REQUIRE(Vector.z == 0);
}

TEST_CASE("Vec3 int init with 0", "[vec3][vec3_int]")
{
    Vector3<int> Vector{0, 0, 0};

    REQUIRE(Vector.x == 0);
    REQUIRE(Vector.y == 0);
    REQUIRE(Vector.z == 0);
}

TEST_CASE("Vec3 int init with numbers", "[vec3][vec3_int]")
{
    Vector3<int> Vector{1, 2, 3};

    REQUIRE(Vector.x == 1);
    REQUIRE(Vector.y == 2);
    REQUIRE(Vector.z == 3);
}

TEST_CASE("Vec3 int compare identical", "[vec3][vec3_int]")
{
    Vector3<int> Vector1{1, 2, 3};
    Vector3<int> Vector2{1, 2, 3};

    bool Result = Vector1 == Vector2;

    REQUIRE(Result == true);
}

TEST_CASE("Vec3 int compare nonidentical", "[vec3][vec3_int]")
{
    Vector3<int> Vector1{1, 2, 3};
    Vector3<int> Vector2{4, 5, 6};

    bool Result = Vector1 == Vector2;

    REQUIRE(Result == false);
}

TEST_CASE("Vec3 int compare with 1 identical numbers", "[vec3][vec3_int]")
{
    Vector3<int> Vector1{1, 2, 3};
    Vector3<int> Vector2{1, 5, 6};

    bool Result = Vector1 == Vector2;

    REQUIRE(Result == false);
}

TEST_CASE("Vec3 int compare with 2 identical numbers", "[vec3][vec3_int]")
{
    Vector3<int> Vector1{1, 2, 3};
    Vector3<int> Vector2{1, 2, 6};

    bool Result = Vector1 == Vector2;

    REQUIRE(Result == false);
}

TEST_CASE("Vec3 int compare with no lvalue - identical", "[vec3][vec3_int]")
{
    Vector3<int> Vector1{1, 2, 3};
    
    bool Result = Vector1 == Vector3<int>{1, 2, 3};

    REQUIRE(Result == true);
}

TEST_CASE("Vec3 int compare with no lvalue - non identical", "[vec3][vec3_int]")
{
    Vector3<int> Vector1{1, 2, 3};
    
    bool Result = Vector1 == Vector3<int>{2, 2, 3};

    REQUIRE(Result == false);
}

TEST_CASE("Vec3 int compare with no lvalue(both) - identical", "[vec3][vec3_int]")
{
    bool Result = Vector3<int> {1, 2, 3} == Vector3<int>{1, 2, 3};

    REQUIRE(Result == true);
}

TEST_CASE("Vec3 int compare with no lvalue(both) - non identical", "[vec3][vec3_int]")
{
    
    bool Result = Vector3<int> {1, 2, 3} == Vector3<int>{2, 2, 3};

    REQUIRE(Result == false);
}

TEST_CASE("Vec3 int test != operator with non identical", "[vec3][vec3_int]")
{
    Vector3<int> Vector1{1, 2, 3};
    Vector3<int> Vector2{1, 2, 6};

    bool Result = Vector1 != Vector2;

    REQUIRE(Result == true);
}

TEST_CASE("Vec3 int test != operator with identical", "[vec3][vec3_int]")
{
    Vector3<int> Vector1{1, 2, 3};
    Vector3<int> Vector2{1, 2, 3};

    bool Result = Vector1 != Vector2;

    REQUIRE(Result == false);
}


TEST_CASE("Vec3 int add 2 predefined vectors", "[vec3][vec3_int]")
{
    Vector3<int> Vector1{1, 1, 1};
    Vector3<int> Vector2{1, 1, 1};

    auto Result = Vector1 + Vector2;

    REQUIRE(Result.x == 2);
    REQUIRE(Result.y == 2);
    REQUIRE(Result.z == 2);
}

TEST_CASE("Vec3 int add predefined vector and non lvalue vector", "[vec3][vec3_int]")
{
    Vector3<int> Vector1{1, 1, 1};

    auto Result = Vector1 + Vector3<int>{1, 1, 1};

    REQUIRE(Result.x == 2);
    REQUIRE(Result.y == 2);
    REQUIRE(Result.z == 2);
}

TEST_CASE("Vec3 int add 2 non lvalue vector", "[vec3][vec3_int]")
{
    auto Result = Vector3<int>{1, 1, 1} + Vector3<int>{1, 1, 1};

    REQUIRE(Result.x == 2);
    REQUIRE(Result.y == 2);
    REQUIRE(Result.z == 2);
}

TEST_CASE("Vec3 int sud 2 predefined vectors", "[vec3][vec3_int]")
{
    Vector3<int> Vector1{1, 1, 1};
    Vector3<int> Vector2{1, 1, 1};

    auto Result = Vector1 - Vector2;

    REQUIRE(Result.x == 0);
    REQUIRE(Result.y == 0);
    REQUIRE(Result.z == 0);
}

TEST_CASE("Vec3 int sub predefined vector and non lvalue vector", "[vec3][vec3_int]")
{
    Vector3<int> Vector1{1, 1, 1};

    auto Result = Vector1 - Vector3<int>{1, 1, 1};

    REQUIRE(Result.x == 0);
    REQUIRE(Result.y == 0);
    REQUIRE(Result.z == 0);
}

TEST_CASE("Vec3 int sub 2 non lvalue vector", "[vec3][vec3_int]")
{
    auto Result = Vector3<int>{1, 1, 1} - Vector3<int>{1, 1, 1};

    REQUIRE(Result.x == 0);
    REQUIRE(Result.y == 0);
    REQUIRE(Result.z == 0);
}