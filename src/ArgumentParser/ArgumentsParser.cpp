#include "ArgumentsParser.h"

#include <regex>

const std::string HelpArg = "-h";

const std::string StartArg = "-s";

const std::string GoalArg = "-g";

const std::string VelocityArg = "-v";

const std::string WeightArg = "-w";

const std::string SimStepArg = "-step";


ArgumentParser::ArgumentParser(int argc, char** argv)
{
    m_ArgumentCount = argc;
    m_Arguments = argv;
}


ArgumentParser::~ArgumentParser()
{

}


ParseResult ArgumentParser::parseArguments()
{
    if(m_ArgumentCount < 2)
    {
        m_LastError = "No arguments to parse";
        return USER_GIVE_ZERO_ARG;
    }

    for (int ArgumentNumber = 1; ArgumentNumber < m_ArgumentCount; ArgumentNumber++)
    {
        std::string_view ArgumentString = m_Arguments[ArgumentNumber];

        ParseResult Result = OK;

        if (ArgumentString.compare(HelpArg) == 0)
        {
            return USER_WANT_HELP;
        }

        else if (ArgumentString.compare(StartArg) == 0)
        {
            ArgumentNumber++;
            Result = parseStartArgument(ArgumentNumber);
            if(Result != OK) return Result;
            ArgumentNumber+= 2;
        }

        else if (ArgumentString.compare(GoalArg) == 0)
        {
            ArgumentNumber++;
            Result = parseGoalArgument(ArgumentNumber);
            if(Result != OK) return Result;
            ArgumentNumber+= 2;
        }

        else if (ArgumentString.compare(VelocityArg) == 0)
        {
            ArgumentNumber++;
            Result = parseVelocityArgument(ArgumentNumber);
            if(Result != OK) return Result;
        }
        else if (ArgumentString.compare(WeightArg) == 0)
        {
            ArgumentNumber++;
            Result = parseWeightArgument(ArgumentNumber);
            if(Result != OK) return Result;
        }
        else if (ArgumentString.compare(SimStepArg) == 0)
        {
            ArgumentNumber++;
            Result = parseSimStepArgument(ArgumentNumber);
            if(Result != OK) return Result;
        }
        
    }

    if(m_Checker.isAllChecked() == false)
    {
        m_LastError = "You need to define all arguments";
        return NOT_ALL_ARGUMENTS_DEFINED;
    }


    return OK;
}


std::string ArgumentParser::getErrorInfo() const
{
    return m_LastError;
}


Arguments ArgumentParser::getParsedArguments() const
{
    return m_ParsedArguments;
}

