#version 330 core

in vec2 LVertexPos2D;
in float LColVal;

uniform mat4 projectionMatrix; // Add this line to declare the projectionMatrix uniform

out float FragColor;

void main() {
    gl_Position = projectionMatrix * vec4(LVertexPos2D, 0.0, 1.0);
    FragColor = LColVal;
}
