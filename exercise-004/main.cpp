#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h.in"
#include <string.h>
#include "BMP.h"

auto main(int argc, char **argv) -> int
{

    std::string filename{DEFAULT_BMP_FILE};

    CLI::App app{PROJECT_NAME};
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.add_option("-f,--file", filename, fmt::format("Create a vector with the given size default: {}", filename));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    BMP bmp;
    bmp.read(filename);


    return 0; /* exit gracefully*/
}
