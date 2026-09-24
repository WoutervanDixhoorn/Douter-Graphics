#vertex

layout(location = 0) in vec4 position;
uniform mat4 camera;

void main()
{
	gl_Position = camera * position;
}

#fragment

precision mediump float;

layout(location = 0) out vec4 color;
void main()
{
	color = vec4(1.0, 1.0, 1.0, 1.0);
}