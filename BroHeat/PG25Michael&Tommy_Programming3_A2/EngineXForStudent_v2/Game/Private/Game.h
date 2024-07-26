//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.h
// definition of MyGame, an implementation of exGameInterface
//

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include <memory>
#include <Game/Public/GameObject/Ball.h>
#include <Game/Public/GameObject/Brick.h>
#include <Game/Public/GameObject/Boundary.h>
#include <Game/Public/GameObject/BricksFactory.h>
#include <Game/Public/GameObject/Player.h>

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class MyGame : public exGameInterface
{
public:

								MyGame();
	virtual						~MyGame();

	virtual void				Initialize( exEngineInterface* pEngine );

	virtual const char*			GetWindowName() const;
	virtual void				GetClearColor( exColor& color ) const;

	virtual void				OnEvent( SDL_Event* pEvent );
	virtual void				OnEventsConsumed();

	virtual void				Run( float fDeltaT );

private:

	exEngineInterface*			mEngine;

	int							mFontID;

	bool						mUp;
	bool						mDown;
	bool						mLeft;
	bool						mRight;
	

	char*						mText;
	exVector2					mTextPosition;

	std::shared_ptr<Boundary>   mUpperBound;
	std::shared_ptr<Boundary>   mLeftBound;
	std::shared_ptr<Boundary>   mRightBound;
	std::shared_ptr<Boundary>   mBottomBound;


	std::shared_ptr<Ball>		mBall;
	float						mBallSpeed;

	std::shared_ptr<Player>     mPlayer;
	float						mPlayerSpeed;

	// Add the BricksFactory as a member variable
	std::unique_ptr<BricksFactory> mBricksFactory;

};
