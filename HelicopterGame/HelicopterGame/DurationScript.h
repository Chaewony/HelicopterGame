#pragma once
#include "GameObject.h"
#include "Behaviour.h"

class DurationScript:
	public Behaviour
{
	int playTime;
	char buffer[3];
	int startTime;

public:
	DurationScript(GameObject* gameObject) :Behaviour(gameObject), playTime(0), startTime(time(NULL) % 1000){
		sprintf(buffer, "%3d", playTime);
	}
	void update() override {
		//printf("%d", time(NULL));
		//playTime = time(NULL);
		playTime = time(NULL) % 1000 - startTime;
		sprintf(buffer, "%3d", playTime);
		renderer->setShape(buffer);
	}
	void setValue(int value) { this->playTime = value; }
	int getValue() const { return playTime; }

};

