#include "Scene.h"

void Scene::update() {    

    if (input->getKey(VK_ESCAPE)) {
        isCompleted = true;
        return;
    }

    if (currentBlock->isAlive() == false) {
        map->removeChild(currentBlock);
        delete currentBlock;
        nextBlock->setParent(map);
        currentBlock = nextBlock;
        currentBlock->getOrAddComponent<BlockScript>()->start();
        currentBlock->getOrAddComponent<BlockScript>()->setStartPoint(150, 0);

        nextBlockShape = BlockScript::ChooseShape();
        nextBlock = new GameObject{ this, "nextBlock", "block", nextBlockShape.shape,
                nextBlockShape.dim, {-10,0}, Position::zeros };
    }


    helicopter->getComponent<Animator>()->HelicopterAnimation();

    internalRemove();
    //게임 오버 조건
    if (helicopter->getComponent<Helicopter>()->isDone()) {
        isCompleted = true;
        return;
    }

    /*if (helicopter->getOrAddComponent<Collider>()->getIsCollision())
    {
        isCompleted = true;
        return;
    }*/

    internalRender(Position::zeros, false);
    internalUpdate();
}
