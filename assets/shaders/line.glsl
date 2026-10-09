#vertex

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

uniform mat4 camera;

out vec4 v_lineColor;

void main()
{
    v_lineColor = color;
	gl_Position = camera * vec4(position, 1.0f);
}

#fragment

precision mediump float;

in vec4 v_lineColor;

layout(location = 0) out vec4 color;
void main()
{
	color = v_lineColor;
}