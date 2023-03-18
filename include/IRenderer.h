#pragma once
class IRenderer {
public:
    virtual void Initialize(const char* windowName, const int windowWidth, const int windowHeight) = 0;
    virtual void Shutdown() = 0;
    virtual bool BeginFrame() = 0;
    virtual void EndFrame() = 0;
    //virtual void DrawRectangle();//int x, int y, int w, int h) = 0;
    // add more rendering functions as needed
};
