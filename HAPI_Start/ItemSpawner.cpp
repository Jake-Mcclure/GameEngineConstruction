#include "ItemSpawner.h"

std::vector<Entity*> ItemSpawner::GenerateItems(Vector2 sizeofarea, int amount)
{
	for (int i = 0; i < amount; i++)
	{
		sizeofarea.x = sizeofarea.x - 50;
		sizeofarea.y = sizeofarea.y - 50;
		int x{ 10 }, y{ 10 };
		x += sizeofarea.x;
		y += sizeofarea.y;
		
		Collectable* item = new Collectable("Data//Grenade.png", { rand() % x + 10, rand() % y + 10 }, Grenade);
		Collectable* item2 = new Collectable("Data//Health.png", { rand() % x + 5, rand() % y + 15 },Health);
		items.push_back(item);
		items.push_back(item2);
	}
	return items;
}
