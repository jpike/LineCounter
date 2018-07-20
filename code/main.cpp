#include <cstdlib>
#include <iostream>
#include <optional>
#include "CommandLineArguments.h"
#include "Filesystem/DirectoryListing.h"
#include "LineCountStatistics.h"

int main(const int command_line_argument_count, const char* const command_line_arguments[])
{
    // PARSE THE COMMAND LINE ARGUMENTS.
    std::optional<CommandLineArguments> parsed_arguments = CommandLineArguments::Parse(
        command_line_argument_count, 
        command_line_arguments);
    if (!parsed_arguments)
    {
        std::cerr << "Invalid command line arguments." << std::endl;
        return EXIT_FAILURE;
    }

    // READ THE DIRECTORY LISTING.
    std::optional<FILESYSTEM::DirectoryListing> directory_listing = FILESYSTEM::DirectoryListing::Read(parsed_arguments->RootFolderPath);
    if (!directory_listing)
    {
        std::cerr << "Failed to get directory listing." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << directory_listing->ToTextString() << std::endl;

    // CALCULATE THE PRINT LINE COUNTS.
    LineCountStatistics line_count_statistics = LineCountStatistics::Calculate(*directory_listing);
    std::cout << line_count_statistics.ToTextString() << std::endl;
    std::cout << "Total Line Count: " << line_count_statistics.LineCount << std::endl;

    return EXIT_SUCCESS;
}
