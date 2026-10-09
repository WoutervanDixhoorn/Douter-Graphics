#vertex

layout(location = 0) in vec3 worldPosition;
layout(location = 1) in vec2 localPosition;
layout(location = 2) in vec4 color;
layout(location = 3) in float fillLevel;


uniform mat4 camera;

out vec2 v_localPos;
out vec4 v_circleColor;
out float v_circleFillLevel;

void main() 
{
    gl_Position = camera * vec4(worldPosition, 1.0f);
    v_localPos = localPosition;
    v_circleColor = color;
    v_circleFillLevel = fillLevel;
}

#fragment

precision mediump float;

in vec2 v_localPos;
in vec4 v_circleColor;
in float v_circleFillLevel;

layout(location = 0) out vec4 fragColor;

void main() 
{
    vec3 circleColor = v_circleColor.rgb;
    float thickness = v_circleFillLevel;
    float fade = 0.01;

    // Bereken de afstand tot het centrum (0,0) van de quad
    float distance = 1.0 - length(v_localPos);
    
    // Smoothstep voor anti-aliasing
    vec3 color = vec3(smoothstep(0.0, fade, distance));
    color *= vec3(smoothstep(thickness + fade, thickness, distance));

    // Pas de kleur toe
    fragColor = vec4(color * circleColor, color.r);
}