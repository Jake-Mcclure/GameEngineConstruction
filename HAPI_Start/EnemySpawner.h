#pragma once
#include "enemy.h"
#include "Entity.h"
class EnemySpawner
{
private:
	std::vector<Entity*> enemies;
public:
	std::vector<Entity*> GenerateEnemy(Vector2 sizeofarea,int amount);
};

