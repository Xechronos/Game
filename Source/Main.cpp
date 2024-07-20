#include "Engine.h"
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"
#include "GameData.h"
#include "MyGame.h"

#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
	g_engine.Initialize();

	MyGame* game = new MyGame(&g_engine);
	game->Initialize();

	while (!g_engine.isQuit())
	{
		g_engine.Update();
		game->Update(g_engine.GetTime().GetDeltaTime());
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		game->Draw(g_engine.GetRenderer());

		g_engine.GetRenderer().EndFrame();
	}
	return 0;
}


/*

	// create audio system


	

	std::vector<Particle> particles;
	float offset = 0;
	/*for (int i = 0; i < 10000; i++) {
		particles.push_back(Particle{ {rand() % 800, rand() % 800} , { randomf(100,300), 0.0f } } );

	}



	



	Model* model = new Model{ GameData::ShipPoints, Color{1,0,0} };


	Scene* scene = new Scene();

		Transform transform{ Vector2{400,300}, 0, 3};
		Player* player = new Player(200, transform, model);
		player->SetDamping(1.5f);
		player->SetTag("Player");
		scene->AddActor(player);
	

		float spawnTimer = 2;

	Vector2 position{ 400, 300 };
	float rotation = 0;

	bool quit = false;
	while (!g_engine.isQuit())
	{
		g_engine.Update();

		g_engine.GetInput().Update();
		g_engine.GetAudio().Update();


		spawnTimer -= g_engine.GetTime().GetDeltaTime();
		if (spawnTimer <= 0) {
			Model* enemyModel = new Model{ GameData::ShipPoints, Color{1,0,1} };
			Enemy* enemy = new Enemy(400, Transform{ {g_engine.GetRenderer().GetWidth(),g_engine.GetRenderer().GetHeight()}, 0, 2 }, enemyModel);
			enemy->SetDamping(1.0f);
			enemy->SetTag("Enemy");
			scene->AddActor(enemy);
			//spawn enemy
		}

		scene->Update(g_engine.GetTime().GetDeltaTime());

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_Q)){
			g_engine.GetAudio().PlaySound("bass.wav");
		}

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_W)) {
			g_engine.GetAudio().PlaySound("snare.wav");
		}

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_E)) {
			g_engine.GetAudio().PlaySound("open-hat.wav");
		}

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_R) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_R)) {
			g_engine.GetAudio().PlaySound("close-hat.wav");
		}

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_T) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_T)) {
			g_engine.GetAudio().PlaySound("clap.wav");
		}
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Y) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_Y)) {
			g_engine.GetAudio().PlaySound("cowbell.wav");
		}

		

		Vector2 mousePosition = g_engine.GetInput().GetMousePosition();
		if (g_engine.GetInput().GetMouseButtonDown(0)) {
			particles.push_back(Particle{ mousePosition,
			{ randomOnUnitCircle() * randomf(50, 300)},
			{randomf(1, 5)},
			uint8_t{(uint8_t)randomf(0, 255)} ,
			uint8_t{(uint8_t)randomf(0, 255)} ,
				uint8_t{(uint8_t)randomf(0, 255) },
				uint8_t{ 0 }
				}
			);
		}


			for (Particle& particle : particles) {
				particle.Update(g_engine.GetTime().GetDeltaTime());
				if (particle.position.x > 800) {
					particle.position.x = 0;
				}
				if (particle.position.x < 0) {
					particle.position.x = 800;
				}
				if (particle.lifespan != 0) {
					particle.lifespan -= g_engine.GetTime().GetDeltaTime();
				}
			}


			if (g_engine.GetInput().GetMouseButtonDown(0) && !g_engine.GetInput().GetPrevMouseButtonDown(0)) {
				std::cout << "mouse pressed" << std::endl;
				points.push_back(mousePosition);
			}

			if (g_engine.GetInput().GetMouseButtonDown(0) && g_engine.GetInput().GetPrevMouseButtonDown(0)) {
				float distance = (points.back() - mousePosition).Length();
				if (distance > 5) {
					points.push_back(mousePosition);
				}
			}

			//	// clear screen
			g_engine.GetRenderer().SetColor(0, 0, 0, 0);
			g_engine.GetRenderer().BeginFrame();
			//	SDL_RenderClear(renderer);
			/*renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
			float radius = 30;
			offset += (90 * time.GetDeltaTime());
			for (float angle = 0; angle < 360; angle += 360 / 30) {
				float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.1f) * radius;
				float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.1f) * radius;

				renderer.DrawRect(400 + x, 300 + y, randomf(1, 20), randomf(1, 20));
			}*/

			
			/*for (Particle particle : particles) {
				particle.Draw(g_engine.GetRenderer());

			}
			//	// draw line


			/*for (int i = 0; points.size() >  1 && i < points.size() - 1; i++) {
				renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0);
				renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
			}
			g_engine.GetRenderer().SetColor(255, 255, 255, 0);
			scene->Draw(g_engine.GetRenderer());

			g_engine.GetRenderer().EndFrame();
		}

		return 0;
	}
	*/