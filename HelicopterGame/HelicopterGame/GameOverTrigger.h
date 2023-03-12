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
			//			collision->getComponent<Collider>()->checkCollision(gameObject); // 헬리콥터 기준으로 블록을 게임오브젝트로 받아온다. => 그리고 나서 블럭의 공백제외 pos값 저장 => 헬리콥터에도 공백/흰부분 비교
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

