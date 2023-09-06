#pragma once
#include "Entity.h"
class Explosion : public Entity
{
protected:

public:
	void Render(BYTE* screen) override;
	void Update() override;
};

