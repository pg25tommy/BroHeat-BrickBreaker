#include "Game/Public/GameObject/BricksFactory.h"
#include "Engine/Public/EngineInterface.h"


BricksFactory::BricksFactory(exEngineInterface* pEngine, int rows, int columns, const exVector2& startPosition, float brickWidth, float brickHeight, float spacing)
    : mEngine(pEngine), mRows(rows), mColumns(columns), mStartPosition(startPosition), mBrickWidth(brickWidth), mBrickHeight(brickHeight), mSpacing(spacing) {
}

BricksFactory::~BricksFactory() {

    // Destructor code here if needed
}

void BricksFactory::Tick(float delta)
{

    UpdateBricks(delta);
}

void BricksFactory::CreateBricks() {
    for (int row = 0; row < mRows; ++row) {
        for (int col = 0; col < mColumns; ++col) {
            //set position
            float positionX = mStartPosition.x + col * (mBrickWidth + mSpacing);
            float positionY = mStartPosition.y + row * (mBrickHeight + mSpacing);
            // Set the brick color to red
            exColor color = { 255, 0, 0, 255 }; // RGB for red, 255 for fully opaque

            int health = 3; // health?
            
            std::shared_ptr<Brick> brick = std::make_shared<Brick>(health, exVector2{ positionX,positionY }, exVector2{mBrickWidth,mBrickHeight}, color);

            //brick->FindComponentOfType<PhysicsComponent>()->ListenToCollision( );

            mBricks.push_back(brick);
        }
    }
}



void BricksFactory::BeginPlay()
{
    GameObject::BeginPlay();

    for (int i = 0; i < mBricks.size(); i++)
    {
        mBricks[i]->BeginPlay();
    }

}
void BricksFactory::UpdateBricks(float delta)
{
    
    auto it = mBricks.begin();
    while(it != mBricks.end()){
        (*it)->Tick(delta);
        if (!((*it)->IsAlive())) {
            it = mBricks.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
/*
void BricksFactory::RenderBricks() {
    for (const auto& brick : mBricks) {
        if (brick.GetHealth()  > 0) {
            exVector2 topLeft = brick.GetPosition();
            exVector2 bottomRight = { topLeft.x + mBrickWidth, topLeft.y + mBrickHeight };
            //mEngine->DrawBox(topLeft, bottomRight, brick.color, 0);
        }
    }
}
*/



//check collision with ball?
