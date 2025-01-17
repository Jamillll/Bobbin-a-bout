#pragma once
#include "Entity.h"
#include "..\Types.h"

#include <box2d/box2d.h>

class Player : public Entity, public b2ContactListener
{
private:
	const float m_MaxAcceleration = 10;
	float m_Acceleration = 2;

	float m_JumpPower = 20;
	const int m_MaxJumps = 2;
	int m_JumpCount = 0;
	bool m_JumpPrimed = true;

	unsigned int m_LivesCount = 3;

public:
	Vec4 m_Colour = { 1, 0, 0, 0.5f };
	Vec2 m_Size = { 1.5, 2 };
	b2Body* m_Body = nullptr;
	Texture* m_Texture = nullptr;

	bool m_IsDead = false;

	Player(b2World& world);

	void Update(GLFWwindow* window);
	void Draw(Renderer& renderer);

	unsigned int GetLivesCount();

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	~Player();
};
