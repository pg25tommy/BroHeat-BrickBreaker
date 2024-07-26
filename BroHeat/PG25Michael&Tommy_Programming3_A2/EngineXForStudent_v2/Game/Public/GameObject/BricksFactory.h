#pragma once

#include "Engine/Public/EngineInterface.h"
#include "Game/Public/GameObject/Brick.h"
#include <vector>

class BricksFactory : GameObject
{
public:
    BricksFactory(exEngineInterface* pEngine, int rows, int columns, const exVector2& startPosition, float brickWidth, float brickHeight, float spacing);
    ~BricksFactory();

    void Tick(float delta);
    void CreateBricks();
    void BeginPlay();
    void UpdateBricks(float delta);
    //void RenderBricks();

private:
    exEngineInterface* mEngine;
    std::vector< std::shared_ptr<Brick>> mBricks;
    int mRows;
    int mColumns;
    exVector2 mStartPosition;
    float mBrickWidth;
    float mBrickHeight;
    float mSpacing;

    // could add more
};

