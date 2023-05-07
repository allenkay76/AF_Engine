#version 330 core
layout (location = 0) in vec3 LVertexPos2D;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord; 
uniform mat4 transform;

void main() { 
    gl_Position = transform * vec4(LVertexPos2D, 1.0f);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}