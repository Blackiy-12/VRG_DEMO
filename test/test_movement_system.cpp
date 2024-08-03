#include <Simulation/MovementSystem.h>
#include <Simulation/Unit.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Movement system bullet test basic", "[movement_system]")
{
    std::shared_ptr<entt::registry> Registry = std::make_shared<entt::registry>();

    MovementSystem TestSystem(Registry, 10);

    Vector3<float>StartPosition {0, 0, 0};

    Vector3<float>StartVelocity {1, 1, 1};

    auto Bullet = Registry->create();
    Registry->emplace<ID>(Bullet, 0);
    Registry->emplace<Position>(Bullet, StartPosition);
    Registry->emplace<Velocity>(Bullet, StartVelocity);

    TestSystem.step(1.0);

    auto BulletPosition = Registry->get<Position>(Bullet);
    auto BulletVelocity = Registry->get<Velocity>(Bullet);


    REQUIRE(BulletVelocity.VelocityVector.y == -9.0f);
    REQUIRE(BulletPosition.Position == Vector3{1.0f, 1.0f, 1.0f});
}


TEST_CASE("Movement system bullet test move on 0 y", "[movement_system]")
{
    std::shared_ptr<entt::registry> Registry = std::make_shared<entt::registry>();

    MovementSystem TestSystem(Registry, 10);

    Vector3<float>StartPosition {0, 0, 0};

    Vector3<float>StartVelocity {1, -10, 1};

    auto Bullet = Registry->create();
    Registry->emplace<ID>(Bullet, 0);
    Registry->emplace<Position>(Bullet, StartPosition);
    Registry->emplace<Velocity>(Bullet, StartVelocity);

    TestSystem.step(1.0);

    auto BulletPosition = Registry->get<Position>(Bullet);
    auto BulletVelocity = Registry->get<Velocity>(Bullet);


    REQUIRE(BulletVelocity.VelocityVector.y == 0.0f);
    REQUIRE(BulletPosition.Position == Vector3{0.0f, 0.0f, 0.0f});
}


TEST_CASE("Movement system bullet test with aerodynamic", "[movement_system]")
{
    using namespace Catch::Matchers;

    std::shared_ptr<entt::registry> Registry = std::make_shared<entt::registry>();

    MovementSystem TestSystem(Registry, 10);

    Vector3<float>StartPosition {0, 0, 0};

    Vector3<float>StartVelocity {1, 1, 1};


    auto Bullet = Registry->create();
    Registry->emplace<ID>(Bullet, 0);
    Registry->emplace<Position>(Bullet, StartPosition);
    Registry->emplace<Velocity>(Bullet, StartVelocity);
    Registry->emplace<Weight>(Bullet, 1.0f);
    Registry->emplace<Aerodynamic>(Bullet, .1f, .1f);

    TestSystem.step(1.0);

    auto BulletPosition = Registry->get<Position>(Bullet);
    auto BulletVelocity = Registry->get<Velocity>(Bullet);


    REQUIRE_THAT(BulletVelocity.VelocityVector.y, WithinAbs(-9.01f, 0.001));
    REQUIRE_THAT(BulletVelocity.VelocityVector.x, WithinAbs(.98f, 0.01));
    REQUIRE_THAT(BulletVelocity.VelocityVector.z, WithinAbs(.98f, 0.01));
    REQUIRE(BulletPosition.Position == Vector3{1.0f, 1.0f, 1.0f});
}
