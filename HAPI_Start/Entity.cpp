#include "Entity.h"

void Entity::Render(BYTE* screen)
{
	if (m_isAlive)
	{
		m_texture.AlphaBlit(screen, m_position.x, m_position.y);
	}
}
//this calls the rotateimage funciton from the texture class
void Entity::RotateImage(int theta)
{
	int temp = m_Rotation;
	if (theta == m_Rotation)
	{
		return;
	}
	else if (theta > m_Rotation)
	{
		m_Rotation = theta;
		theta = theta - temp;
		
	}
	else
	{
		m_Rotation = theta;
		theta = (360 - temp) + theta;
		
	}
	//std::cout << theta << "  " << m_Direction << std::endl;
	m_texture.RotateImage(theta);
}

void Entity::SetPosition(Vector2 newpos)
{
	m_position = newpos;
}

void Entity::SetSide(Sides side)
{
	m_side = side;
}

void Entity::SetAlive(bool state)
{
	m_isAlive = state;
}

//this converts from world position to screen position
void Entity::SetScreenPos(Vector2 playerpos)
{
	if (playerpos.x > GLOBALS::SCREENWIDTH / 2)
	{
		m_screenPos.x = m_position.x - (playerpos.x - GLOBALS::SCREENWIDTH / 2);
	}
	else
	{
		m_screenPos.x = m_position.x;
	}

	if (playerpos.y > GLOBALS::SCREENHEIGHT / 2)
	{
		m_screenPos.y = m_position.y - (playerpos.y - GLOBALS::SCREENHEIGHT / 2);
		
	}
	else
	{
		m_screenPos.y = m_position.y;
	}

}

void Entity::SetSpeed(int speed)
{
	m_speed = speed;
}

void Entity::SetHealth(int health)
{
	m_health = health;
}

void Entity::FindPath(Vector2 playerpos)
{
	//if the entity is on the enemy side it will move towards the player
	//TODO needs reworking
	if (m_side == 2 )
	{
		//checks enemy is within agressive range
		if (m_position.x > playerpos.x - GLOBALS::ENEMYAGRO && m_position.x < playerpos.x + GLOBALS::ENEMYAGRO
			&& m_position.y > playerpos.y - GLOBALS::ENEMYAGRO && m_position.y < playerpos.y + GLOBALS::ENEMYAGRO)
		{
			if (playerpos.x > m_position.x)
				m_position.x++;
			if (playerpos.x < m_position.x)
				m_position.x--;
			if (playerpos.y > m_position.y)
				m_position.y++;
			if (playerpos.y < m_position.y)
				m_position.y--;
		}

		
		//std::cout << "enemy pos = " << m_position.x << " " << m_position.y << std::endl;
	}
	
}

void Entity::CheckCollision(Entity& other)
{
	//checks if current is to the right of other
	if ((m_position.x-5 >  5+other.m_position.x + other.m_texture.GetWidth() ||
		//checks if current is to the left of other
		m_position.x + m_texture.GetWidth() + 5 < other.m_position.x-5) ||
		//checks if current is above other
		(m_position.y + m_texture.GetHeight() +5 < other.m_position.y-5) ||
		//checks if current is below other
		m_position.y-5 > 5+other.m_position.y + other.m_texture.GetHeight())
	{

	}
	else
	{
		//if one is an enemy and one is friendly
		if (m_side != Neutral && other.m_side != Neutral && m_side != other.m_side)
		{
			//std::cout << "Opposite Collision" << std::endl;
			if (m_isAlive && other.m_isAlive)
			{
				int temp = m_health;
				m_health -= other.m_health;
				other.m_health -= temp;
				if (m_health <= 0)
				{
					m_isAlive = false;
				}
				if (other.m_health <= 0)
				{
					other.m_isAlive = false;
				}
				if (!HAPI.PlaySound("Data//gasp.wav"))
					std::cout << "couldnt load gasp sound" << std::endl;
			}
		}
		//if either the player bullet or player collides with the collectable
		//if player collides it will pick it up if bullet collides it will destroy it
		//be careful
		else if (m_side == other.m_side && m_side == Friendly)
		{
			std::cout << "collect" << std::endl;
			switch (other.m_type)
			{
			case Grenade:
				m_grenCount++;
				other.m_isAlive = false;
				break;
			case Health:
				if (!HAPI.PlaySound("Data//heal.wav"))
					std::cout << "couldnt load heal sound" << std::endl;
				m_health += 20;
				other.m_isAlive = false;
				break;
			default:
				break;
			}
		}
		
	}
}

int Entity::GetHealth()
{
	return m_health;
}

Sides Entity::GetSide()
{
	return m_side;
}

Vector2 Entity::GetPosition()
{
	return m_position;
	
}

bool Entity::GetAlive()
{
	return m_isAlive;
}

Entity::Entity(const std::string& fileName, Vector2 newpos,Sides side,int health):
	m_health(health),
	m_side(side),
	m_texture(fileName),
	m_position(newpos)
{
}
