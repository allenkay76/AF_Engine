#include "SingletonRoot.h"

SingletonRoot::SingletonRoot() {}

SingletonRoot::~SingletonRoot() {}

SingletonRoot& SingletonRoot::getInstance() {
    static SingletonRoot instance;
    return instance;
}

