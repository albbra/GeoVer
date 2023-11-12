#version 460 core
#pragma optimize(on)

layout(location = 0)
in vec4 inVertex;

void main()
{	
    gl_Position = vec4(inVertex.xy, 0.0, 1.0);
}
