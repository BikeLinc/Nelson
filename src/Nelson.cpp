#include "NelsonEngine.h"

class Player : public Sprite {
public:
	Player(const char* texturePath, glm::vec2 meshBounds, Transform transformOrigin) : Sprite(texturePath, meshBounds, transformOrigin) {

	}

	void update(double delta) override {
		transform.position.x += delta * 0.05;;
	}
};

int main() {
	Window window("Nelson");
	window.init();

	Scene scene(glm::vec4(0.25, 0.25, 0.35, 1.0));

	Player sprite("../res/images/chong.png", glm::vec2(0.25), Transform());

	scene.add(sprite);

	double t0 = 0.0;
	double t1 = 0.0;

	while (window.isOpen()) {
		t0 = t1; t1 = glfwGetTime(); double delta = t1 - t0;

		scene.update(delta);

		scene.draw();

		window.update();
	}

	scene.destroy();
	
	window.terminate();

	return 0;
}
