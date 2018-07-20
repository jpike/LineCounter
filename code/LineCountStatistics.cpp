#include "LineCountStatistics.h"

/// Calculates the line counts for the specified directory listing.
/// @param[in]  directory_listing - The directory listing for which to calculate line counts.
/// @return The line counts calculated for the specified directory listing.
LineCountStatistics LineCountStatistics::Calculate(const FILESYSTEM::DirectoryListing& directory_listing)
{
    LineCountStatistics total_line_count_statistics(directory_listing.RootFolder.Path);

    // COUNT LINES FOR FILES DIRECTLY IN THE CURRENT FOLDER.
    for (const auto& file : directory_listing.Files)
    {
        // COUNT LINES FOR THE CURRENT FILE.
        LineCountStatistics file_line_count_statistics(file.Path);
        file_line_count_statistics.LineCount = file.CountLines();

        // INCLUDE THE FILE'S LINES IN THE CURRENT STATISTICS.
        total_line_count_statistics.LineCount += file_line_count_statistics.LineCount;
        total_line_count_statistics.ChildStatistics.push_back(file_line_count_statistics);
    }

    // COUNT LINES FROM FILES IN ALL SUB-FOLDERS.
    for (const auto& subfolder : directory_listing.Subfolders)
    {
        // COUNT LINES FOR THE CURRENT SUB-FOLDER.
        LineCountStatistics subfolder_line_count_statistics = LineCountStatistics::Calculate(subfolder);

        // INCLUDE THE SUB-FOLDERS'S LINES IN THE CURRENT STATISTICS.
        total_line_count_statistics.LineCount += subfolder_line_count_statistics.LineCount;
        total_line_count_statistics.ChildStatistics.push_back(subfolder_line_count_statistics);
    }

    return total_line_count_statistics;
}

/// Constructor.
/// @param[in]  path - The path to which these statistics apply.
LineCountStatistics::LineCountStatistics(const std::filesystem::path& path) :
    Path(path),
    LineCount(0),
    ChildStatistics()
{}

/// Prints the statistics to a hierarchically-indented string.
/// @param[in]  indentation_level - The current indentation level used to print the current statistics.
///     Child statistics will be printed at deeper indentation levels.
/// @param[in]  max_indentation_level - The maximum indentation level to print.
///     If more child statistics exist at deeper indentation levels than this, they won't be printed.
/// @return A string representation of the statistics.
std::string LineCountStatistics::ToTextString(const std::size_t indentation_level, const std::size_t max_indentation_level) const
{
    // DON'T RETURN ANY STRING IF THE MAX INDENTATION LEVEL HAS BEEN EXCEEDED.
    bool max_indentation_level_exceeded = (indentation_level > max_indentation_level);
    if (max_indentation_level_exceeded)
    {
        return "";
    }

    // PRINT STATISTICS FOR THE CURRENT PATH.
    const char INDENTATION_CHARACTER = '\t';
    std::string indentation(indentation_level, INDENTATION_CHARACTER);
    std::ostringstream line_count_string;
    line_count_string << indentation << Path << INDENTATION_CHARACTER << LineCount << std::endl;

    // PRINT ALL CHILD STATISTICS.
    for (const auto& child_line_counts : ChildStatistics)
    {
        std::size_t child_indentation_level = indentation_level + 1;
        line_count_string << child_line_counts.ToTextString(child_indentation_level, max_indentation_level);
    }

    return line_count_string.str();
}