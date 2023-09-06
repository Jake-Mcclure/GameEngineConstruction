#pragma once
#include "Entity.h"
#include "Projectile.h"

class Enemy : public Entity
{
private:
	Vector2 Direction{ 2, 0};
	void Shoot();
	

public:
void Move(Vector2 playerpos);
	void Update() override;
	void Render(BYTE* screen) override;
	void ChangeDirection(Vector2 newdirection);

	Enemy(const std::string &filename, Vector2 pos);
};

