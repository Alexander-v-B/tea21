#include <fmt/chrono.h>
#include <fmt/format.h>
#include <cstdlib>

#include "CLI/CLI.hpp"
#include "config.h"

void printVec(std::vector<int> vec){

    fmt::print("----------------\n");
    for (int &num : vec){
        fmt::print("{}, ", num);
    }

}

void sortVec(std::vector<int> vec, int count){

    auto start = std::chrono::system_clock::now();

    /**
     * for (int i = 0; i < count; i++){
        for (int j = 1; j < count; j++){
            if(vec.at(j) < vec.at(j - 1)){
                std::swap(vec[j], vec[j-1]);
            }
        }
    } 
    */

    std::sort(vec.begin(), vec.end());

    auto end = std::chrono::system_clock::now();

    auto elapse = std::chrono::duration_cast<std::chrono::milliseconds> (end - start);
    fmt::print("Verstrichene Zeit {}\n", elapse);

    printVec(vec);

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

    std::srand(time(NULL));

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
    sortVec(vec, count);
    /* INSERT YOUR CODE HERE */

    return 0; /* exit gracefully*/
}
