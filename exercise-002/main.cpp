#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More inpo at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};

    int count = 20;
    app.add_option("-c,--count", count, "Count variable");

    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());

    std::vector<int> vec(count);
    for (int &num : vec){
        /**
         * rand liefert Werte zwischen 0 und maximum
         * module 100 schränkt es auf Werte von 0 bis 99
         * + 1 verschiebt es auf 1 bis 100
        */
        num = std::rand() % 100  + 1;
    }

    /* INSERT YOUR CODE HERE */

    return 0; /* exit gracefully*/
}
