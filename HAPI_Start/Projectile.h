#pragma once
#include "Entity.h"

class Projectile : public Entity
{
private:
	
	
	Vector2 m_Direction{0,-1};

public:

	void Shoot(Vector2 pos,int rotation);
	void Move();
	void Update() override;
	void Render(BYTE* screen) override;
	
	
	
	Projectile(const std::string& fileName, Vector2 newpos);
};

