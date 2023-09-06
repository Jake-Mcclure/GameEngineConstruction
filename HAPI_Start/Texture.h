#pragma once
#include <HAPI_lib.h>
#include "Global_vars.h"

using namespace HAPISPACE;
class Texture
{
public:
	Texture(const std::string& fileName);
	void Render(BYTE* screen,int posx, int posy);
	//fast simple blit
	void Blit(BYTE* screen, int posx, int posy);
	//takes alpha channel into account
	void AlphaBlit(BYTE* screen, int posx, int posy);
	//slower but only blits what is on screen
	void ClippingBlit(BYTE* screen, int posx, int posy);
	void RotateImage(int theta);
	//void AlphaTexture();
	bool Create(const std::string& filename);

	int GetHeight();
	int GetWidth();

private:
	BYTE* m_textureData;
	int m_width;
	int m_height;
	
	
};

