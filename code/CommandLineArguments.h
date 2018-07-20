#pragma once

#include <filesystem>
#include <optional>

/// Handles parsing the command line arguments for the application.
class CommandLineArguments
{
public:
    // CONSTRUCTION.
    static std::optional<CommandLineArguments> Parse(
        const int argument_count,
        const char* const arguments[]);

    /// The root folder path for which to count lines.
    std::filesystem::path RootFolderPath = "";
};