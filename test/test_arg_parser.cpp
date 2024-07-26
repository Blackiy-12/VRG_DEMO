#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>


#include <ArgumentParser/ArgumentsParser.h>

char AppArg[] = "App";

char HelpArg[] = "-h";

char StartArg[] = "-s";

char GoalArg[] = "-g";

char VelocityArg[] = "-v";

char WeightArg[] = "-w";

char SimStepArg[] = "-step";

char Integer[] = "1";

char FullFloat[] = "1.5f";

char HalfFloat[] = ".5f";


TEST_CASE("Parse 0 arg", "[arg]")
{
    char* argv[] = {
        AppArg
    };

    ArgumentParser Parser(1, argv);

    REQUIRE(Parser.parseArguments() == USER_GIVE_ZERO_ARG);
}

TEST_CASE("Parse all args", "[arg]")
{
    char* argv[] = {
        AppArg,
        StartArg, FullFloat, FullFloat, FullFloat, 
        GoalArg, FullFloat, FullFloat, FullFloat, 
        VelocityArg, FullFloat,
        WeightArg, FullFloat,
        SimStepArg, FullFloat
        };

    ArgumentParser Parser(15, argv);

    REQUIRE(Parser.parseArguments() == OK);

    auto Arg = Parser.getParsedArguments();

    Vector3<float> Target{1.5f, 1.5f, 1.5f};

    REQUIRE(Arg.Goal == Target);
    REQUIRE(Arg.Start == Target);

    
    using namespace Catch::Matchers;

    REQUIRE_THAT(Arg.SimStep, WithinRel(1.5f, 0.0001f));
    REQUIRE_THAT(Arg.StartVelocity, WithinRel(1.5f, 0.0001f));
    REQUIRE_THAT(Arg.Weight, WithinRel(1.5f, 0.0001f));
}

TEST_CASE("Parse all args with half float", "[arg]")
{
    char* argv[] = {
        AppArg,
        StartArg, HalfFloat, HalfFloat, HalfFloat, 
        GoalArg, HalfFloat, HalfFloat, HalfFloat, 
        VelocityArg, HalfFloat,
        WeightArg, HalfFloat,
        SimStepArg, HalfFloat
        };

    ArgumentParser Parser(15, argv);

    REQUIRE(Parser.parseArguments() == OK);

    auto Arg = Parser.getParsedArguments();

    Vector3<float> Target{.5f, .5f, .5f};

    REQUIRE(Arg.Goal == Target);
    REQUIRE(Arg.Start == Target);

    
    using namespace Catch::Matchers;

    REQUIRE_THAT(Arg.SimStep, WithinRel(.5f, 0.0001f));
    REQUIRE_THAT(Arg.StartVelocity, WithinRel(.5f, 0.0001f));
    REQUIRE_THAT(Arg.Weight, WithinRel(.5f, 0.0001f));
}

TEST_CASE("Parse not all args", "[arg]")
{
    char* argv[] = {
        AppArg,
        StartArg, HalfFloat, HalfFloat, HalfFloat, 
        SimStepArg, HalfFloat
        };

    ArgumentParser Parser(7, argv);

    REQUIRE(Parser.parseArguments() == NOT_ALL_ARGUMENTS_DEFINED);
}

TEST_CASE("Parse arg with not all value", "[arg]")
{
    char* argv[] = {
        AppArg,
        StartArg, HalfFloat, HalfFloat
        };

    ArgumentParser Parser(4, argv);

    REQUIRE(Parser.parseArguments() == NOT_ENOUGH_VALUES_FOR_ARGUMENT);
}

TEST_CASE("Parse arg with wrong value", "[arg]")
{
    char* argv[] = {
        AppArg,
        StartArg, AppArg, HalfFloat
        };

    ArgumentParser Parser(4, argv);

    REQUIRE(Parser.parseArguments() == NOT_ENOUGH_VALUES_FOR_ARGUMENT);
}

TEST_CASE("Parse arg with help", "[arg]")
{
    char* argv[] = {
        AppArg,
        HelpArg
        };

    ArgumentParser Parser(2, argv);

    REQUIRE(Parser.parseArguments() == USER_WANT_HELP);
}

TEST_CASE("Parse arg with help and all args", "[arg]")
{
    char* argv[] = {
        AppArg,
        StartArg, FullFloat, FullFloat, FullFloat, 
        GoalArg, FullFloat, FullFloat, FullFloat, 
        VelocityArg, FullFloat,
        WeightArg, FullFloat,
        SimStepArg, FullFloat,
        HelpArg
        };

    ArgumentParser Parser(16, argv);

    REQUIRE(Parser.parseArguments() == USER_WANT_HELP);
}