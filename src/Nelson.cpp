#include "NelsonEngine.h"

int main() {
	Window window("Nelson");
	window.init();

	Scene scene(glm::vec4(0.25, 0.25, 0.35, 1.0));

	Sprite sprite("../res/images/chong.png", Transform());

	scene.add(sprite);

	float playerMovementSpeed = 0.005f;

	while (window.isOpen()) {

		Transform playerMovement;

		if (window.isKeyDown(GLFW_KEY_W)) {
			playerMovement.position.y += playerMovementSpeed;
		}
		if (window.isKeyDown(GLFW_KEY_S)) {
			playerMovement.position.y -= playerMovementSpeed;
		}
		if (window.isKeyDown(GLFW_KEY_A)) {
			playerMovement.position.x -= playerMovementSpeed;
		}
		if (window.isKeyDown(GLFW_KEY_D)) {
			playerMovement.position.x += playerMovementSpeed;
		}

		sprite.transform.position += playerMovement.position;

		scene.draw();

		window.update();
	}

	scene.destroy();
	
	window.terminate();

	return 0;
}
