#pragma once
#include <HAPI_lib.h>
#include <array>
#include "Entity.h"
#include "Projectile.h"

using namespace HAPISPACE;

class Player :public Entity 
{

private:
	std::vector<Projectile* > m_bullets;
	int m_shootTimer = 0;
	Vector2 m_currentDirection{0,0};
	int m_score{ 0 };
	

public:
	
	int GetScore();
	void AddScore(int score);

	std::vector<Projectile*> GetProjectiles();
	void Shoot();
	void ThrowGrenade();

	void Move();

	void Render(BYTE* screen) override;
	void Update() override;

	void SetDirection(Vector2 direction);
	explicit Player(const std::string& fileName, Vector2 newpos);

};

