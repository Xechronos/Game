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

	// create texture, using shared_ptr so texture can be shared
	res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("hydra logo.png", engine->GetRenderer());


	while (!engine->IsQuit()) {
		engine->Update();
		engine->GetRenderer().SetColor(255, 0, 0, 0);
		engine->GetRenderer().BeginFrame();
		engine->GetPS().Draw(engine->GetRenderer());
		engine->GetRenderer().DrawTexture(texture.get(), 30, 30, 0);
		engine->GetRenderer().EndFrame();
	}

	engine->Shutdown();
	return 0;
}