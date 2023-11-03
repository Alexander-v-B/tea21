#include <fmt/chrono.h>
#include <fmt/format.h>

#include <iostream>
#include <random>

#include "CLI/CLI.hpp"
#include "config.h"

auto main(int argc, char **argv) -> int
{
   
    fmt::print("Hello, {}!\n", "hello !");
    return 0; /* exit gracefully*/
}
