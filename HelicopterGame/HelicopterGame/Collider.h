#pragma once
#include "Component.h";
#include "GameObject.h"
#include "Helicopter.h"
#include "MapScript.h"

class Collider
	: public Component
{
	Renderer* renderer;
	GameObject* collision;
	bool isCollision;
	GameObject* map;
	vector <Position> colliderPos;

public:
	Collider(GameObject* gameObject)
		:Component(gameObject), renderer(gameObject->getRenderer()), collision(nullptr), isCollision(false), map(nullptr)
	{
		auto dim = renderer->getDimension();
	}

	void update() override
	{
		
		//checkCollider(gameObject);
		
	}

	void SetTarget(GameObject* collision)
	{
		this->collision = collision;
	}


	bool getIsCollision()
	{
		return isCollision;
	}

	void SetMap(GameObject* map)
	{
		this->map = map;
	}

	void checkCollision(GameObject* collision)
	{
		checkCollider(gameObject);
		vector <Position> collisionColliderPos = collision->getComponent<Collider>()->checkCollider(collision);

		for (int i = 0; i < colliderPos.size()-1; i++)
		{
			for (int j = 0; j < collisionColliderPos.size(); j++)
			{
				if(colliderPos[i]== collisionColliderPos[j])
					gameObject->getComponent<Helicopter>()->setIsDone();
			}
		}
	}

	vector<Position> checkCollider(GameObject* collision)
	{
		auto shape = renderer->getShape();
		auto pos = getTransform()->getPos();
		auto dim = renderer->getDimension();
		auto width = dim.x;
		auto height = dim.y;
		

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (shape[j + i * width] != ' ') {
					colliderPos.push_back({ pos.x + renderer->offset2Pos(j + i * width).x,pos.y + renderer->offset2Pos(j + i * width).y });
				}
			}
		}

		return colliderPos;
	}

	vector<Position> getColliderPos()
	{
		return colliderPos;
	}
};

