#include "Player.h"
#include "Projectile.h"



int Player::GetScore()
{
	return m_score;
}

void Player::AddScore(int score)
{
	m_score += score;
}

std::vector<Projectile*> Player::GetProjectiles()
{
	return m_bullets;
}
//this finds the first available projectile and shoots it and also plays a sound 
void Player::Shoot()
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets[i]->GetAlive() == false)
		{
			if (m_shootTimer >= 15)
			{
				if (!HAPI.PlaySound("Data//shoot.wav"))
					std::cout << "couldnt load gunshot sound" << std::endl;
				m_bullets[i]->Shoot(m_position, m_Rotation);
				m_shootTimer = 0;
			}
			else
			{
				std::cout << "shoot timer = " << m_shootTimer << std::endl;
			}
		}
	}
	
}

void Player::ThrowGrenade()
{
	if (m_grenCount > 0)
	{

		m_grenCount--;
	}
}

void Player::Move()
{
	//this just alters the players position according to the current direction and speed

	if (m_currentDirection.y == -1)
	{
		if (m_position.y > 0)
			m_position.y += m_currentDirection.y * m_speed;
	}
	if (m_currentDirection.y == 1)
	{
		m_position.y += m_currentDirection.y * m_speed;
	}
	if (m_currentDirection.x == -1)
	{
		if (m_position.x > 0)
			m_position.x += m_currentDirection.x * m_speed;
	}
	if (m_currentDirection.x == 1)
	{
		m_position.x += m_currentDirection.x * m_speed;
	}
	
	//m_position += m_currentDirection;
}


void Player::Render(BYTE* screen)
{
	if (m_isAlive)
	{//if the players worl position is past half the width or height of the window then it will be stuck to the middle of the screen
		//the world pos is still changed just not the screen pos
		//std::cout << "player pos = " << m_position.x << " " << m_position.y << std::endl;
		int tempx = m_position.x;
		int tempy = m_position.y;
		if (m_position.x > GLOBALS::SCREENWIDTH / 2)
			tempx = GLOBALS::SCREENWIDTH / 2;
		if (m_position.y > GLOBALS::SCREENHEIGHT / 2)
			tempy = GLOBALS::SCREENHEIGHT / 2;
		m_texture.Render(screen, tempx, tempy);

		for (int i = 0; i < m_bullets.size(); i++)
		{
			if (m_bullets[i]->GetAlive() && m_bullets[i]->GetAlive())
			{
				m_bullets[i]->SetScreenPos(m_position);
				m_bullets[i]->Render(screen);
				
			}
		}
	}
}

void Player::Update()
{
	//this loops throguht the projectiles and renders them
	if (m_isAlive)
	{
		Move();
		for (int i = 0; i < m_bullets.size(); i++)
		{
			m_bullets[i]->Update();
			m_bullets[i]->SetScreenPos(m_position);
		}
		m_shootTimer += 1;
	}
}

void Player::SetDirection(Vector2 direction)
{
	m_currentDirection = direction;
}

Player::Player(const std::string& fileName, Vector2 newpos) : Entity(fileName, newpos, Friendly,500)
{
	//this adds 25  projectiles to the players vector upon creation
	for (int i = 0; i < 25; i++)
	{
		Projectile* proj = new Projectile("Data//Projectile.png", m_position);
		proj->SetAlive(false);
		m_bullets.push_back(proj);
		m_bullets[i]->SetSide(Friendly);
	}
	m_speed = 2;
}
