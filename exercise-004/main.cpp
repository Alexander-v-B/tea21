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

    for(int y = 0; y < bmp.m_infoHeader.biHeight; y++){
        for(int x = 0; x < bmp.m_infoHeader.biWidth; x++){
            bmp.pixel_buffer.at(y * bmp.m_infoHeader.biWidth + x).red = bmp.pixel_buffer.at(y * bmp.m_infoHeader.biWidth + x).alpha;
            bmp.pixel_buffer.at(y * bmp.m_infoHeader.biWidth + x).green = bmp.pixel_buffer.at(y * bmp.m_infoHeader.biWidth + x).alpha;
            bmp.pixel_buffer.at(y * bmp.m_infoHeader.biWidth + x).blue = bmp.pixel_buffer.at(y * bmp.m_infoHeader.biWidth + x).alpha;
        }
     }

    bmp.write(filename);


    return 0; /* exit gracefully*/
}