ParseResult ArgumentParser::parseStartArgument(int ArgumentNumber)
{
    if(m_Checker.Start == true)
    {
        m_LastError = "Start argument(-s) must be only one";
        return DOUBLE_DEFINE;
    }

    //X
    if (ArgumentNumber >= m_ArgumentCount)
    {
        m_LastError = "Start argument(-s) must have 3 floats, you give nothing";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    std::string ArgumentString = m_Arguments[ArgumentNumber];
    if (isNumber(ArgumentString) == false)
    {
        m_LastError = "Start argument(-s) must have 3 floats, you give nothing";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    m_ParsedArguments.Start.x = strtof(ArgumentString.data(), nullptr);
    ArgumentNumber++;

    //Y
    if (ArgumentNumber >= m_ArgumentCount)
    {
        m_LastError = "Start argument(-s) must have 3 floats, you give 1";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    ArgumentString = m_Arguments[ArgumentNumber];
    if (isNumber(ArgumentString) == false)
    {
        m_LastError = "Start argument(-s) must have 3 floats, you give 1";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    m_ParsedArguments.Start.y = strtof(ArgumentString.data(), nullptr);
    ArgumentNumber++;

    //Z
    if (ArgumentNumber >= m_ArgumentCount)
    {
        m_LastError = "Start argument(-s) must have 3 floats, you give 2";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    ArgumentString = m_Arguments[ArgumentNumber];
    if (isNumber(ArgumentString) == false)
    {
        m_LastError = "Start argument(-s) must have 3 floats, you give 2";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    m_ParsedArguments.Start.z = strtof(ArgumentString.data(), nullptr);

    m_Checker.Start = true;

    return OK;
}

    
ParseResult ArgumentParser::parseGoalArgument(int ArgumentNumber)
{
    
    if(m_Checker.Goal == true)
    {
        m_LastError = "Goal argument(-g) must be only one";
        return DOUBLE_DEFINE;
    }

    //X
    if (ArgumentNumber >= m_ArgumentCount)
    {
        m_LastError = "Goal argument(-g) must have 3 floats, you give nothing";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    std::string ArgumentString = m_Arguments[ArgumentNumber];
    if (isNumber(ArgumentString) == false)
    {
        m_LastError = "Goal argument(-g) must have 3 floats, you give nothing";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    m_ParsedArguments.Goal.x = strtof(ArgumentString.data(), nullptr);
    ArgumentNumber++;

    //Y
    if (ArgumentNumber >= m_ArgumentCount)
    {
        m_LastError = "Goal argument(-g) must have 3 floats, you give 1";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    ArgumentString = m_Arguments[ArgumentNumber];
    if (isNumber(ArgumentString) == false)
    {
        m_LastError = "Goal argument(-g) must have 3 floats, you give 1";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    m_ParsedArguments.Goal.y = strtof(ArgumentString.data(), nullptr);
    ArgumentNumber++;

    //Z
    if (ArgumentNumber >= m_ArgumentCount)
    {
        m_LastError = "Goal argument(-g) must have 3 floats, you give 2";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    ArgumentString = m_Arguments[ArgumentNumber];
    if (isNumber(ArgumentString) == false)
    {
        m_LastError = "Goal argument(-g) must have 3 floats, you give 2";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    m_ParsedArguments.Goal.z = strtof(ArgumentString.data(), nullptr);

    m_Checker.Goal = true;

    return OK;
}


ParseResult ArgumentParser::parseVelocityArgument(int ArgumentNumber)
{
    if (m_Checker.Velocity == true)
    {
        m_LastError = "Velocity(-v) must be only one";
        return DOUBLE_DEFINE;
    }

    if (ArgumentNumber >= m_ArgumentCount)
    {
        m_LastError = "Velocity(-v) must have 1 float, you give nothing";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    std::string ArgumentString = m_Arguments[ArgumentNumber];
    if (isNumber(ArgumentString) == false)
    {
        m_LastError = "Velocity(-v) must have 1 float, you give nothing";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    m_ParsedArguments.StartVelocity = strtof(ArgumentString.data(), nullptr);

    m_Checker.Velocity = true;

    return OK;
}


ParseResult ArgumentParser::parseWeightArgument(int ArgumentNumber)
{
    if (m_Checker.Weight == true)
    {
        m_LastError = "Weight(-w) must be only one";
        return DOUBLE_DEFINE;
    }

    if (ArgumentNumber >= m_ArgumentCount)
    {
        m_LastError = "Weight(-w) must have 1 float, you give nothing";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    std::string ArgumentString = m_Arguments[ArgumentNumber];
    if (isNumber(ArgumentString) == false)
    {
        m_LastError = "Weight(-w) must have 1 float, you give nothing";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    m_ParsedArguments.Weight = strtof(ArgumentString.data(), nullptr);

    m_Checker.Weight = true;

    return OK;
}
    

ParseResult ArgumentParser::parseSimStepArgument(int ArgumentNumber)
{
    if (m_Checker.SimsStep == true)
    {
        m_LastError = "Simulation step(-step) must be only one";
        return DOUBLE_DEFINE;
    }


    if (ArgumentNumber >= m_ArgumentCount)
    {
        m_LastError = "Simulation step(-step) must have 1 float, you give nothing";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    std::string ArgumentString = m_Arguments[ArgumentNumber];
    if (isNumber(ArgumentString) == false)
    {
        m_LastError = "Simulation step(-step) must have 1 float, you give nothing";
        return NOT_ENOUGH_VALUES_FOR_ARGUMENT;
    }
    m_ParsedArguments.SimStep = strtof(ArgumentString.data(), nullptr);

    m_Checker.SimsStep = true;

    return OK;
}


bool ArgumentParser::isNumber(const std::string &String)
{
    std::regex Pattern("(^\\d*\\.?\\d+f?$)");
    std::smatch Matches;

    return std::regex_match(String, Matches, Pattern);
}