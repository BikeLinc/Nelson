#include "NelsonEngine.h"

class Sprite : public Model {
public:
	Sprite(const char* texturePath, glm::vec2 meshBounds, Transform transformOrigin) : Model(texturePath, PlaneGeometry(meshBounds), transformOrigin) {

	}

	void update(double delta) override {
		transform.position.x += delta * 0.05;;
	}
};

int main() {
	Window window("Nelson");
	window.init();

	Renderer renderer;
	renderer.init();

	Gui gui;
	gui.init(window.getWindow());

	Scene scene(glm::vec4(0.25, 0.25, 0.35, 1.0));

	Sprite sprite("../res/images/chong.png", glm::vec2(0.25), Transform());

	scene.add(sprite);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (window.isOpen()) {

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		scene.update(deltaTime);

		renderer.render(&scene);

		gui.draw();

		window.update();
	}

	scene.destroy();

	gui.terminate();
	
	window.terminate();

	return 0;
}
