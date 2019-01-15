#include "GameMain.h"
#include "Console.h"
#include <memory>

#include <string>



int main() {
	//‰ŠúÝ’è
	Console* console = Console::getIns();
	console->SetScreenSize(100, 40);
	console->SetFontSize(18);

	std::unique_ptr<Game> game = std::make_unique<Game>();

	game->initialize();

	while (true) {
		game->update();
		//game->render();
	}

	game->finalize();

	

	return 0;
}