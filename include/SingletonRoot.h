#pragma once

class SingletonRoot {
public:
    static SingletonRoot& getInstance();

protected:
    SingletonRoot(); // private constructor to prevent direct instantiation
    ~SingletonRoot(); // private destructor to prevent deletion of the instance
    SingletonRoot(const SingletonRoot&) = delete; // disable copy constructor
    SingletonRoot& operator=(const SingletonRoot&) = delete; // disable assignment operator
   
};
