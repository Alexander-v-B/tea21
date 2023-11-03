#include <fmt/chrono.h>
#include <fmt/format.h>

#include <iostream>
#include <random>

#include "CLI/CLI.hpp"
#include "config.h"

int foo;

auto main(int argc, char **argv) -> int
{
   
    fmt::print("Value of variable foo {}, address of variable foo {}\n", foo, fmt::ptr(&foo));
    return 0; /* exit gracefully*/
}
