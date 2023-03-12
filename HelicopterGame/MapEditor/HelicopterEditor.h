#pragma once

#include <fstream>
#include <functional>
#include "Position.h"
#include "MapEditor.h"
#include "ConfirmationPanel.h"
#include "PanelRenderer.h"
#include "BlockPanel.h"

using namespace std;

class HelicopterEditor :
    public GameObject
{
    bool        isCompleted;

    GameObject* map;    // cache
    MapEditor* mapEditor;    // cache

    GameObject* save;
    GameObject* terminate;
    GameObject* load;

    GameObject* blockPanel1;
    GameObject* blockPanel2;
    GameObject* blockPanel3;

public:
    HelicopterEditor()
        : GameObject{ nullptr, "root", "root", nullptr, {1, 1}, {0, 0}, Position::zeros },
        isCompleted(false), map(nullptr), mapEditor(nullptr), save(nullptr), terminate(nullptr), load(nullptr), blockPanel1(nullptr), blockPanel2(nullptr), blockPanel3(nullptr)
    {
        //맵 에디터
        map = new GameObject(this, "map", "panel", nullptr, { 50, 20 }, { 1, 1 }, Position::zeros);
        map->getOrAddComponent<PanelRenderer>();
        mapEditor = map->getOrAddComponent<MapEditor>();

        //세이브 버튼
        save = new GameObject(this, "save", "button", nullptr, { 10, 2 }, { 2,25 }, Position::zeros);
        save->getOrAddComponent<PanelRenderer>();
        save->getOrAddComponent<Clickable>()->setOnClick([&]() { map->getComponent<MapEditor>()->save(); });

        //나가기 버튼
        terminate = new GameObject(this, "exit", "button", nullptr, { 10, 2 }, { 22,25 }, Position::zeros);
        terminate->getOrAddComponent<PanelRenderer>();
        terminate->getOrAddComponent<Clickable>()->setOnClick([&]() { isCompleted = true; });

        //로드 버튼
        load = new GameObject(this, "load", "button", nullptr, { 10, 2 }, { 42,25 }, Position::zeros);
        load->getOrAddComponent<PanelRenderer>();
        load->getOrAddComponent<Clickable>()->setOnClick([&]() { map->getComponent<MapEditor>()->load(); });

        //블럭 띄우는 패널1
        blockPanel1 = new GameObject(this, "block1", "panel", nullptr, { 6, 4 }, { 53,2 }, Position::zeros);
        blockPanel1->getOrAddComponent<PanelRenderer>();
        blockPanel1->getOrAddComponent<Clickable>()->setOnClick([&]() { map->getComponent<MapEditor>()->setBlock(176); });
        auto blockType1 = new GameObject(blockPanel1, "blockType1", "panel", "0", { 3,1 }, { 2, 2 }, Position::zeros);
        blockType1->getOrAddComponent<BlockPanel>()->setBlock(176); // 화면에 나올 블럭 종류 설정

        //블럭 띄우는 패널2
        blockPanel2 = new GameObject(this, "block2", "panel", nullptr, { 6, 4 }, { 53,9 }, Position::zeros);
        blockPanel2->getOrAddComponent<PanelRenderer>();
        blockPanel2->getOrAddComponent<Clickable>()->setOnClick([&]() { map->getComponent<MapEditor>()->setBlock(219); });
        auto blockType2 = new GameObject(blockPanel2, "blockType2", "panel", "0", { 3,1 }, { 2, 2 }, Position::zeros);
        blockType2->getOrAddComponent<BlockPanel>()->setBlock('\xdb'); // 화면에 나올 블럭 종류 설정

        //블럭 띄우는 패널3
        blockPanel3 = new GameObject(this, "block3", "panel", nullptr, { 6, 4 }, { 53,16 }, Position::zeros);
        blockPanel3->getOrAddComponent<PanelRenderer>();
        blockPanel3->getOrAddComponent<Clickable>()->setOnClick([&]() { map->getComponent<MapEditor>()->setBlock(178); });
        auto blockType = new GameObject(blockPanel3, "blockType3", "panel", "0", { 3,1 }, { 2, 2 }, Position::zeros);
        blockType->getOrAddComponent<BlockPanel>()->setBlock(178); // 화면에 나올 블럭 종류 설정
    }

    bool isGameOver() const { return isCompleted; }

    void update() override;
};

