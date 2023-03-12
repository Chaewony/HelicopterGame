#pragma once
#include <iostream>
#include <fstream>
//#include "Panel.h"
#include "GameObject.h"
#include "Behavior.h"

class MapEditor : public Behavior {
	bool* map;
	int* blockTypeMap;

	//static const char rectFill = '\xdb';
	unsigned char rectFill = 176;

	bool isInside(const Position& pos) const {
		auto myPos = getTransform();
		return 0 <= pos.x && renderer->getDimension().x >= pos.x && 0 <= pos.y && renderer->getDimension().y >= pos.y;
	}

public:
	MapEditor(GameObject* gameObject) : Behavior(gameObject), map(nullptr)
	{
		auto dim = renderer->getDimension();
		auto width = dim.x;
		auto height = dim.y;

		map = new bool[(size_t)dim.x * dim.y];
		blockTypeMap = new int[(size_t)dim.x * dim.y];

		for (int i = 0; i < width * height; i++)
			map[i] = false;
		for (int i = 0; i < width * height; i++)
			blockTypeMap[i] = 0;
		load();
	}

	~MapEditor() { if (map) delete[] map; }

	bool isValidRange(const Position& nextPos, const Dimension& sz)
	{
		auto pos = getTransform();
		if (nextPos.x < 0 || nextPos.x > renderer->getWidth() || nextPos.y < 0 || nextPos.y > renderer->getHeight()) return false;
		if (nextPos.x + sz.x > renderer->getWidth() || nextPos.y + sz.y > renderer->getHeight()) return false;
		return true;
	}

	void save() {
		ofstream mapFile;

		//�� ��ġ ������ ����
		mapFile.open("map.txt", ofstream::trunc);
		auto capacity = renderer->getCapacity();
		for (int i = 0; i < capacity; i++)
		{
			mapFile << map[i] ? '1' : '0';
		}
		mapFile.close();

		//��ġ�� �� Ÿ���� ����
		mapFile.open("blockMap.txt", ofstream::trunc);
		for (int i = 0; i < capacity; i++)
		{
			mapFile << blockTypeMap[i];
		}
		mapFile.close();
	}

	void load() {
		ifstream mapFile;
		auto capacity = renderer->getCapacity();

		//�� ��ġ ������ �ε��ϴ� ������
		char* data = new char[capacity];
		mapFile.open("map.txt");
		memset(map, false, sizeof(bool) * capacity);
		if (mapFile.is_open() == false) {
			return;
		}
		if (!mapFile.eof()) {
			mapFile.getline(data, capacity);
		}
		mapFile.close();
		for (int i = 0; i < capacity; i++)
		{
			if (data[i] == '1') map[i] = true;
		}

		//��ġ�� �� Ÿ���� �����ϴ� ������
		char* blockType = new char[capacity];
		mapFile.open("blockMap.txt");
		memset(blockTypeMap, false, sizeof(int) * capacity);
		if (mapFile.is_open() == false) {
			return;
		}
		if (!mapFile.eof()) {
			mapFile.getline(blockType, capacity);
		}
		mapFile.close();
		for (int i = 0; i < capacity; i++)
		{
			blockTypeMap[i] = blockType[i]-'0'; //char���� blockType[i]�� ���ڸ� int������ blockTypeMap�� ����, �� blockTypeMap���� �� �ѹ�(1,2,3,0)�� ���� �ȴ�.
		}

		delete[] data;
		delete[] blockType;

		draw();
	}

	void update()
	{
		//GameObject::update();
		if (input->getMouseButtonDown(0)) {
			auto pos = transform->screen2Local(input->getMousePosition());
			if (isInside(pos)) {
				auto offset = renderer->pos2Offset(pos);
				map[offset] = !map[offset];
				renderer->setShape(map[offset] ? rectFill : ' ', offset);

				if (map[offset])
					blockTypeMap[offset] = rectFill2BlockNum(rectFill);
				else
					blockTypeMap[offset] = 0;
			}
		}
	}

	void draw()
	{
		//Panel::draw(); // draw border lines

		auto height = renderer->getDimension().y;
		auto width = renderer->getDimension().x;
		for (auto i = 0; i < height; i++) {
			for (auto j = 0; j < width; j++) {
				renderer->setShape(map[j + i * width] ? BlockNum2rectFill(blockTypeMap[j + i * width]) : ' ', j + i * width);
			}
		}
		//GameObject::draw(); // draw shape
	}

	void setBlock(const char block) { this->rectFill = block; }
	char getBlock() const { return rectFill; }
	int rectFill2BlockNum(const unsigned char rectFill) {
		if (rectFill == 176)
		{
			return 1;
		}
		else if (rectFill == 219)
		{
			return 2;
		}
		else if (rectFill == 178)
		{
			return 3;
		}
		else return 0;
	}
	unsigned char BlockNum2rectFill(const char blockNum) {
		if (blockNum == 1)
		{
			return 176;
		}
		else if (blockNum == 2)
		{
			return 219;
		}
		else if (blockNum == 3)
		{
			return 178;
		}
		else return ' ';
	}
};