#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Particles.h"
#include "Random.h"
#include "ETime.h"
#include "MathUtils.h"
#include "Model.h"

#include <SDL.h>
#include <iostream>
#include <vector>
#include <fmod.hpp>

int main(int argc, char* argv[])
{
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game engine", 800, 600);

	// create audio system
	FMOD::System* audio;
	FMOD::System_Create(&audio);

	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

	Input input;
	input.Initialize();


	Time time;

	std::vector<Particle> particles;
	float offset = 0;
	/*for (int i = 0; i < 10000; i++) {
		particles.push_back(Particle{ {rand() % 800, rand() % 800} , { randomf(100,300), 0.0f } } );

	}*/



	FMOD::Sound* sound = nullptr;
	

	std::vector<FMOD::Sound*> sounds;
	audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
	
	audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
	
	audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);



	std::vector<Vector2> points;
	points.push_back(Vector2{ -5, 5 });
	points.push_back(Vector2{ 0, -5 });
	points.push_back(Vector2{ 5, 5 });
	points.push_back(Vector2{ -5, 5 });

	Model model{ points, Color{1,1,1,0} };

	Vector2 position{ 400, 300 };
	float rotation = 0;

	bool quit = false;
	while (!quit)
	{
		time.Tick();
		std::cout << time.GetTime() << std::endl;

		input.Update();
		audio->update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPrevKeyDown(SDL_SCANCODE_Q)){
			audio->playSound(sounds[0], 0, false, nullptr);
		}

		if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPrevKeyDown(SDL_SCANCODE_W)) {
			audio->playSound(sounds[1], 0, false, nullptr);
		}

		if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPrevKeyDown(SDL_SCANCODE_E)) {
			audio->playSound(sounds[2], 0, false, nullptr);
		}

		if (input.GetKeyDown(SDL_SCANCODE_R) && !input.GetPrevKeyDown(SDL_SCANCODE_R)) {
			audio->playSound(sounds[3], 0, false, nullptr);
		}

		if (input.GetKeyDown(SDL_SCANCODE_T) && !input.GetPrevKeyDown(SDL_SCANCODE_T)) {
			audio->playSound(sounds[4], 0, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_Y) && !input.GetPrevKeyDown(SDL_SCANCODE_Y)) {
			audio->playSound(sounds[5], 0, false, nullptr);
		}
		Vector2 velocity{ 0, 0 };
		if (input.GetKeyDown(SDL_SCANCODE_UP)) velocity.y = -100;
		if (input.GetKeyDown(SDL_SCANCODE_DOWN)) velocity.y = 100;
		if (input.GetKeyDown(SDL_SCANCODE_LEFT)) velocity.x = -100;
		if (input.GetKeyDown(SDL_SCANCODE_RIGHT)) velocity.x = 100;

		position = position + velocity * time.GetDeltaTime();
		rotation = velocity.Angle();

		Vector2 mousePosition = input.GetMousePosition();
		if (input.GetMouseButtonDown(0)) {
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
				particle.Update(time.GetDeltaTime());
				if (particle.position.x > 800) {
					particle.position.x = 0;
				}
				if (particle.position.x < 0) {
					particle.position.x = 800;
				}
				if (particle.lifespan != 0) {
					particle.lifespan -= time.GetDeltaTime();
				}
			}


			if (input.GetMouseButtonDown(0) && !input.GetPrevMouseButtonDown(0)) {
				std::cout << "mouse pressed" << std::endl;
				points.push_back(mousePosition);
			}

			if (input.GetMouseButtonDown(0) && input.GetPrevMouseButtonDown(0)) {
				float distance = (points.back() - mousePosition).Length();
				if (distance > 5) {
					points.push_back(mousePosition);
				}
			}

			//	// clear screen
			renderer.SetColor(0, 0, 0, 0);
			renderer.BeginFrame();
			//	SDL_RenderClear(renderer);
			/*renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
			float radius = 30;
			offset += (90 * time.GetDeltaTime());
			for (float angle = 0; angle < 360; angle += 360 / 30) {
				float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.1f) * radius;
				float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.1f) * radius;

				renderer.DrawRect(400 + x, 300 + y, randomf(1, 20), randomf(1, 20));
			}*/

			
			for (Particle particle : particles) {
				particle.Draw(renderer);

			}
			//	// draw line


			/*for (int i = 0; points.size() >  1 && i < points.size() - 1; i++) {
				renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0);
				renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
			}*/
			renderer.SetColor(255, 255, 255, 0);
			model.Draw(renderer, position, rotation, 5);


			renderer.EndFrame();
		}

		return 0;
	}