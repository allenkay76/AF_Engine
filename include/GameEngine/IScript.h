#pragma once
class IScript {
public:
    virtual void Awake() = 0;
    virtual void Start() = 0;
    virtual void Update() = 0;

    virtual ~IScript() {}
};
