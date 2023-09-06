#include "World.h"

void World::Update()
{
	

		Game->clearToColour(HAPI_TColour::BLACK);
		//this is the start of the game loop
		m_lastTimeUpdated = HAPI.GetTime() - m_lastTimeUpdated;
		if (m_lastTimeUpdated >= m_kTickTime)
		{
			//checking for user inputs
			Vector2 Direction{ 0,0 };
			if (KeyData.scanCode['W'])
			{
				Direction.y -= 1;
				m_player.RotateImage(0);
				
			}
			if (KeyData.scanCode['S'])
			{
				Direction.y += 1;
				m_player.RotateImage(180);
			
			}
			if (KeyData.scanCode['A'])
			{
				Direction.x -= 1;
				m_player.RotateImage(90);
				
			}
			if (KeyData.scanCode['D'])
			{
				Direction.x += 1;
				m_player.RotateImage(270);
			}
			if (KeyData.scanCode['F'])
			{
				m_player.Shoot();
				//std::cout << "shoot" << std::endl;

			}
			m_player.SetDirection(Direction);
			CheckEnemyCollisions(entities);

			//Update
			m_player.Update();
			m_aliveEnemies = 0;
			for (auto& Enemy : entities)
			{
				//checking for how many enemys are still alive and then updating and generating the screen position of each entity
				if (Enemy->GetAlive() && Enemy->GetSide() == Enemies)
					m_aliveEnemies++;
				Enemy->FindPath(m_player.GetPosition());
				Enemy->Update();
				Enemy->SetScreenPos(m_player.GetPosition());
			}
			//if all enemies are dead it will spawn a new wave
			if (m_aliveEnemies == 0)
				SpawnWave();
			//resets gameloop timer
			m_lastTimeUpdated = HAPI.GetTime();
		}
	
}

void World::Initialise()
{
	//initalizing the visuals
	if (!Game->Initialise(m_width, m_height))
		return;

	
	m_screen = HAPI.GetScreenPointer();
			
	HAPI.SetShowFPS(true);

	SpawnWave();
	//m_player = Player("Data//Player_Up.tga", { m_width / 2, m_height / 2 });
}


void World::Render()
{
	//this renders the backround and screen
	Game->DrawBackground(m_player.GetPosition());
	m_player.Render(m_screen);
	//looping through and rendering the entities
	for (auto& Enemy : entities)
	{
		Enemy->Render(m_screen);
	}

	//this renders the text which appears a tthe top of the screen for health, score, wave and enemies alive
	HAPI.RenderText((GLOBALS::SCREENWIDTH / 2) , 0, HAPI_TColour::WHITE,"Health = " + std::to_string(m_player.GetHealth()), 25);
	HAPI.RenderText((GLOBALS::SCREENWIDTH / 2) - 250, 40, HAPI_TColour::WHITE,"Wave = " + std::to_string(m_wave) + " Enemys alive = " + std::to_string(m_aliveEnemies), 25);
	HAPI.RenderText((GLOBALS::SCREENWIDTH / 2) - 250, 0, HAPI_TColour::WHITE,"Score = " + std::to_string(m_player.GetScore()), 25);

}



void World::CheckEnemyCollisions(std::vector<Entity*> entity)
{
	//loops through all entities
	for (auto& Enemy : entities)
	{
		
		if (Enemy->GetAlive())
		{
			//player checks if it has collided with the alive entity
			m_player.CheckCollision(*Enemy);
			for (auto& projectile : m_player.GetProjectiles())
			{
				//only checks to see if the alive projectiles have collided with an enemy
				if (projectile->GetAlive())
				{
					projectile->CheckCollision(*Enemy);
								
				}
				
			}
			//if an enemy dies in this loop 20 score is added 
			if (!Enemy->GetAlive())
				m_player.AddScore(20);
		}
		
	}
}

void World::SpawnWave()
{
	//this calls the enemy and item spawners and adds both to the entity vector
	m_wave++;
	entities.clear();
	entities = m_enemySpawner.GenerateEnemy(Game->GetMapSize(), m_wave * 10 + 5);
	std::vector<Entity*> items = m_itemSpawner.GenerateItems(Game->GetMapSize(), m_wave * 2);
	for (auto& item : items)
	{
		entities.push_back(item);
	}
	std::cout << entities.size() << std::endl;
	
}
