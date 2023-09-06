#include "Enemy.h"

void Enemy::Move(Vector2 playerpos)
{
	if (playerpos.x > m_position.x)
		m_position.x++;
	if (playerpos.x < m_position.x)
		m_position.x--;
	if (playerpos.y > m_position.y)
		m_position.y++;
	if (playerpos.y > m_position.y)
		m_position.y--;
}

void Enemy::Shoot()
{
//	std::cout << "i shoot" << std::endl;
}

void Enemy::Update()
{
	if (m_isAlive)
	{
		//Move();

		if (rand() % 100 <= 50)
		{
			Shoot();
		}
	}
}

void Enemy::Render(BYTE* screen)
{
	if (m_isAlive)
	{
		if (m_screenPos.x > -32 && m_screenPos.y > -32)
		{
			m_texture.Render(screen, m_screenPos.x, m_screenPos.y);
		}
		
	}
}

void Enemy::ChangeDirection(Vector2 newdirection)
{
	Direction = newdirection;
}

Enemy::Enemy(const std::string &filename, Vector2 pos) : Entity(filename,pos, Enemies, 20)
{
}
