#pragma once
#include "Component.h";
#include "GameObject.h"
#include "Helicopter.h"
#include "MapScript.h"
#include "Collider.h"

class GameOverTrigger
	: public Component
{
	Renderer* renderer;
	GameObject* collision;
	GameObject* map;

public:
	GameOverTrigger(GameObject* gameObject)
		:Component(gameObject), renderer(gameObject->getRenderer()), collision(nullptr), map(nullptr)
	{
		//auto dim = renderer->getDimension();
	}

	void update() override
	{
		/*auto pos = transform->getPos();
		auto dim = renderer->getDimension();*/

		auto pos = transform->getPos();
		auto dim = renderer->getDimension();
		auto width = dim.x;
		auto height = dim.y;
		auto shape = renderer->getShape();

		auto collisionPos = collision->getTransform()->getPos();
		auto collisionDim = collision->getRenderer()->getDimension();

		/*if ((collisionPos.x + collisionDim.x >= pos.x && collisionPos.x + collisionDim.x <= pos.x + dim.x)
			|| (collisionPos.x >= pos.x && collisionPos.x <= pos.x + dim.x))
		{
			collision->getComponent<Helicopter>()->setIsDone();
		}*/
		/*if ((collisionPos.x + collisionDim.x >= pos.x && collisionPos.y >= pos.y + dim.y)
			|| (collisionPos.x + collisionDim.x >= pos.x && collisionPos.y + collisionDim.y <= pos.y)
			|| (collisionPos.x <= pos.x + dim.x && collisionPos.y + collisionDim.y <= pos.y)
			|| (collisionPos.x <= pos.x + dim.x && collisionPos.y >= pos.y + dim.y))
		{
			collision->getComponent<Helicopter>()->setIsDone();
		}*/
		if ((collisionPos.x + collisionDim.x >= pos.x && collisionPos.y <= pos.y + dim.y))
		{
			//for (int i = 0; i < collisionDim.y; i++) {
			//	for (int j = 0; j < collisionDim.x; j++) {
			//		if (shape[j + i * collisionDim.x] != ' ') {
			//			//collision->getComponent<Helicopter>()->setIsDone();
			//			collision->getComponent<Collider>()->checkCollision(gameObject); // �︮���� �������� ����� ���ӿ�����Ʈ�� �޾ƿ´�. => �׸��� ���� ���� �������� pos�� ���� => �︮���Ϳ��� ����/��κ� ��
			//		}
			//	}
			//}
			collision->getComponent<Collider>()->checkCollision(gameObject);
		}
	} 

	void SetTarget(GameObject* collision)
	{
		this->collision = collision;
	}

	void SetMap(GameObject* map)
	{
		this->map = map;
	}
};

