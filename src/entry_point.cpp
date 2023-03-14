#include <cstdio>
#include "Application.h"

int main(int argc, char* args[]) {
	printf("Starting AF_Engine entry point \n");
    printf("Number of arguments: %d\n", argc);
    printf("First argument: %s\n", args[0]);
    Application* application = new Application();
    const char* engineName = "AF_Engine";
    application->appData.applicationName = engineName;
    application->appData.windowXPos = 0;
    application->appData.windowYPos = 0;
    application->appData.windowWidth = 720;
    application->appData.windowHeight = 640;
    application->appData.fullscreen = false;
	return 0;
}