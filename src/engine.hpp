#pragma once

#include <SDL3/SDL_video.h>
#include <glad/glad.h>
#include <string>

class Engine
{
public:
    enum class MEMORY_BARRIER_TYPE
    {
        SHADER_STORAGE_BARRIER = GL_SHADER_STORAGE_BARRIER_BIT,
    };

    void init(const std::string window_title, int init_window_width, int init_window_height);
    void clear_window(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 1.0);
    void swap_window();
    static std::string read_file(const std::string &filename);
    float get_time_seconds();
    void memory_barrier(MEMORY_BARRIER_TYPE type);
    ~Engine();

private:
    SDL_Window *m_window = nullptr;
    SDL_GLContext m_glcontext = nullptr;

private:
    void init_window(const std::string window_title, int init_window_width, int init_window_height);
    void init_debug();
    static void glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message,
                              const void *userParam);
};