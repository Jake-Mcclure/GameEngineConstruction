#pragma once
#include "Entity.h"
#include "Collectable.h"
class ItemSpawner
{
private:
	std::vector<Entity*> items;
public:
	std::vector<Entity*> GenerateItems(Vector2 sizeofarea, int amount);
};

