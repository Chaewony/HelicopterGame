#include "GameObject.h"
#include "Behavior.h"

Behavior::Behavior(GameObject* gameObject)
	: Component(gameObject), input(Input::GetInstance()) {
	renderer = gameObject->getComponent<Renderer>();
}