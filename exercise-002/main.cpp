#include <fmt/chrono.h>
#include <fmt/format.h>
#include <cstdlib>

#include "CLI/CLI.hpp"
#include "config.h"

void printVec(std::vector<int> vec){

    for (int &num : vec){
        fmt::print("{}\n", num);
    }

}

auto main(int argc, char **argv) -> int
{
    CLI::App app{PROJECT_NAME};

    int count = 20;

    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.add_option("-c,--count", count, "Count variable");
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
    fmt::print("Count value: {}!\n", count);

    std::vector<int> vec(count);
    for (int &num : vec){
        /**
         * rand liefert Werte zwischen 0 und maximum
         * module 100 schränkt es auf Werte von 0 bis 99
         * + 1 verschiebt es auf 1 bis 100
        */
        num = std::rand() % 100  + 1;
    }

    printVec(vec);
    /* INSERT YOUR CODE HERE */

    return 0; /* exit gracefully*/
}
