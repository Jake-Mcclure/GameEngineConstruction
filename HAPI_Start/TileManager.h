#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Vector2.h"

class TileManager
{
public:
	void LoadMap(const std::string& filename);
	std::vector<std::vector<int>> GetMap();
	Vector2 GetSize();
	
private:
	std::vector<std::vector<int>> m_map;
	int m_width{ 0 };
	int m_height{0};
};

