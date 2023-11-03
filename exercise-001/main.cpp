#include <fmt/chrono.h>
#include <fmt/format.h>

#include <iostream>
#include <random>

#include "CLI/CLI.hpp"
#include "config.h"

int foo;

// .bss segment
int bss = 0;
// .data segment
int data = 4711;

// .rodata segment
const int rodata = 42;


auto main(int argc, char **argv) -> int
{
   // .stack segment
    int stack = 12;

   // output lines
    fmt::print("Value of variable foo {}, address of variable foo {}\n", foo, fmt::ptr(&foo));
    fmt::print("Value of variable bss {}, address of variable bss {}\n", bss, fmt::ptr(&bss));
    fmt::print("Value of variable data {}, address of variable data {}\n", data, fmt::ptr(&data));
    fmt::print("Value of variable rodata {}, address of variable rodata {}\n", rodata, fmt::ptr(&rodata));
    fmt::print("Value of variable stack {}, address of variable stack {}\n", stack, fmt::ptr(&stack));
    return 0; /* exit gracefully*/
}
