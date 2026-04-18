#version 460 core

in vec3 out_color;
flat in int out_skip;
in vec3 out_normal;
in vec3 out_pos;

out vec4 FragColor;

void main()
{
    if (out_skip == 1)
    {
        discard;
    }

    vec3 light_source_pos = vec3(200.0f, 800.0f, -200.0f);

    vec3 norm = normalize(out_normal);
    float diff = max(dot(norm, normalize(light_source_pos - out_pos)), 0.2);

    FragColor = vec4(out_color.xyz * diff, 1.0);
}
