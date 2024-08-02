#include <Vector3/Vector3.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Vec3 float init with zero arg", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector{};
    REQUIRE_THAT(Vector.x, WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(Vector.y, WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(Vector.z, WithinRel(0.0f, 0.0001f));
}

TEST_CASE("Vec3 float init with 0", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector{0.0f, 0.0f, 0.0f};
    REQUIRE_THAT(Vector.x, WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(Vector.y, WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(Vector.z, WithinRel(0.0f, 0.0001f));
}

TEST_CASE("Vec3 float init with numbers", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector{1, 2, 3};

    REQUIRE_THAT(Vector.x, WithinRel(1.0f, 0.0001f));
    REQUIRE_THAT(Vector.y, WithinRel(2.0f, 0.0001f));
    REQUIRE_THAT(Vector.z, WithinRel(3.0f, 0.0001f));
}

TEST_CASE("Vec3 float init with numbers - not integer", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector{1.5f, 2.2f, 3.3f};

    REQUIRE_THAT(Vector.x, WithinRel(1.5f, 0.0001f));
    REQUIRE_THAT(Vector.y, WithinRel(2.2f, 0.0001f));
    REQUIRE_THAT(Vector.z, WithinRel(3.3f, 0.0001f));
}


TEST_CASE("Vec3 float compare identical integer", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector1{1, 2, 3};
    Vector3<float> Vector2{1, 2, 3};

    bool Result = Vector1 == Vector2;

    REQUIRE(Result == true);
}

TEST_CASE("Vec3 float compare nonidentical integer", "[vec3][vec3_float]")
{
    Vector3<float> Vector1{1, 2, 3};
    Vector3<float> Vector2{4, 5, 6};

    bool Result = Vector1 == Vector2;

    REQUIRE(Result == false);
}

TEST_CASE("Vec3 float compare identical float", "[vec3][vec3_float]")
{
    Vector3<float> Vector1{1.5f, 2.2f, 3.3f};
    Vector3<float> Vector2{1.5f, 2.2f, 3.3f};

    bool Result = Vector1 == Vector2;

    REQUIRE(Result == true);
}

TEST_CASE("Vec3 float compare nonidentical float", "[vec3][vec3_float]")
{
    Vector3<float> Vector1{1.5f, 2.2f, 3.3f};
    Vector3<float> Vector2{4.5f, 6.2f, 1.3f};

    bool Result = Vector1 == Vector2;

    REQUIRE(Result == false);
}

TEST_CASE("Vec3 float test != operator with non identical", "[vec3][vec3_float]")
{
    Vector3<float> Vector1{1, 2, 3};
    Vector3<float> Vector2{1, 2, 6};

    bool Result = Vector1 != Vector2;

    REQUIRE(Result == true);
}

TEST_CASE("Vec3 float test != operator with identical", "[vec3][vec3_float]")
{
    Vector3<float> Vector1{1, 2, 3};
    Vector3<float> Vector2{1, 2, 3};

    bool Result = Vector1 != Vector2;

    REQUIRE(Result == false);
}


TEST_CASE("Vec3 float add 2 predefined vectors", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector1{1.3f, 1.4f, 1.5f};
    Vector3<float> Vector2{1.3f, 1.4f, 1.5f};

    auto Result = Vector1 + Vector2;

    REQUIRE_THAT(Result.x, WithinRel(2.6f, 0.0001f));
    REQUIRE_THAT(Result.y, WithinRel(2.8f, 0.0001f));
    REQUIRE_THAT(Result.z, WithinRel(3.0f, 0.0001f));
}

TEST_CASE("Vec3 float sud 2 predefined vectors", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector1{1.3f, 1.4f, 1.5f};
    Vector3<float> Vector2{1.4f, 2.4f, 1.3f};

    auto Result = Vector1 - Vector2;

    REQUIRE_THAT(Result.x, WithinRel(-0.1f, 0.0001f));
    REQUIRE_THAT(Result.y, WithinRel(-1.0f, 0.0001f));
    REQUIRE_THAT(Result.z, WithinRel(0.2f, 0.0001f));
}

TEST_CASE("Vec3 float multiply", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector1{1, 1, 1};

    auto Result = Vector1 * 2.4f;

    REQUIRE_THAT(Result.x, WithinRel(2.4f, 0.0001f));
    REQUIRE_THAT(Result.y, WithinRel(2.4f, 0.0001f));
    REQUIRE_THAT(Result.z, WithinRel(2.4f, 0.0001f));
}

TEST_CASE("Vec3 float divide by positive number, result integer", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector1{3.0f, 3.0f, 3.0f};

    auto Result = Vector1 / 2.0f;

    REQUIRE_THAT(Result.x, WithinRel(1.5f, 0.0001f));
    REQUIRE_THAT(Result.y, WithinRel(1.5f, 0.0001f));
    REQUIRE_THAT(Result.z, WithinRel(1.5f, 0.0001f));
}

TEST_CASE("Vec3 float modify existed vector: add", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector{1.5f,1.2f,1.3f};

    Vector+= Vector3<float>{1.5f,0.2f,-1.3f};
    
    REQUIRE_THAT(Vector.x, WithinRel(3.0f, 0.0001f));
    REQUIRE_THAT(Vector.y, WithinRel(1.4f, 0.0001f));
    REQUIRE_THAT(Vector.z, WithinRel(0.0f, 0.0001f));
}

TEST_CASE("Vec3 float modify existed vector: sub", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector{1.5f,1.2f,1.3f};

    Vector-= Vector3<float>{1.5f,0.2f,-1.3f};
    
    REQUIRE_THAT(Vector.x, WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(Vector.y, WithinRel(1.0f, 0.0001f));
    REQUIRE_THAT(Vector.z, WithinRel(2.6f, 0.0001f));
}

TEST_CASE("Vec3 float modify existed vector: mul", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector{1.5f,1.2f,1.3f};

    Vector*= 2.0f;
    
    REQUIRE_THAT(Vector.x, WithinRel(3.0f, 0.0001f));
    REQUIRE_THAT(Vector.y, WithinRel(2.4f, 0.0001f));
    REQUIRE_THAT(Vector.z, WithinRel(2.6f, 0.0001f));
}

TEST_CASE("Vec3 float modify existed vector: div", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector{3.0f,1.2f,1.3f};

    Vector/= 2.0f;
    
    REQUIRE_THAT(Vector.x, WithinRel(1.5f, 0.0001f));
    REQUIRE_THAT(Vector.y, WithinRel(0.6f, 0.0001f));
    REQUIRE_THAT(Vector.z, WithinRel(0.65f, 0.0001f));
}


TEST_CASE("Vec3 float cross function 1", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector1{1.3f, 1.4f, 1.5f};
    Vector3<float> Vector2{1.4f, 2.4f, 1.3f};

    auto Result = cross(Vector1, Vector2);


    REQUIRE_THAT(Result.x, WithinRel(-1.78f, 0.0001f));
    REQUIRE_THAT(Result.y, WithinRel(0.41f, 0.0001f));
    REQUIRE_THAT(Result.z, WithinRel(1.16f, 0.0001f));
}


TEST_CASE("Vec3 float cross function 2", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector1{0.0f, 0.0f, 0.0f};
    Vector3<float> Vector2{0.0f, 0.0f, 0.0f};

    auto Result = cross(Vector1, Vector2);


    REQUIRE_THAT(Result.x, WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(Result.y, WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(Result.z, WithinRel(0.0f, 0.0001f));
}


TEST_CASE("Vec3 float vector length 1", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector1{0.0f, 0.0f, 0.0f};

    REQUIRE_THAT(Vector1.getLength(), WithinRel(0.0f, 0.0001f));

}


TEST_CASE("Vec3 float vector length 2", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector1{1.0f, 1.0f, 1.0f};

    REQUIRE_THAT(Vector1.getLength(), WithinAbs(1.732f, 0.01f));
}


TEST_CASE("Vec3 float unit vector 1", "[vec3][vec3_float]")
{

    using namespace Catch::Matchers;
    Vector3<float> Vector1{0.0f, 0.0f, 0.0f};

    auto Result = Vector1.getUnitVector();

    REQUIRE_THAT(Result.x, WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(Result.y, WithinRel(0.0f, 0.0001f));
    REQUIRE_THAT(Result.z, WithinRel(0.0f, 0.0001f));
}


TEST_CASE("Vec3 float unit vector 2", "[vec3][vec3_float]")
{
    using namespace Catch::Matchers;
    Vector3<float> Vector1{1.0f, 1.0f, 1.0f};

    auto Result = Vector1.getUnitVector();

    REQUIRE_THAT(Result.x, WithinAbs(0.577f, 0.01f));
    REQUIRE_THAT(Result.y, WithinAbs(0.577f, 0.01f));
    REQUIRE_THAT(Result.z, WithinAbs(0.577f, 0.01f));

}