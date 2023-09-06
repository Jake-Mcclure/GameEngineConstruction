#include "TileManager.h"

void TileManager::LoadMap(const std::string& filename)
{

	std::string line, value;
	std::ifstream map;

	map.open(filename);
	if (!map.fail())
	{//if the file opens it loops through and adds each value inbetween the commas to the map
		//for each row another vector is added to the map vector
		while (std::getline(map, line))
		{
			m_width++;
			std::vector<int> row;
			std::stringstream s(line);
			while (std::getline(s,value,','))
			{
				row.push_back(std::stoi(value));
				m_height++;
			}
			m_map.push_back(row);
			m_height /= m_width;
			
		}
	
	}
	else
	{
		std::cout << "Map can not be loaded" << std::endl;
	}
}

std::vector<std::vector<int>> TileManager::GetMap()
{
	return m_map;
}

Vector2 TileManager::GetSize()
{
	return Vector2(m_width,m_height);
}
