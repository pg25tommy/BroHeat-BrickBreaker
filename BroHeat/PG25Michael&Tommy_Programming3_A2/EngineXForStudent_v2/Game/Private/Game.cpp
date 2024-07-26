//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game/Private/Game.h"

#include "Engine/Public/EngineInterface.h"
#include "Game/Public/GameObject/Ball.h"
#include "Engine/Public/SDL.h"
#include "Game/Public/Singletons/RenderEngine.h"
#include "Game/Public/Singletons/PhysicsEngine.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Sample EngineX Game";

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine( nullptr )
	, mFontID( -1 )
	, mUp( false )
	, mDown( false )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize( exEngineInterface* pEngine )
{
	mEngine = pEngine;
	mFontID = mEngine->LoadFont( "Resource/DragonHunter.otf", 32 );

	mTextPosition.x = 10.0f;
	mTextPosition.y = 10.0f;
	mText = (char*)"BroHeat - BrickBreaker!!";
	
	// to get screen size
	int screenWidth = 800; //  width
	int screenHeight = 600; // screen height 

	float paddleWidth = 150.0f; // paddle width
	float paddleHeight = 20.0f; // paddle height

	// Position the paddle close to the bottom of the screen
	exVector2 paddleSpawnLocation = { screenWidth / 2.0f - paddleWidth/2.0f, screenHeight - paddleHeight - 50.0f }; // 50 pixels above the bottom edge
	exVector2 paddleSize = exVector2{ paddleWidth,paddleHeight };

	mPlayerSpeed = 8.0f;

	mPlayer = std::make_shared<Player>(paddleSpawnLocation, paddleSize, exColor{ 255,255,0,255 }); // mRadius used as half-width here
	mPlayer->BeginPlay();

	


	mBallSpeed = 5.0f;

	mBall = std::make_shared<Ball>(10.0f ,paddleSpawnLocation + exVector2{ paddleWidth / 2.0f , -12.0f }, 10.0f, exColor{255,255,0,255});
	mBall->BeginPlay();


	// Bricks
	int rows = 6;
	int columns = 7;
	exVector2 startPosition = { 50.0f, 50.0f }; // Adjust starting position as needed
	float brickWidth = 90.0f;
	float brickHeight = 20.0f;
	float spacing = 5.0f;

	mBricksFactory = std::make_unique<BricksFactory>(mEngine, rows, columns, startPosition, brickWidth, brickHeight, spacing);
	mBricksFactory->CreateBricks();
	mBricksFactory->BeginPlay();


	//Boundary collision box
	mUpperBound = std::make_shared<Boundary>(exVector2{ 0.0f,-100.0f }, exVector2{ kViewportWidth, 100.0f }, exColor{ 0,0,0,255 });
	mUpperBound->BeginPlay();
	mLeftBound = std::make_shared<Boundary>(exVector2{ -100.0f,0.0f }, exVector2{ 100.0f, kViewportHeight }, exColor{ 0,0,0,255 });
	mLeftBound->BeginPlay();
	mRightBound = std::make_shared<Boundary>(exVector2{ kViewportWidth, 0.0f }, exVector2{ 100.0f, kViewportHeight }, exColor{ 0,0,0,255 });
	mRightBound->BeginPlay();
	/*
	mBottomBound = std::make_shared<Boundary>(exVector2{ 0.0f,kViewportHeight }, exVector2{ kViewportWidth, 100.0f }, exColor{ 0,0,0,255 });
	mBottomBound->BeginPlay();
	*/
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 128;
	color.mColor[1] = 128;
	color.mColor[2] = 128;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEvent( SDL_Event* pEvent )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{
	int nKeys = 0;
	const Uint8 *pState = SDL_GetKeyboardState( &nKeys );

	bool left = pState[SDL_SCANCODE_A];
	bool right = pState[SDL_SCANCODE_D];
	bool space = pState[SDL_SCANCODE_SPACE];

	if (mPlayer) { // Ensure mBall is initialized
		auto physicsComp = mPlayer->FindComponentOfType<PhysicsComponent>();
		auto transformComp = mPlayer->FindComponentOfType<TransformComponent>();
		if (left && transformComp->GetPosition().x > 0) {
			physicsComp->SetVelocity(exVector2{ -mPlayerSpeed, 0.0f }); // Adjust to desired speed
			if (!(mBall->IsStart())) {
				if (std::shared_ptr<PhysicsComponent> ballPhysicsComp = mBall->FindComponentOfType<PhysicsComponent>()) {
					ballPhysicsComp->SetVelocity(exVector2{ -mPlayerSpeed, 0.0 });
				}
			}
		}
		else if (right && transformComp->GetPosition().x + 150.0f < kViewportWidth) {
			physicsComp->SetVelocity(exVector2{ mPlayerSpeed, 0.0f }); // Adjust to desired speed
			if (!(mBall->IsStart())) {
				if (std::shared_ptr<PhysicsComponent> ballPhysicsComp = mBall->FindComponentOfType<PhysicsComponent>()) {
					ballPhysicsComp->SetVelocity(exVector2{ mPlayerSpeed, 0.0f });
				}
			}
		}
		else {
			physicsComp->SetVelocity(exVector2{ 0.0f, 0.0f }); // Stop moving when neither key is pressed
			if (!(mBall->IsStart())) {
				if (std::shared_ptr<PhysicsComponent> ballPhysicsComp = mBall->FindComponentOfType<PhysicsComponent>()) {
					ballPhysicsComp->SetVelocity(exVector2{ 0.0f, 0.0f });
				}
			}
		}
	}
	if (mBall) {
		if(!(mBall->IsStart()) && space ){
			if (std::shared_ptr<PhysicsComponent> physicsComp = mBall->FindComponentOfType<PhysicsComponent>()) {
				physicsComp->SetVelocity(exVector2{ 0.0f,-mBallSpeed });
			}
			mBall->StartMoving();
		}
	}
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{
	exColor c = {255,255,0,255 };
	//mText = (char *)"BroHeat - BrickBreaker!!";
	mEngine->DrawText( mFontID, mTextPosition, "BroHeat - BrickBreaker!!", c, 0 );
	mBricksFactory->UpdateBricks(fDeltaT);
	mBall->Tick(fDeltaT);

	RENDER_ENGINE.Render(mEngine);
	PHYSICS_ENGINE.Physics();

}
