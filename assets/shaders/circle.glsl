#vertex
#version 300 es

layout(location = 0) in vec2 worldPosition;
layout(location = 1) in vec2 localPosition;
layout(location = 2) in vec4 color;


uniform mat4 camera;

out vec2 v_localPos;
out vec4 v_circleColor;

void main() 
{
    gl_Position = camera * vec4(worldPosition, 0.0f, 1.0f);
    v_localPos = localPosition;
    v_circleColor = color;
}

#fragment
#version 300 es
precision mediump float;

in vec2 v_localPos;
in vec4 v_circleColor;

layout(location = 0) out vec4 fragColor;

void main() 
{
    vec3 circleColor = v_circleColor.rgb;
    float thickness = 0.05;
    float fade = 0.01;

    // Bereken de afstand tot het centrum (0,0) van de quad
    float distance = 1.0 - length(v_localPos);
    
    // Smoothstep voor anti-aliasing
    vec3 color = vec3(smoothstep(0.0, fade, distance));
    color *= vec3(smoothstep(thickness + fade, thickness, distance));

    // Pas de kleur toe
    fragColor = vec4(color * circleColor, color.r);
}