
#version 330 core

in vec4 FragColor;
out vec4 LFragment; 

void main() { 
    LFragment = FragColor;//vec4(FragColor.x, FragColor.y, FragColor.y, 1.0); 
}

