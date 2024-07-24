#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include "Scene.h"
#include "GameData.h"
#include "Game.h"
#include "MyGame.h"
#include <iostream>

void Player::Update(float dt)
{

	Vector2 direction{ 0,0 };
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) direction.x = 1;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.x = -1;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_E)) {
		m_transform.position.x = random(0, 800);
		m_transform.position.y = random(0, 300);
	}

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) m_transform.rotation -= Math::DegToRad(100) * dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) m_transform.rotation += Math::DegToRad(100) * dt;

	Vector2 acceleration = direction.Rotate(m_transform.rotation) * m_speed;

	m_velocity += acceleration * dt;

		// randomize wrap position
	if (m_transform.position.x > (float)g_engine.GetRenderer().GetWidth() || m_transform.position.x < 0)
	{
		int r = random(3);
		switch (r)
		{
		case 0:
			m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
			break;
		case 1:
			m_transform.position.y = 0;
			m_transform.position.x = (float)g_engine.GetRenderer().GetWidth() / 2;
			break;
		case 2:
			m_transform.position.y = (float)g_engine.GetRenderer().GetHeight();
			m_transform.position.x = (float)g_engine.GetRenderer().GetWidth() / 2;
			break;

		}
	}
	if (m_transform.position.y > (float)g_engine.GetRenderer().GetHeight() || m_transform.position.y < 0)
	{
		int r = random(3);
		switch (r)
		{
		case 0:
			m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());
			break;
		case 1:
			m_transform.position.x = 0;
			m_transform.position.y = (float)g_engine.GetRenderer().GetHeight() / 2;
			break;
		case 2:
			m_transform.position.x = (float)g_engine.GetRenderer().GetWidth();
			m_transform.position.y = (float)g_engine.GetRenderer().GetHeight() / 2;
			break;

		}
	}

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	m_fireTimer -= dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0) {
		m_fireTimer = 0.2f;

		Vector2 direction = g_engine.GetInput().GetMousePosition() - m_transform.position;
		//float angle = direction.Angle();

		// actor
		/*Model* model = new Model{ GameData::BulletPoints, Color{ 1, 1, 0 } };
		Transform transform{ m_transform.position, m_transform.rotation, 1.0f };

		auto bullet = std::make_unique<Bullet>(400.0f, transform, model);
		bullet->SetLifespan(1);
		bullet->SetTag("Player");
		m_scene->AddActor(std::move(bullet));*/

		//if(powerup){copy above code, adjust positions}
		constexpr float angle = Math::DegToRad(20);
		float startAngle = -((m_bulletCount - 1) * angle * 0.5f);

		for (int i = 0; i < m_bulletCount; i++) {
			Model* model = new Model{ GameData::BulletPoints, Color{ 1, 1, 0 } };
			Transform transform{ m_transform.position, m_transform.rotation + startAngle + (angle * i), 1.0f };

			auto bullet = std::make_unique<Bullet>(400.0f, transform, model);
			bullet->SetLifespan(1);
			bullet->SetTag("Player");
			m_scene->AddActor(std::move(bullet));
		}
	}

	Actor::Update(dt);
	}

	void Player::OnCollision(Actor * actor) {
		if (actor->GetTag() == "Enemy") {
			m_destroyed = true;
			dynamic_cast<MyGame*>(m_scene->GetGame())->OnPlayerDeath();
		}
	}

