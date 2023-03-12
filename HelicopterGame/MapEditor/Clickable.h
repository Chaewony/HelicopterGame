#pragma once
#include <functional>
#include "Panel.h"
#include "Component.h"
#include "Behavior.h"
#include "MapEditor.h"

class Clickable :
    public Behavior
{
    std::function<void(void)> onClick;
    MapEditor* map;

    bool isInside(const Position& pos) const {
        auto myPos = getTransform();
        return 0 <= pos.x && renderer->getDimension().x >= pos.x && 0 <= pos.y && renderer->getDimension().y >= pos.y;
    }

    string title;

public:
    Clickable(GameObject* gameObject)
        : Behavior(gameObject), title(gameObject->getName()), map(nullptr)
    {
        renderer->setShape(title.c_str());
    }

    void update()
    {
        if (input->getMouseButtonDown(0)) {
            auto pos = transform->screen2Local(input->getMousePosition());
            if (isInside(pos)) {
                onClick();
            }
        }
    }

    void setOnClick(std::function<void()> func = [&]() {}) { onClick = func; }
};
