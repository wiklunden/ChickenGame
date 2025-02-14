#include "RenderWindow.h"

SDL_Renderer* RenderWindow::renderer;

RenderWindow::RenderWindow(const char* P_TITLE, const int& P_WIDTH, const int& P_HEIGHT)
	: window(nullptr) {
	window = SDL_CreateWindow(P_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, P_WIDTH, P_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		std::cout << "Failed to initialize window!\nError: " << SDL_GetError() << "\n";
	}

	// Creates a renderer.
	// Makes sure renderer uses the GPU, if one exists.
	// Game keeps up with monitor's refreshrate with PresentVSync.
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Window* RenderWindow::getWindow() const {
	return window;
}

SDL_Texture* RenderWindow::loadTexture(const char* P_FILEPATH) {
	SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(renderer, P_FILEPATH);

	if (texture == nullptr) {
		std::cout << "Failed to load texture!\nError: " << SDL_GetError() << "\n";
	}

	return texture;
}

int RenderWindow::getRefreshRate() {
	int displayIndex = SDL_GetWindowDisplayIndex(window);
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);

	return mode.refresh_rate;
}

void RenderWindow::cleanUp() {
	SDL_DestroyWindow(window);
}

void RenderWindow::clear() {
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity) {
	SDL_Rect src = p_entity.getCurrentFrame();
	SDL_Rect dst{};

	dst.x = p_entity.getPos().x * p_entity.getScaler();
	dst.y = p_entity.getPos().y * p_entity.getScaler();
	dst.w = src.w * p_entity.getScaler();
	dst.h = src.h * p_entity.getScaler();

	SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dst);
}

void RenderWindow::render(std::vector<Entity*>& vec) {
	for (auto& it : vec) {
		SDL_Rect src = it->getCurrentFrame();
		SDL_Rect dst{};

		dst.x = it->getPos().x * it->getScaler();
		dst.y = it->getPos().y * it->getScaler();
		dst.w = src.w * it->getScaler();
		dst.h = src.h * it->getScaler();

		SDL_RenderCopy(renderer, it->getTexture(), &src, &dst);
	}
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}