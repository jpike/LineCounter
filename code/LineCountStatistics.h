#pragma once

#include <cstddef>
#include <filesystem>
#include <limits>
#include <string>
#include <vector>
#include "Filesystem/DirectoryListing.h"

/// Line counts for a path (incorporating all child items within that path).
class LineCountStatistics
{
public:
    // CONSTRUCTION.
    static LineCountStatistics Calculate(const FILESYSTEM::DirectoryListing& directory_listing);
    explicit LineCountStatistics(const std::filesystem::path& path);

    // PRINTING.
    std::string ToTextString(
        const std::size_t indentation_level = 0,
        const std::size_t max_indentation_level = std::numeric_limits<std::size_t>::max()) const;

    // MEMBER VARIABLES.
    /// The path for which lines are counted by these statistics.
    std::filesystem::path Path = "";
    /// The total line count for this path (incorporating counts from all child folders/files).
    unsigned long long LineCount = 0;
    /// The line counts for child folders/files.
    std::vector<LineCountStatistics> ChildStatistics = {};
};