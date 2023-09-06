#pragma once
#include <iostream>
#include <HAPI_lib.h>
#include <unordered_map>
#include "Texture.h"
#include "TileManager.h"
#include "Vector2.h"

using namespace HAPISPACE;
class Visulation
{
public:
	//clears to a solid colour
	void clearToColour(HAPI_TColour col);
	//draws the texture 
	void drawTexture(const std::string& name, int posx,int posy,bool fast);
	bool Initialise(int screenwidth, int screenheight);
	bool LoadTexture(const std::string& filename, const std::string& name);
	void DrawBackground(Vector2 playerpos);
	Vector2 GetMapSize();

protected:
	TileManager m_background;
	std::unordered_map<std::string, Texture*> m_texturemap;
	int m_screenWidth, m_screenHeight;
	BYTE* m_screen{nullptr};
	
};

