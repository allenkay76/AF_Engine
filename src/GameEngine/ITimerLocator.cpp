#include "GameEngine/ITimer.h"
ITimer* ITimerLocator::m_service = &ITimerLocator::m_nullService;
NullITimer ITimerLocator::m_nullService;

void ITimerLocator::initialize() {
    m_service = &m_nullService;
}

ITimer* ITimerLocator::getTimer() {
    return m_service;
}