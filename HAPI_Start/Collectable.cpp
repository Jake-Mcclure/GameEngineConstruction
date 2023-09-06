#include "Collectable.h"

Collectable::Collectable(const std::string& fileName, Vector2 newpos,Type type) : Entity(fileName, newpos, Friendly, 1)
{
	m_type = type;
}

void Collectable::Update()
{
}

void Collectable::Render(BYTE* screen)
{
	if (m_isAlive)
	{
		if (m_screenPos.y > -32 || m_screenPos.y < GLOBALS::SCREENHEIGHT ||
			m_screenPos.x > -32 || m_screenPos.x < GLOBALS::SCREENWIDTH)
		{
			m_texture.Render(screen, m_screenPos.x, m_screenPos.y);
		}
	}
}
