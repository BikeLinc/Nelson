#include "NelsonEngine.h"

int main() {
	Window window("Nelson");
	window.init();

	Scene scene(glm::vec4(0.25, 0.25, 0.35, 1.0));

	Model rectangle(glm::vec2(0.25), "../res/images/chong.png");
	 
	ModelInstance player(&rectangle, Transform());

	scene.add(player);

	scene.start();

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

		player.transform.position += playerMovement.position;

		scene.update();

		scene.draw();

		window.update();
	}

	scene.destroy();
	
	window.terminate();

	return 0;
}
