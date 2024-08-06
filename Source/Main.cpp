#include "Engine.h"

#include <iostream>
#include <vector>
#include <cassert>

int main(int argc, char* argv[]) {
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	engine->Initialize();
	ResourceManager rm = ResourceManager();

#ifdef _Debug
	std::cout << "debug\n";
#endif

	int i = 5;
	ASSERT(i == 5);

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;
	{
		// create texture, using shared_ptr so texture can be shared
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("hydra logo.png", engine->GetRenderer());
		res_t<Font> font = ResourceManager::Instance().Get<Font>("Begok.ttf", 12);
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), "hello", { 0,0,0,1 });
		Transform t{ {30,30} };
		std::unique_ptr<Actor> actor = std::make_unique<Actor>(t);
		std::unique_ptr<TextureComp> component = std::make_unique<TextureComp>();
		component->texture = texture;
		actor->AddComponent(std::move(component));


		while (!engine->IsQuit()) {
			engine->Update();

			actor->Update(engine->GetTime().GetDeltaTime());

			engine->GetRenderer().SetColor(255, 255, 255, 0);
			engine->GetRenderer().BeginFrame();
			engine->GetPS().Draw(engine->GetRenderer());
			/*engine->GetRenderer().DrawTexture(texture.get(), 30, 30, 0);*/
			actor->Draw(engine->GetRenderer());
			text->Draw(engine->GetRenderer(), 400, 400);
			engine->GetRenderer().EndFrame();
		}
	}
	ResourceManager::Instance().Clear();
	engine->Shutdown();
	return 0;
}