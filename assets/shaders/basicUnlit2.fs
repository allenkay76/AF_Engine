
#version 330 core

in float FragColor;
out vec4 LFragment; 

void main() { 
    LFragment = vec4(FragColor, 0.5, 0.5, 1.0); 
}

