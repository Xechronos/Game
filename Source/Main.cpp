#include "Renderer.h"
#include "Vector2.h"

#include <SDL.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game engine", 600, 800);

	Vector2 v1{ 400, 300 };
	Vector2 v2{ 600, 100 };

	std::vector<Vector2> points;
	for (int i = 0; i < 100; i++) {
		points.push_back(Vector2{ rand() % 800, rand() % 600 });
	}

	while (true)
	{
		Vector2 speed{ 0.1f, -0.1f };
		for (Vector2& point : points) {
			point = point + speed;
		}

		//	// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		//	SDL_RenderClear(renderer);

		//	// draw line
		renderer.SetColor(255,255,255,0);
		renderer.DrawLine(300, 400, 400, 300);
		renderer.DrawLine(400, 300, 500, 400);
		renderer.DrawLine(500, 400, 300, 400);
		renderer.DrawLine(v1.x, v1.y, v2.x, v2.y);

		for (int i = 0; i < points.size() - 1; i++) {
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}

		for (int i = 0; i < 200; i++) {
			renderer.DrawLine(rand() % 300, rand() % 200, rand() % 800, rand() % 600);
			renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0);
			renderer.DrawPoint(rand() % 400, rand() % 300);
		}

		renderer.EndFrame();
	}

	return 0;
}