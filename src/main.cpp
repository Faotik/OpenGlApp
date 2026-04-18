#include "app.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>

int main(int argc, char *argv[])
{
    srand(time(nullptr));

    try
    {
        App app;
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
