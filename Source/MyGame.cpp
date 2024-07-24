#include "MyGame.h"
#include "Engine.h"
#include "Scene.h"
#include "Player.h"
#include "GameData.h"
#include "Enemy.h"
#include "Font.h"
#include "Text.h"
#include "Pickup.h"

bool MyGame::Initialize()
{
    m_scene = new Scene(this);

	g_engine.GetAudio().Update();

	m_font = new Font();
	m_font->Load("Begok.ttf", 20);
	m_largeFont = new Font();
	m_largeFont->Load("Begok.ttf", 40);
	
	m_textScore = new Text(m_font);
	m_textLives = new Text(m_font);

	m_textTitle = new Text(m_largeFont);
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
		m_lives = 3;
		g_engine.GetAudio().PlaySound("theme.wav");
		m_state = eState::StartLevel;
		break;
	case MyGame::eState::StartLevel:
		m_scene->RemoveAll();
	{
		Transform transform{ Vector2{400,300}, 0, 3 };
		Model* model = new Model{ GameData::ShipPoints, Color{1,0,0} };
		auto player = std::make_unique<Player>(250.0f, transform, model);
		player->SetDamping(1.5f);
		player->SetTag("Player");
		m_scene->AddActor(std::move(player));
	}
	m_spawnTime = 3;
	m_spawnTimer = m_spawnTime;
	m_state = eState::Game;
		break;
	case MyGame::eState::Game:
		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0) {
			m_spawnTime -= 0.2f;
			m_spawnTime = Math::Max(0.2f, m_spawnTime);
			m_spawnTimer = m_spawnTime;

			auto* enemyModel = new Model{ GameData::EnemyPoints, Color{1,0,1} };
			auto enemy = std::make_unique<Enemy>(400.0f, Transform{ { random(g_engine.GetRenderer().GetWidth()),random(g_engine.GetRenderer().GetHeight())}, 0, 2 }, enemyModel);
			enemy->SetTag("Enemy");
			m_scene->AddActor(std::move(enemy));
		}
		m_pickupTimer -= dt;
		if (m_pickupTimer <= 0) {
			m_pickupTimer = 10;

			auto* pickupModel = new Model{ GameData::PickupPoints, Color{1,1,1} };
			auto pickup = std::make_unique<Pickup>(Transform{ { random(g_engine.GetRenderer().GetWidth()),random(g_engine.GetRenderer().GetHeight())}, 0, 2 }, pickupModel);
			pickup->SetTag("Pickup");
			m_scene->AddActor(std::move(pickup));
		}
		break;
	case MyGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_state = eState::StartLevel;
		}
		break;
	case MyGame::eState::GameOver:
		if (m_stateTimer <= 0) {
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}
	m_scene->Update(dt);
}

void MyGame::Draw(Renderer& renderer)
{
	switch (m_state){
		case MyGame::eState::Title:
			m_textTitle->Create(renderer, "warpline", Color{ 1,0,0,1 });
			m_textTitle->Draw(renderer, 400, 300);

			break;
		case MyGame::eState::GameOver:
			m_textTitle->Create(renderer, "game over", Color{ 1,0,0,1 });
			m_textTitle->Draw(renderer, 400, 300);
			break;
		default:
			break;
	}

	std::string text = "score: " + std::to_string(m_score);
	m_textScore->Create(renderer, text, { 0,1,0,1 });
	m_textScore->Draw(renderer, 20, 20);

	std::string livestext = "lives: " + std::to_string(m_lives);
	m_textLives->Create(renderer, livestext, { 0,1,0,1 });
	m_textLives->Draw(renderer, 20, 40);



    m_scene->Draw(renderer);
}

void MyGame::OnPlayerDeath()
{
	m_lives--;
	m_state = (m_lives == 0)? eState::GameOver : eState::PlayerDead;
	m_stateTimer = 3;
}
