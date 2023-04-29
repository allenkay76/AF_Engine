#include "GameEngine/IRenderer.h"
IRenderer* IRendererLocator::m_service = &IRendererLocator::m_nullService;
NullIRenderer IRendererLocator::m_nullService;

void IRendererLocator::initialize() {
    m_service = &m_nullService;
}

IRenderer* IRendererLocator::getRenderer() {
    return m_service;
}