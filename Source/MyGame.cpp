#include "MyGame.h"
#include "Engine.h"
#include "Scene.h"
#include "Player.h"
#include "GameData.h"
#include "Enemy.h"

bool MyGame::Initialize()
{
    m_scene = new Scene();
    return true;
}

void MyGame::Shutdown()
{
}

void MyGame::Update(float dt)
{
	switch (m_state)
	{
	case MyGame::eState::Title:
		if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
		}
		break;
	case MyGame::eState::StartGame:
		m_score = 0;
		m_state = eState::StartLevel;
		break;
	case MyGame::eState::StartLevel:
	{
		Transform transform{ Vector2{400,300}, 0, 3 };
		Model* model = new Model{ GameData::ShipPoints, Color{1,0,0} };
		Player* player = new Player(100, transform, model);
		player->SetDamping(1.5f);
		player->SetTag("Player");
		m_scene->AddActor(player);
	}
	m_spawnTime = 3;
	m_spawnTimer = m_spawnTime;
	m_state = eState::Game;
		break;
	case MyGame::eState::Game:
		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0) {
			m_spawnTime -= 0.2f;
			m_spawnTimer = m_spawnTime;

			auto* enemyModel = new Model{ GameData::EnemyPoints, Color{1,0,1} };
			auto* enemy = new Enemy(400, Transform{ { randomf(g_engine.GetRenderer().GetWidth()),randomf(g_engine.GetRenderer().GetHeight())}, 0, 2 }, enemyModel);
			enemy->SetTag("Enemy");
			m_scene->AddActor(enemy);
		}
		break;
	case MyGame::eState::PlayerDead:
		break;
	case MyGame::eState::GameOver:
		break;
	default:
		break;
	}
	m_scene->Update(dt);
}

void MyGame::Draw(Renderer& renderer)
{

    m_scene->Draw(renderer);
}
