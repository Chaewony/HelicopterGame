#pragma once
#include "GameObject.h"
#include "Behavior.h"

class BlockPanel:
	public Behavior
{
	char buffer[3];
	char block;
public:
	BlockPanel(GameObject* gameObject) : Behavior(gameObject), block(176) {
		sprintf(buffer, "%c", block);
	}

	void update() override {

		sprintf(buffer, "%c", block);
		renderer->setShape(buffer);
	}

	void setBlock(const char block) { this->block = block; update(); }
	char getBlock() const { return block; }
};

