#pragma once
#include "GameEngine.h"

#define BALLX 0
#define BALLY 0

struct BallManager
{
	b2CircleShape* BallShape;
	b2BodyDef* BallDef;
	b2FixtureDef* BallFix;

	inline b2Vec2 ComputeVector(float TargetX, float TargetY)
	{
		return b2Vec2(TargetX - BALLX, TargetY - BALLY);
	}

	void BallInit()
	{
		BallShape = new b2CircleShape();
		BallShape->m_p.Set(0.0f, 0.0f);
		BallShape->m_radius = 0.4f;
		BallDef = new b2BodyDef;
		BallDef->type = b2_dynamicBody;
		BallDef->position.Set(BALLX, BALLY);
		BallFix = new b2FixtureDef;
		BallFix->restitution = 1.1f;
		BallFix->friction = 0.15f;
		BallFix->shape = BallShape;

	}

	void AddBall(float TargetX, float TargetY)
	{
		Object* NewBall = new Object();
		NewBall->CreateBody(BallDef);
		NewBall->CreateFixture(BallFix);
		NewBall->SetImageSource("Ball.png");
		NewBall->Body->ApplyLinearImpulse(ComputeVector(TargetX, TargetY), NewBall->Body->GetPosition(), true);
		RushEngineInfo.ObjectsDatabase->PushChanges();
	}

	BallManager()
	{
		BallInit();
	}
};