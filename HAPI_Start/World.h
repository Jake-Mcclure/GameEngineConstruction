#pragma once
#include <HAPI_lib.h>
#include "Global_vars.h"
#include "Visulation.h" 
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "TileManager.h"
#include "EnemySpawner.h"
#include "ItemSpawner.h"

class World
{
private:
	const DWORD m_kTickTime = 1000 / 50;
	DWORD m_lastTimeUpdated = HAPI.GetTime();

	int m_width = GLOBALS::SCREENWIDTH;
	int m_height = GLOBALS::SCREENHEIGHT;
	int m_wave{ 0 };
	int m_aliveEnemies{0};

	Visulation* Game = new Visulation();
	const HAPI_TKeyboardData& KeyData = HAPI.GetKeyboardData();

	EnemySpawner m_enemySpawner;
	ItemSpawner m_itemSpawner;

	Player m_player = Player("Data//Player.png", { GLOBALS::SCREENWIDTH/2, GLOBALS::SCREENHEIGHT/2 });;
	BYTE* m_screen;
	std::vector<Entity*> entities;

	void CheckEnemyCollisions(std::vector<Entity*> entity);
	void SpawnWave();
	
public:
	void Update();
	void Initialise();
	void Render();
	
	

};
