#include "GameMain.h"
#include <memory>


int main() {

	std::unique_ptr<Game> game = std::make_unique<Game>();

	game->initialize();

	while (true) {
		game->update();
		game->render();
	}

	game->finalize();

	

	return 0;
}