/*
 * This is a minimal eaxmple of a useful service example using glibmm and giomm.
 * And it compiles...
 *
 * Build: clang  -std=c++17 -O2 -Werror -Weverything -Wall $(pkg-config --cflags --libs glibmm-2.4 giomm-2.4) mainpp.cc DBusApp.cc -lstdc++
 *
*/

#include <iostream>
#include <memory>

#include "DBusApp.hpp"

int main(int, char**)
{
    std::locale::global(std::locale(""));
    DBusApp::InitEnv();

    auto app = std::make_unique<DBusApp>();
    app->Run();

    return 0;
}

