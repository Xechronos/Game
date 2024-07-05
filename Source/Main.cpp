#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Particles.h"
#include "Random.h"
#include "ETime.h"

#include <SDL.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game engine", 800, 600);

	Input input;
	input.Initialize();

	Time time;

	std::vector<Particle> particles;
	/*for (int i = 0; i < 10000; i++) {
		particles.push_back(Particle{ {rand() % 800, rand() % 800} , { randomf(100,300), 0.0f } } );

	}*/


	std::vector<Vector2> points;
	
	bool quit = false;
	while (!quit)
	{
		time.Tick();
		std::cout << time.GetTime() << std::endl;

		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		Vector2 mousePosition = input.GetMousePosition();
		if (input.GetMouseButtonDown(0)) {
			particles.push_back(Particle{ mousePosition, { randomf(-100,100), randomf(-100,100) } , {randomf(1, 5)}});
		}

		for (Particle& particle : particles) {
			particle.Update(time.GetDeltaTime());
			if (particle.position.x > 800) {
				particle.position.x = 0;
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

		renderer.SetColor(255, 255, 255, 0);
		for (Particle particle : particles) {
			if (particle.lifespan >= 0) {
				particle.Draw(renderer);
			}
		}
		//	// draw line
		

		/*for (int i = 0; points.size() >  1 && i < points.size() - 1; i++) {
			renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0);
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}*/

		

		renderer.EndFrame();
	}

	return 0;
}