#include "EnemySpawner.h"

std::vector<Entity*> EnemySpawner::GenerateEnemy(Vector2 sizeofarea, int amount)
{
	for (int i = 0; i < amount; i++)
	{
		sizeofarea.x  = sizeofarea.x - 50;
		sizeofarea.y = sizeofarea.y- 50;
		int x{ 1 }, y{ 1 };
		x += sizeofarea.x;
		y += sizeofarea.y;
		Enemy* enemy = new Enemy("Data//enemy.png", { rand()%x + 1, rand() % y+1 });
		enemies.push_back(enemy);
	}
	return enemies;
}
