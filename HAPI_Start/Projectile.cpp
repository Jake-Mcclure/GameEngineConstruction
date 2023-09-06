#include "Projectile.h"

void Projectile::Shoot(Vector2 pos, int rotation)
{
	//this gets the direction the player is facing and rotates the projectile accordingly
	//it also sets the spawn position and the direction 
	SetHealth(20);
	m_isAlive = true;
	switch (rotation)
	{
	case  0:
		m_Direction = { 0,-m_speed };
		pos.x += 25;
		pos.y -= 25;
		break;

	case 90:
		m_Direction = { -m_speed,0 };
		pos.x -= 50;
		pos.y += 25;
		RotateImage(rotation);
		break;

	case 180:
		m_Direction = { 0,m_speed };
		pos.x += 25;
		pos.y += 50;
		RotateImage(rotation);
		break;

	case 270:
		m_Direction = { m_speed,0 };
		pos.x += 50;
		pos.y += 25;
		RotateImage(rotation);
		break;
	default:
		break;
	}
	m_position = pos;
}

void Projectile::Move()
{
	/*if (isActive == true && GetAlive())
	{
		if (m_position.y <= 0)
		{
			isActive = false;
		}
		else if(m_position.x <= 0)
		{
			isActive = false;
		}
		else
		{
			m_position.y += m_Direction.y;
			m_position.x += m_Direction.x;
		}
	}*/
}



void Projectile::Update()
{
	//if it is off screen then it is destroyed
	if (m_isAlive == true)
	{
		if (m_position.y <= 0 || m_screenPos.y < -32 || m_screenPos.y > GLOBALS::SCREENHEIGHT ||
			m_position.x <= 0 || m_screenPos.x < -32 || m_screenPos.x > GLOBALS::SCREENWIDTH)
		{
			m_isAlive = false;
		}
		
		else
		{
			
			m_position.y += m_Direction.y;
			m_position.x += m_Direction.x;
		}
	}
}

void Projectile::Render(BYTE* screen)
{
	if (m_isAlive)
	{
		m_texture.Render(screen, m_screenPos.x, m_screenPos.y);

	}
}

Projectile::Projectile(const std::string& fileName, Vector2 newpos) : Entity(fileName,newpos,Neutral, 20)
{
	m_speed = 3;
}
