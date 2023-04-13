#pragma once
#include <SDL2/SDL.h>
#include "GameEngine/ITimer.h"


class SDLGameTimer: public ITimer {   // Define the SDLGameInput class and inherit from ITimer

public:

    bool Initialize() override;       // Declare the Initialize function, which is a pure virtual function in ITimer
    void Shutdown() override;         // Declare the Shutdown function, which is a pure virtual function in ITimer

    void start() override;            // Declare the start function, which is implemented in this class
    void stop() override;             // Declare the stop function, which is implemented in this class
    void pause() override;            // Declare the pause function, which is implemented in this class
    void unpause() override;          // Declare the unpause function, which is implemented in this class

    int getTicks() const override;    // Declare the getTicks function, which is implemented in this class and returns an int

    bool isStarted() override;        // Declare the isStarted function, which is implemented in this class and returns a bool
    bool isPaused() override;         // Declare the isPaused function, which is implemented in this class and returns a bool

    // Implement other rendering functions using SDL2 API
    // (no additional functions implemented in this class)

    SDLGameTimer();                   // Declare the constructor for the SDLGameTimer class
    ~SDLGameTimer();                  // Declare the destructor for the SDLGameTimer class
private:
    // The clock time when the timer started
    unsigned int startTicks;          // This is an unsigned int, which is 4 bytes on most systems

    // The clock time when the timer was paused
    unsigned int pausedTicks;         // This is an unsigned int, which is 4 bytes on most systems

    // The timer status
    bool paused;                      // This is a bool, which is 1 byte on most systems
    bool started;                     // This is a bool, which is 1 byte on most systems

};

// Total memory used by the class:
// 2 bytes for padding (due to the bools being placed next to each other)
// 8 bytes for the two unsigned int variables
// 2 bytes for padding (due to the bools and unsigned ints requiring 4-byte alignment)
// 2 bytes for the bool variables
// So the total memory used by this class on most systems would be 14 bytes.
