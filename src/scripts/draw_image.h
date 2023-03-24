#pragma once
#include "GameEngine/IScript.h"
#include "Utils/LogManager.h"

class draw_image : public IScript {
public:
    void Awake() override {
        // Implementation code for Awake function
        LogManager::Log("MyScript::Awake() called");
    }

    void Start() override {
        // Implementation code for Start function
        LogManager::Log("MyScript::Start() called");
    }

    void Update() override {
        // Implementation code for Update function
        LogManager::Log("MyScript::Update() called");
    }
};