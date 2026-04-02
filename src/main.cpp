#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>
#include <glad/glad.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static SDL_Window *window;
static SDL_GLContext glcontext;

static bool is_app_running = true;

static const int init_window_width = 1000;
static const int init_window_height = 800;

unsigned int shader_program;

void read_file(const char *path, char *out, int buffer_size)
{
    FILE *fp = fopen(path, "r");

    int i = 0;
    char c;
    while ((c = fgetc(fp)) != EOF)
    {
        if (i == buffer_size)
        {
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Could not read the entire shader '%s' because it is longer than %d characters",
                        path, buffer_size);
            break;
        }
        i++;
        *out = c;
        out++;
    }
    *out = '\0';

    fclose(fp);
}

bool check_shader(int shader)
{
    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        int log_size = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
        char *log = (char *)malloc(log_size);
        glGetShaderInfoLog(shader, log_size, &log_size, log);
        printf("%s", log);
        free(log);

        return false;
    }

    return true;
}

int app_init()
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        SDL_Log("SDL failed to initialise");
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow("TestApp", init_window_width, init_window_height, SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        SDL_Log("SDL failed to create a window");
        return -2;
    }

    glcontext = SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -3;
    }

    glViewport(0, 0, init_window_width, init_window_height);

    // Shaders
    unsigned int buffer_size = 0xFFFF;
    char *buffer = (char *)malloc(sizeof(char) * buffer_size);

    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    read_file("./resources/vertex.glsl", buffer, buffer_size);
    glShaderSource(vertex_shader, 1, (const GLchar *const *)(&buffer), NULL);
    glCompileShader(vertex_shader);

    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    read_file("./resources/fragment.glsl", buffer, buffer_size);
    glShaderSource(fragment_shader, 1, (const GLchar *const *)(&buffer), NULL);
    glCompileShader(fragment_shader);

    SDL_Log("Check shaders:");

    if (!check_shader(vertex_shader))
    {
        exit(-1);
    }
    if (!check_shader(fragment_shader))
    {
        exit(-1);
    }

    shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    free(buffer);

    return 0;
}

void app_destroy()
{
    SDL_GL_DestroyContext(glcontext);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void render()
{
    float time = ((float)SDL_GetTicks()) / 1000;

    const float vertices[] = {
        -1.0f, -1.0f, 0.0f, //
        -1.0f, 1.0f,  0.0f, //
        1.0f,  1.0f,  0.0f, //
        1.0f,  -1.0f, 0.0f  //
    };

    // VBO, VAO

    glClearColor(1.0, 1.0, 1.0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    GLuint EBO;
    glGenBuffers(1, &EBO);

    GLuint indices[] = {
        0, 1, 2, 0, 2, 3 //
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    int uniform_time_location = glGetUniformLocation(shader_program, "time");

    glUseProgram(shader_program);

    glUniform1f(uniform_time_location, time);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
    SDL_GL_SwapWindow(window);
}

void events()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            is_app_running = false;
            return;
        case SDL_EVENT_KEY_DOWN:
            switch (event.key.key)
            {
            case SDLK_ESCAPE:
                is_app_running = false;
                return;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int init_status = app_init();
    if (init_status < 0)
    {
        return init_status;
    }

    while (is_app_running)
    {
        render();
        events();
    }

    app_destroy();

    return 0;
}
