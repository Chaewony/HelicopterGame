#pragma once

#include "Position.h"
#include "GameObject.h"
#include "PanelRenderer.h"
#include "DurationScript.h"
#include "MapScript.h"
#include "Helicopter.h"
#include "Animator.h"
#include "BlockScript.h"
#include "GameOverTrigger.h"
#include "Collider.h"

using namespace std;

class Scene : public GameObject
{
    bool    isCompleted;
    Input*  input;
    MapScript* mapScript;
    GameObject* helicopter;
    
    GameObject* frontGamePanel;
    GameObject* backGamePanel;
    GameObject* map;
    GameObject* duration;
    GameObject* currentBlock;
    GameObject* nextBlock;
    BlockShape          nextBlockShape;

public:

    Scene() 
        : GameObject{ nullptr, "root", "root", nullptr, {1, 1}, {0, 0}, Position::zeros }, isCompleted(false),
        input( Input::GetInstance() ), mapScript(nullptr), map(nullptr), helicopter(nullptr)
    {
        // 맵
        map = new GameObject(this, "map", "panel", nullptr, { 700, 20 }, { 2,2 }, Position::zeros);
        mapScript = map->getOrAddComponent<MapScript>();

        // 헬리콥터
        auto helicopterShape = Helicopter::OriginalShape();
        helicopter = new GameObject{ map, "helicopter", "helicopter", helicopterShape.shape.c_str(),
            helicopterShape.dim, {5,0},  Position::zeros };
        helicopter->addComponent<Helicopter>();
        helicopter->addComponent<Animator>();
        //helicopter->addComponent<Collider>();

        // 시간 패널 및 시간(value)
        duration = new GameObject(this, "duration", "panel", nullptr, { 10,3 }, { 22, 23 }, Position::zeros);
        duration->getOrAddComponent<PanelRenderer>()->setTitle(" Time ");
        auto time = new GameObject(duration, "duration", "time", "0", { 3,1 }, { 3, 1 }, Position::zeros);
        //auto durationScript = time->getOrAddComponent<DurationScript>();
        time->getOrAddComponent<DurationScript>();

        // 블럭(장애물)
        auto blockShape = BlockScript::ChooseShape();
        currentBlock = new GameObject{ map, "currentBlock", "block", blockShape.shape,
            blockShape.dim, {5,0},  Position::zeros };
        currentBlock->addComponent<BlockScript>();
        currentBlock->getOrAddComponent<GameOverTrigger>()->SetTarget(helicopter);
        currentBlock->getOrAddComponent<Collider>();

        nextBlockShape = BlockScript::ChooseShape();
        nextBlock = new GameObject{ this, "nextBlock", "block", nextBlockShape.shape,
            nextBlockShape.dim, {-10,0}, Position::zeros };
        /*nextBlock->getOrAddComponent<GameOverTrigger>()->SetTarget(helicopter);
        currentBlock->getOrAddComponent<Collider>();*/

        //게임 패널
        frontGamePanel = new GameObject(this, "map", "panel", nullptr, { 1, 20 }, { 78,1 }, Position::zeros);
        frontGamePanel->getOrAddComponent<PanelRenderer>();
        //frontGamePanel->getOrAddComponent<GameOverTrigger>()->SetTarget(helicopter);
        backGamePanel = new GameObject(this, "map", "panel", nullptr, { 1, 20 }, { 1,1 }, Position::zeros);
        backGamePanel->getOrAddComponent<PanelRenderer>();
        //backGamePanel->getOrAddComponent<GameOverTrigger>()->SetTarget(helicopter);

        helicopter->getOrAddComponent<Collider>()->SetTarget(currentBlock);
        helicopter->getOrAddComponent<Collider>()->SetMap(map);
        //helicopter->getOrAddComponent<Collider>()->SetHelicopter(helicopter);
        

        internalStart();
    }

    void start() override { internalStart(); }

    void update() override;

    bool isSceneOver() const { return isCompleted; }

#if 0
    void update() override {
        if (confirm && confirm->isActive() == false) {
            remove(confirm);
            delete confirm;
            confirm = nullptr;
        }
        if (input->getKey(VK_ESCAPE)) {
            auto dim = getDimension();
            confirm = new ConfirmationPanel{ getPos() + Position{ dim.x / 2 - 25/2, dim.y / 2 - 5/2}, 25, 5, this,
                [&]() { map->setFreeze(false); }, // if clicked cancel
                [&]() { isCompleted = true; } // if clicked okay
            };
            map->setFreeze(true);
        }
    }
#endif
};

