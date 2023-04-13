#include "GameEngine/IInput.h"
IInput* IInputLocator::m_service = &IInputLocator::m_nullService;
NullIInput IInputLocator::m_nullService;

void IInputLocator::initialize() {
    m_service = &m_nullService;
}

IInput* IInputLocator::getInput() {
    return m_service;
}