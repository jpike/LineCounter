#pragma once

#include <filesystem>

/// Holds code for interacting with computer filesystems.
namespace FILESYSTEM
{
    /// A file.
    class File
    {
    public:
        // CONSTRUCTION.
        explicit File(const std::filesystem::path& path);

        // LINE COUNTING.
        unsigned long long CountLines() const;

        // MEMBER VARIABLES.
        /// The path to the file.
        std::filesystem::path Path = "";
    };
}
