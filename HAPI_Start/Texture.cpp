#define _USE_MATH_DEFINES
#include "Texture.h"
#include "Rectangle.h"
#include <cmath>

Texture::Texture(const std::string& _fileName) :
	m_textureData(nullptr),
	m_width(0),
	m_height(0)
{
	//if the filename is invalid then an error will be displayed to the user
	if (!HAPI.LoadTexture(_fileName, &m_textureData, m_width, m_height)) {
		std::cout << "FILE : " << _fileName << " NOT FOUND" << std::endl;
		const std::string message{ "The file: " + _fileName + " was not located. Check the file path or the filename." };
		HAPI.UserMessage(message, "File not found");
		m_width = 64;
		m_height = 64;
	}
	

}

//this is a very fast blit with no checks, no clipping and does not take alpha into account
void Texture::Blit(BYTE* screen, int posx, int posy)
{	
		for (int newY = 0; newY < m_height; newY++)
		{
			int offset = (GLOBALS::SCREENWIDTH * (posy + newY) + posx) * 4;
			int textureOffset = m_height * newY * 4;

			memcpy(screen + offset, m_textureData + textureOffset, m_width * 4);

		}	
}

//thi takes alpha into account but is a little slower than the Blit function
void Texture::AlphaBlit(BYTE* screen, int posx, int posy)
{
	BYTE* screenstart = screen + (posx + posy * GLOBALS::SCREENWIDTH) * 4;

	BYTE* texturestart{ m_textureData };

	int endoflinedestincrememnt{ GLOBALS::SCREENWIDTH * 4 - m_width * 4 };

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			BYTE a = texturestart[3];

			if (a > 0) 
			{
				//if it is completely opaque
				if (a == 255)
				{
					memcpy(screenstart, texturestart, 4);
				}
				else
				{
					float alpha = a / 255.0f;

					screenstart[0] = alpha * texturestart[0] + screenstart[0] * (1.0f - alpha);
					screenstart[1] = alpha * texturestart[1] + screenstart[1] * (1.0f - alpha); 
					screenstart[2] = alpha * texturestart[2] + screenstart[2] * (1.0f - alpha);
				}

			}
			screenstart += 4;
			texturestart += 4;
		}
		screenstart += endoflinedestincrememnt;
	}

}
//this is slower than both other blits however will not crash when it goes off the bottom tof the screen
void Texture::ClippingBlit(BYTE* screen, int posx, int posy)
{
	//two rectangles are created one for the screen and one for the texture
	Rectangle screenRect(posx-GLOBALS::SCREENWIDTH,GLOBALS::SCREENWIDTH,posy-GLOBALS::SCREENHEIGHT,GLOBALS::SCREENHEIGHT);
	Rectangle textureRect(0, m_width, 0, m_height);
	//the texctures rectangle is moved into the desired positionand checked if it is on screen if not then it will exit the funciton
	textureRect.Translate(posx, posy);
	if (!textureRect.isOnScreen(screenRect))
	{
		//std::cout << "Not on screen" << std::endl;
		return;
	}
	//the texture rectangle is altered so only the onscreen part will be rendered then moved back to its origional position 
	textureRect.ClipTo(screenRect);
	textureRect.Translate(-posx, -posy);

	if (posx < 0)
	{
		posx = 0;
	}
	if (posy < 0)
	{
		posy = 0;
	}
	//this section is the alpha blit however the rectangle is used for size rather than the full texture size
	BYTE* screenstart = screen + (posx + posy * GLOBALS::SCREENWIDTH) * 4;

	BYTE* texturestart = m_textureData + (textureRect.m_left + textureRect.m_top * m_width) * 4 ;

	int endoflinedestincrememnt{ (GLOBALS::SCREENWIDTH - textureRect.width()) * 4 };
	int endoflinerectincrement{(m_width - textureRect.width()) * 4};

	for (int y = 0; y < textureRect.height(); y++)
	{
		for (int x = 0; x < textureRect.width(); x++)
		{
			BYTE a = texturestart[3];

			if (a > 0)
			{
				if (a == 255)
				{
					memcpy(screenstart, texturestart, 4);
				}
				else
				{
					float alpha = a / 255.0f;

					screenstart[0] = alpha * texturestart[0] + screenstart[0] * (1.0f - alpha);
					screenstart[1] = alpha * texturestart[1] + screenstart[1] * (1.0f - alpha);
					screenstart[2] = alpha * texturestart[2] + screenstart[2] * (1.0f - alpha);
				}
			}
			screenstart += 4;
			texturestart += 4;
		}
		screenstart += endoflinedestincrememnt;
		texturestart += endoflinerectincrement;
	}
}
//theta is the angle in degrees as of which the image needs to face
void Texture::RotateImage(int theta)
{

	//this is blank but is the same size as the texturedata so thast it can be written to freely
	BYTE* destinationdata = new BYTE[m_width * m_height * 4];
	
	//converting from degrees to radians
	double radians = (theta * M_PI) / 180;

	//the center
	int x0 = (m_width - 1) / 2;
	int y0 = (m_height - 1) / 2;

	
	int cosTheta = cos(radians);
	int sinTheta = sin(radians);

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			long double a = x - x0;
			long double b = y - y0;

			int xx = (+a * cosTheta - b * sinTheta + x0);
			int yy = (+a * sinTheta + b * cosTheta + y0);

			if (xx >=0 && xx < m_width && yy >= 0 && yy < m_height)
			{
				destinationdata[(y * m_width + x) * 4 + 0] = m_textureData[(yy * m_width + xx) * 4 + 0];
				destinationdata[(y * m_width + x) * 4 + 1] = m_textureData[(yy * m_width + xx) * 4 + 1];
				destinationdata[(y * m_width + x) * 4 + 2] = m_textureData[(yy * m_width + xx) * 4 + 2];
				destinationdata[(y * m_width + x) * 4 + 3] = m_textureData[(yy * m_width + xx) * 4 + 3];
			}
		}
	}
	
	delete[] m_textureData;
	m_textureData = destinationdata;
}

//void Texture::AlphaTexture()
//{
//	for (int y = 0; y < m_height; y++)
//	{
//		for (int x = 0; x < m_width; x++)
//		{	
//			if (m_textureData[(y * m_width + x) * 4 + 0] >= 245 && m_textureData[(y * m_width + x) * 4 + 1] >= 245 && m_textureData[(y * m_width + x) * 4 + 2] >= 245)
//			{
//				m_textureData[(y * m_width + x) * 4 + 3] = 0;
//			}
//		}
//		
//	}
//}

//this attempts to create a texture and if it cant it will return false
bool Texture::Create(const std::string& filename)
{
	if (!HAPI.LoadTexture(filename, &m_textureData, m_width, m_height))
		return false;
	//AlphaTexture();
	return true;
}

int Texture::GetHeight()
{
	return m_height;
}

int Texture::GetWidth()
{
	return m_width;
}
//this just renders a texture using the clipping funciton
void Texture::Render(HAPISPACE::BYTE* screen,int posx, int posy){
	if (m_textureData) {
		ClippingBlit(screen, posx, posy);
	}
	else {//this part if the texturedata can not be found will display a horrid pink colour instead
		HAPISPACE::HAPI_TColour* horridPink = &HAPISPACE::HAPI_TColour::HORRID_PINK;
		for (int x = (posx); x < (posx + m_width); x++) {
			for (int y = posy; y < (posy + m_height); y++) {
				const int offset = (x + y * GLOBALS::SCREENWIDTH) * 4;
				memcpy(screen + offset, horridPink, 4);
			}
		}
	}
}

