#pragma once
#include "Entity.h"



class Collectable : public Entity
{
protected:
	

public:
	Collectable(const std::string& fileName, Vector2 newpos,Type type);
	void Update() override;
	void Render(BYTE* screen) override;
};

