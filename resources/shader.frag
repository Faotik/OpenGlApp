#version 460 core

in vec3 out_color;
flat in int out_skip;
in vec3 out_normal;
in vec3 out_pos;
in float out_ambient;

out vec4 FragColor;

void main()
{
    if (out_skip == 1)
    {
        discard;
    }

    vec3 light_source_pos = vec3(200.0f, 800.0f, -200.0f);

    vec3 norm = normalize(out_normal);
    float diff = max(dot(norm, normalize(light_source_pos - out_pos)), 0.6);

    // FragColor = vec4(out_color.xyz * diff, 1.0);
    FragColor = vec4(out_color.xyz * (1 - out_ambient) * diff, 1.0);
}
