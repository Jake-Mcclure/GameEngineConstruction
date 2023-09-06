#pragma once
#include "Graphics.h"
#include "Texture.h"
#include "Vector2.h"

enum Type
{
	Grenade = 0,
	Health = 1
};

enum Sides
{
	Neutral = 0,
	Friendly = 1,
	Enemies = 2
};

class Entity 
{

private:
	

protected:
	Type m_type;
	Sides m_side;
	Texture m_texture;
	int m_health;
	int m_Rotation{0};
	int m_speed{ 1 };
	int m_grenCount{ 0 };
	Vector2 m_position{ 0,0 };
	Vector2 m_screenPos{0,0};
	
	bool m_isAlive = true;
	bool m_collided = false;
	
public:
	void RotateImage(int theta);

	void SetPosition(Vector2 newpos);
	void SetSide(Sides side);
	void SetAlive(bool state);
	void SetScreenPos(Vector2 playerpos);
	void SetSpeed(int speed);
	void SetHealth(int health);

	void FindPath(Vector2 playerpos);
	void CheckCollision(Entity& other);

	int GetHealth();
	Sides GetSide();
	Vector2 GetPosition();
	bool GetAlive();
	//both render and update vary so each child class will ovveride this
	virtual void Update() = 0;
	virtual void Render(BYTE* screen);
	
	Entity(const std::string& fileName, Vector2 newpos,Sides side, int health);
};

