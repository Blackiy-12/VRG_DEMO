#include <ArgumentParser/ArgumentsParser.h>
#include <Simulation/Simulation.h>

#include <iostream>
#include <entt/entt.hpp>

int main(int argc, char** argv)
{

    ArgumentParser Parser(argc, argv);

    if (Parser.parseArguments() != OK)
    {
        std::cout << Parser.getErrorInfo();
        return 0;
    }

    auto UserData = Parser.getParsedArguments();

    Simulation Sim(UserData);

    Sim.run();
    
    return 0;
}