#pragma once
/*
This is an interface class for a rendering engine. 
It provides a set of pure virtual functions that define the basic operations that a renderer must support. 
These functions include initialization and shutdown of the renderer, 
as well as beginning and ending frames for rendering. 
Additional rendering functions can be added as needed by inheriting from this interface class 
and implementing the desired functions.


*/
class IRenderer {
public:
    virtual void Initialize(const char* windowName, const int windowWidth, const int windowHeight) = 0;
    virtual void Shutdown() = 0;
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    // add more rendering functions as needed
};

/*
In C++, when a member function is declared as "pure virtual" using the "= 0" syntax, 
it means that the function has no implementation in the base class, 
and it must be overridden by derived classes.
This is a way to create an abstract class, which cannot be instantiated directly, 
but can serve as a base class for other classes. 
The idea is that the derived classes must provide their own implementation for the pure virtual functions, 
which allows for polymorphism and dynamic dispatch.
*/