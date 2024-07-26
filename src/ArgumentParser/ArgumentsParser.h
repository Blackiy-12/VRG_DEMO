#pragma once

#include <ArgumentParser/Arguments.h>

#include <string>

enum ParseResult
{
    OK = 0,
    
    USER_WANT_HELP = 1,

    USER_GIVE_ZERO_ARG = 2,

    NOT_ENOUGH_VALUES_FOR_ARGUMENT = 11,

    DOUBLE_DEFINE = 12,

    NOT_ALL_ARGUMENTS_DEFINED = 13,

    UNKNOWN_ERROR = 99,
};

class ArgumentParser
{
public:

    /**
     * @warning Maybe dangling pointer on argv
     */
    ArgumentParser(int argc, char** argv);


    ~ArgumentParser();


    /**
     * @brief Parse used CLI arguments and modify parsed arguments
     * @retval OK - on success. Other - on failure, for more info use getErrorInfo
     */
    ParseResult parseArguments();


    /**
     * @brief Return error info
     * @return String with info about error
     * @warning Must call if parse end with error
     */
    std::string getErrorInfo() const;


    /**
     * @brief Return parsed arguments
     * @return Arguments struct
     * @warning Must call after succeed parse
     */
    Arguments getParsedArguments() const;

private:
    Arguments m_ParsedArguments{};


    std::string m_LastError = "";


    int m_ArgumentCount = 0;


    char** m_Arguments = nullptr;

    struct ArgumentChecker
    {
        bool Start = false;
        bool Goal = false;
        bool Velocity = false;
        bool Weight = false;
        bool SimsStep = false;

        bool isAllChecked()
        {
            return Start && Goal && Velocity && Weight && SimsStep;
        }
    };

    ArgumentChecker m_Checker{};

private:

    /**
     * @brief Parse for start arguments and modify ParsedArguments
     * @param ArgumentNumber - where first value of argument
     * @return OK - on success
     * @return Others - on failure, more info in LastError
     */
    ParseResult parseStartArgument(int ArgumentNumber);

    
    /**
     * @brief Parse for goal arguments and modify ParsedArguments
     * @param ArgumentNumber - where first value of argument
     * @return OK - on success
     * @return Others - on failure, more info in LastError
     */
    ParseResult parseGoalArgument(int ArgumentNumber);

    
    /**
     * @brief Parse for velocity arguments and modify ParsedArguments
     * @param ArgumentNumber - where value of argument
     * @return OK - on success
     * @return Others - on failure, more info in LastError
     */
    ParseResult parseVelocityArgument(int ArgumentNumber);


    /**
     * @brief Parse for weight arguments and modify ParsedArguments
     * @param ArgumentNumber - where value of argument
     * @return OK - on success
     * @return Others - on failure, more info in LastError
     */
    ParseResult parseWeightArgument(int ArgumentNumber);
    

    /**
     * @brief Parse for simulation step arguments and modify ParsedArguments
     * @param ArgumentNumber - where value of argument
     * @return OK - on success
     * @return Others - on failure, more info in LastError
     */
    ParseResult parseSimStepArgument(int ArgumentNumber);


    /**
     * @brief Check if string is number
     * @param String - string to check
     * @return true - string is number
     * @return false - string is not a number
     */
    bool isNumber(const std::string &String);
};