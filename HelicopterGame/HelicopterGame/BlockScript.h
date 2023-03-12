#pragma once
#include "GameObject.h"
#include "Behaviour.h"
#include "Transform.h"
#include "MapScript.h"

struct BlockShape {
	const char*		shape;
	Dimension	dim;
};

class BlockScript
	: public Behaviour
{
	float		currentX;
	float		currentY;
	float		speed;
	GameObject* map;
	MapScript* mapScript;
	char* shapeBuffer;

public:
	BlockScript(GameObject* gameObject) : Behaviour(gameObject),
		map(gameObject->getParent()), shapeBuffer(nullptr), speed(0.1f), currentX(0.0f), currentY(0.0f) //speed 없어도 될듯
	{
		auto pos = transform->getPos();
		auto dim = renderer->getDimension();
		currentX = (float)pos.x;
		currentY = (float)pos.y;
		shapeBuffer = new char[(size_t)dim.x * dim.y];
		mapScript = map->getComponent<MapScript>();
	}

	~BlockScript() {
		if (shapeBuffer) {
			delete[] shapeBuffer;
		}
	}

	void start() override {
		auto dim = renderer->getDimension();
		//currentX = map->getComponent<Renderer>()->getWidth() - dim.x;
		currentX = 50.0f;
		currentY = 0.0f;
		speed = 2;
		gameObject->setName("currentBlock");
		transform->setPos((int)currentX, (int)currentY);

	}

	void update() override {
		auto shape = renderer->getShape();
		auto pos = transform->getPos();
		auto dim = renderer->getDimension();
		auto width = dim.x;
		auto height = dim.y;

		//mapScript->place(shape, pos, width, height);

		if (mapScript->isGrounded(shape, pos, width, height)) {
			mapScript->place(shape, pos, width, height);
			for (int i = height - 1; i >= 0; --i) {
				int nCombos = 0;
				/*while (mapScript->evaluateLine(pos.y + i)) {
					nCombos++;
				}*/
			}
			//mapScript->clean();
			destroy(gameObject);
			return;
		}
		/*float nextX = currentX - speed;
		if (mapScript->isValidRange({ (int)nextX, (int)currentY }, dim)) {
			currentX = nextX;
		}
		transform->setPos((int)currentX, (int)currentY);*/
		/*float nextX = currentX - speed;
		currentX = nextX;
		transform->setPos((int)currentX, (int)currentY);*/
	}

	static BlockShape ChooseShape() {
		static vector<BlockShape> candidates{
			{ "\xDB\xDB \xDB \xDB", {2, 3}	},
			{ "\xDB\xDB\xDB\xDB",	{2, 2}	},
			{ "\xDB\xDB\xDB\xDB",	{4, 1}	},
			{ "\xDB\xDB\xDB \xDB ", {2, 3}	},
			{ " \xDB\xDB\xDB\xDB ", {2, 3}	},
			{ " \xDB\xDB\xDB \xDB", {2, 3}	},
			{ "\xDB \xDB\xDB \xDB", {2, 3}  }
		};
		return candidates[rand() % candidates.size()];
	}

	void setStartPoint(int x, int y)
	{
		currentX = x;
		currentY = y;
	}
};

