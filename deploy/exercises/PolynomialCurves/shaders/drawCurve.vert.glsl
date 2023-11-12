#version 400 core
#pragma optimize(on)

in vec2 inVertex;

uniform mat3 u_transformationMatrix;

void main()
{	    
    vec3 p = vec3(inVertex.xy, 1.0);
    gl_Position	= vec4(p.xy, 0.0, 1.0);
}
