#pragma once
#include <mutex>

class SingletonRoot {
public:
    // Deleted copy constructor and assignment operator to prevent copying
    SingletonRoot(const SingletonRoot&) = delete;
    SingletonRoot& operator=(const SingletonRoot&) = delete;

    // Get the singleton instance of SingletonRoot
    static SingletonRoot& getInstance() {
        // Call the helper function to get the unique instance
        static SingletonRoot instance;
        return instance;
    }

protected:
    // Default constructor for SingletonRoot
    SingletonRoot() = default;

    // Destructor for SingletonRoot
    virtual ~SingletonRoot() = default;
};

