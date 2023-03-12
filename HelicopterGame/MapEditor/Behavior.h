#pragma once
#include "Input.h"
#include "Component.h"
#include "Renderer.h"

class Renderer;

class Behavior :
    public Component
{
protected:
    Input* input;
    Renderer* renderer;

public:
    Behavior(GameObject* gameObject);

    virtual ~Behavior() {}
};
