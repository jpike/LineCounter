#include <fstream>
#include <string>
#include "Filesystem/File.h"

namespace FILESYSTEM
{
    /// Constructor.
    /// @param[in]  path - The path to the file.
    File::File(const std::filesystem::path& path) :
        Path(path)
    {}

    /// Counts the number of lines in the file.
    /// @return The number of lines in the file.
    unsigned long long File::CountLines() const
    {
        // OPEN THE FILE.
        std::ifstream file(Path);

        // COUNT EACH LINE.
        unsigned long long line_count = 0;
        std::string line;
        while (std::getline(file, line))
        {
            ++line_count;
        }

        return line_count;
    }
}
