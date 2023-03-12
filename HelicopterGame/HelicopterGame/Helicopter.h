#pragma once
#include "GameObject.h"
#include "Behaviour.h"
#include "Transform.h"
#include "MapScript.h"

struct HelicopterShape { 
	string		shape;
	Dimension	dim;
};

class Helicopter:
	public Behaviour
{
	float		currentX;
	float		currentY;
	float		speed;
	float		minSpeed;
	GameObject* map;
	MapScript* mapScript;
	char* shapeBuffer;
	bool isGrounded;
	Screen* screen;

public:
	Helicopter(GameObject* gameObject) : Behaviour(gameObject),
		map(gameObject->getParent()), shapeBuffer(nullptr), speed(0.1f), currentX(0.0f), currentY(0.0f), isGrounded(false),screen(nullptr)
	{
		auto pos = transform->getPos();
		auto dim = renderer->getDimension();
		currentX = (float)pos.x;
		currentY = (float)pos.y;
		shapeBuffer = new char[(size_t)dim.x * dim.y];
		mapScript = map->getComponent<MapScript>();
		minSpeed = mapScript->getSpeed();
	}

	~Helicopter() {
		if (shapeBuffer) {
			delete[] shapeBuffer;
		}
	}

	void start() override {
		currentX = 10.0f; currentY = 5.0f; //헬리콥터 시작 위치 설정
		speed = minSpeed + 1;
		gameObject->setName("Helicopter");
		transform->setPos((int)currentX, (int)currentY);
		screen = Screen::GetInstance();
	}

	void update() override {
		auto shape = renderer->getShape();
		auto pos = transform->getPos();
		auto dim = renderer->getDimension();
		auto width = dim.x;
		auto height = dim.y;

		//if (mapScript->isGrounded(shape, pos, width, height)) {
		//	//mapScript->place(shape, pos, width, height);
		//	//destroy(gameObject); //살릴지 말지 고민중
		//	//종료조건
		//	isGrounded = true;
		//	return;
		//}

		//게임오버 조건 추가해야됨

		if (input->getKey(VK_RIGHT)) {
			float nextX = currentX + 1.0f;
			if (mapScript->isValidRange({ (int)nextX, (int)currentY }, dim))
				currentX = nextX;
			speed += 0.1;
			return;
		}
		if (input->getKey(VK_LEFT)) {
			float nextX = currentX - 1.0f;
			if (mapScript->isValidRange({ (int)nextX, (int)currentY }, dim))
				currentX = nextX;
			speed -=0.1;
			if (speed <= minSpeed)
				speed = minSpeed;
			return;
		}
		if (input->getKey(VK_UP)) {
			float nextY = currentY - 1.0f;
			if (mapScript->isValidRange({ (int)currentX, (int)nextY }, dim))
				currentY = nextY;
			return;
		}
		if (input->getKey(VK_DOWN)) {
			float nextY = currentY + 1.0f;
			if (mapScript->isValidRange({ (int)currentX, (int)nextY }, dim))
				currentY = nextY;
			return;
		}
		if (input->getKey(VK_SPACE)) {
			return;
		}

		float nextX = currentX + speed;
		if (mapScript->isValidRange({ (int)nextX, (int)currentY }, dim)) {
			currentX = nextX;
		}
		transform->setPos((int)currentX, (int)currentY);

		Borland::Gotoxy(0, 36);
		printf("dim(%d, %d) (%f, %f)\n", dim.x, dim.y, currentX, currentY);

		transform->setPos((int)currentX, (int)currentY);
	}

	bool isDone() const { return isGrounded; }
	void setIsDone() { isGrounded = true; }

	static HelicopterShape OriginalShape()
	{
		static HelicopterShape originalShape
		{ "      \xDB\xDB\xDB\xDB\xDB         \xDB        \xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB \xDB \xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB       \xDB \xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB  ", {12, 8} };
		return originalShape;
	}


};

