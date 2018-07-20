#include "CommandLineArguments.h"

/// Attempts to parse command line arguments.
/// @param[in]  argument_count - The number of arguments.
/// @param[in]  arguments - The arguments to parse.
/// @return The arguments, if successfully parsed.
std::optional<CommandLineArguments> CommandLineArguments::Parse(
    const int argument_count,
    const char* const arguments[])
{
    // MAKE SURE ENOUGH COMMAND LINE ARGUMENTS WERE PROVIDED.
    // The first argument should be the path to the invoked program.
    // After that, one argument is expected.
    const int EXPECTED_COMMAND_LINE_ARGUMENT_COUNT = 2;
    bool enough_command_line_arguments_provided = (argument_count >= EXPECTED_COMMAND_LINE_ARGUMENT_COUNT);
    if (!enough_command_line_arguments_provided)
    {
        // INDICATE THAT NO COMMAND LINE ARGUMENTS COULD BE PARSED.
        return std::nullopt;
    }

    // PARSE THE ROOT FOLDER PATH.
    CommandLineArguments command_line_arguments;

    const unsigned int ROOT_FOLDER_PATH_COMMAND_LINE_ARGUMENT_INDEX = 1;
    command_line_arguments.RootFolderPath = arguments[ROOT_FOLDER_PATH_COMMAND_LINE_ARGUMENT_INDEX];

    return command_line_arguments;
}