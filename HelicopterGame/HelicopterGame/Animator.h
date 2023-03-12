#pragma once
#include "Component.h";
#include "GameObject.h"
#include "Helicopter.h"

class Renderer;

struct HelicopterSprite { //sprite 넣어서 애니메이션 만들 예정
	string		shape;
	Dimension	dim;
};

class Animator:
	public Component
{
	char* shapeBuffer;
	Renderer* renderer;

public:
	Animator(GameObject* gameObject)
		:Component(gameObject), shapeBuffer(nullptr), renderer(gameObject->getRenderer())
	{
		auto dim = renderer->getDimension();
		shapeBuffer = new char[(size_t)dim.x * dim.y];
	}

	void HelicopterAnimation() 
	{
		if(time(NULL)%4==0)
			renderer->setShape(sprites[0].shape.c_str());
		else if (time(NULL) % 4 == 1)
			renderer->setShape(sprites[1].shape.c_str());
		else if (time(NULL) % 4 == 2)
			renderer->setShape(sprites[2].shape.c_str());
		else if (time(NULL) % 4 == 3)
			renderer->setShape(sprites[3].shape.c_str());
		
		//임시 코드 지울것
		//printf("%d", time(NULL));
	}

	vector<HelicopterSprite> sprites{
		{ "      \xDB\xDB\xDB\xDB\xDB         \xDB        \xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB \xDB \xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB       \xDB \xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB  ", {12, 8}  },
		{ "       \xDB\xDB\xDB          \xDB        \xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB \xDB \xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB       \xDB \xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB  ", {12, 8}  },
		{ "        \xDB           \xDB        \xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB \xDB \xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB       \xDB \xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB  ", {12, 8}  },
		{ "       \xDB\xDB\xDB          \xDB        \xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB \xDB \xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB       \xDB \xDB      \xDB\xDB\xDB\xDB\xDB\xDB\xDB  ", {12, 8}  }
	};
};

