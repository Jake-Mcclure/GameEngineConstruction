#include "Visulation.h"
//clear sthe screen to one colour
void Visulation::clearToColour(HAPI_TColour col)
{
	for (int i = 0; i <m_screenWidth * m_screenHeight; i++)
	{
		memcpy(m_screen + i * 4, &col, 4);
	}
}
//draws a texture either quickly or slowly depending on the last parameter
void Visulation::drawTexture(const std::string& name, int posx, int posy,bool fast)
{
	if (fast)
		m_texturemap[name]->Blit(m_screen,posx,posy);
	else 
		m_texturemap[name]->ClippingBlit(m_screen, posx, posy);
}

bool Visulation::Initialise(int screenwidth, int screenheight)
{
	//initalises and loads the tile sused for the background
	//needs to be changed to an enum
	if (!HAPI.Initialise(screenwidth, screenheight, "Zombles Game"))
	{
		return false;
	}
	m_screenHeight = screenheight;
	m_screenWidth = screenwidth;
	m_screen = HAPI.GetScreenPointer();
	
	m_background.LoadMap("Data//Map1.csv");

	Texture* newTexture = new Texture("Data//Tiles//tile_01.png");
	m_texturemap["grass"] = newTexture;

	newTexture = new Texture("Data//Tiles//tile_02.png");
	m_texturemap["water"] = newTexture;
}

bool Visulation::LoadTexture(const std::string& filename, const std::string& name)
{
	//if the texture loads it will be added to the map with its name as refrence
	Texture* newTexture = new Texture(filename);

	if (!newTexture->Create(filename))
	{
		delete newTexture;
		return false;
	}
	m_texturemap[name] = newTexture;
	return true;
}

void Visulation::DrawBackground(Vector2 playerpos)
{
	
		int topx =0, topy = 0, x = 0 ,y = 0 ,currentx = 0,currenty =0;
		int remainderx = 0;
		int remaindery = 0;
		//if the player is to the right/bottom of the middle of the screen then the top left of the
		//onscreen is changed aswell as the remainder which allows for the scrolling background
		if (playerpos.x > GLOBALS::SCREENWIDTH/2)
		{
			topx = (playerpos.x - (GLOBALS::SCREENWIDTH/2)) / 32;
			 remainderx = playerpos.x - GLOBALS::SCREENWIDTH / 2;
		}
		if (playerpos.y > GLOBALS::SCREENHEIGHT/2)
		{
			topy = (playerpos.y - (GLOBALS::SCREENHEIGHT/2)) / 32;
			 remaindery = playerpos.y - GLOBALS::SCREENHEIGHT / 2;
		}
		
	
		//for each row and column of the map
		for (auto& row : m_background.GetMap())
		{
			//if (y >= topy - 2 && y <= topy + (GLOBALS::SCREENHEIGHT/32) + 1 )
			//{
				for (auto& value : row)
				{
					//if (x >= topx - 2 && x <= topx + (GLOBALS::SCREENWIDTH / 32) + 1)
					//{
					//draws the texture according to the number from the csv file
						switch (value)
						{
						case 0:
							m_texturemap["grass"]->ClippingBlit(m_screen, currentx * 32 - remainderx, currenty * 32 - remaindery);
							break;

						case 1:
							m_texturemap["water"]->ClippingBlit(m_screen, currentx * 32 - remainderx, currenty * 32 - remaindery);
							break;

						default:
							std::cout << "Default" << std::endl;
							break;
						}
						currentx++;
					//}
					x++;
				}
				currenty++;
				currentx = 0;
			//}
			y++;
			x = 0;
		}
	
}

Vector2 Visulation::GetMapSize()
{
	return m_background.GetSize();
}


