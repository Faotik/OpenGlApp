#include "app.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>

// bool check_shader(int shader)
// {
//     int success = 0;
//     glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//     if (success == GL_FALSE)
//     {
//         int log_size = 0;
//         glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
//         char *log = (char *)malloc(log_size);
//         glGetShaderInfoLog(shader, log_size, &log_size, log);
//         printf("%s", log);
//         free(log);

//         return false;
//     }

//     return true;
// }

// int app_init()
// {

//     SDL_Log("Check shaders:");

//     if (!check_shader(vertex_shader))
//     {
//         exit(-1);
//     }
//     if (!check_shader(fragment_shader))
//     {
//         exit(-1);
//     }

//     return 0;
// }

int main(int argc, char *argv[])
{
    App app;

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
