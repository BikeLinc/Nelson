/******************************************************************************
 *
 * @file	Scene.h
 *
 * @author	Lincoln Scheer
 * @since	02/23/2022
 *
 * @breif	Scene is the class that Nelson uses to describe where and how 
 *		to render an object.
 *
 *****************************************************************************/

#ifndef SCENE_H
#define SCENE_H

#include "NelsonEngine.h"

struct Transform {
	glm::vec3 position, rotation, scale;
	Transform(glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1)) {
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
	}
};

struct Mesh {
	unsigned int VBO, VAO, EBO;
	glm::vec2 size;
	Mesh(glm::vec2 size) {
		this->size = size;
		float width2 = size.x / 2, height2 = size.y / 2;
		float vertices[] = {
			// positions          // texture coords
			 width2,  height2, 0.0f,   -1.0, -1.0, // top right
			 width2, -height2, 0.0f,   -1.0, 0.0f, // bottom right
			-width2, -height2, 0.0f,   0.0f, 0.0f, // bottom left
			-width2,  height2, 0.0f,   0.0f, -1.0  // top left 
		};

		unsigned int indices[] = {
		    0, 1, 3, // first triangle
		    1, 2, 3  // second triangle
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
};

struct Sprite {
	unsigned int textureID = 0;
	glm::vec2 meshBounds;
	Transform transform;
	Mesh* mesh;
	Shader* shader;

	Sprite(const char* texturePath, glm::vec2 meshBounds, Transform transformOrigin) {
		textureID = TextureLoader(texturePath).getTexture();
		this->meshBounds = meshBounds;
		this->transform = transformOrigin;
		mesh = new Mesh(meshBounds);
		shader = new Shader("../res/shaders/vert.glsl", "../res/shaders/frag.glsl");
		shader->use();
		shader->setInt("textureSRC", textureID);
	}

	Sprite(const char* texturePath, Transform transformOrigin) {
		TextureLoader texLoader(texturePath);
		textureID = texLoader.getTexture();
		int max = std::max(texLoader.width, texLoader.height);
		this->meshBounds = glm::vec2(texLoader.width/max, texLoader.height/max);
		this->transform = transformOrigin;
		mesh = new Mesh(meshBounds);
		shader = new Shader("../res/shaders/vert.glsl", "../res/shaders/frag.glsl");
		shader->use();
		shader->setInt("textureSRC", textureID);
	}

	virtual void update(double delta) {

	}

	void draw() {
		glActiveTexture(GL_TEXTURE0 + textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		// create transformations
		glm::mat4 model_transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		model_transform = glm::translate(model_transform, transform.position);
		model_transform = glm::rotate(model_transform, transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		model_transform = glm::rotate(model_transform, transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		model_transform = glm::rotate(model_transform, transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		model_transform = glm::scale(model_transform, transform.scale);

		// get matrix's uniform location and set matrix
		shader->use();
		unsigned int transformLoc = glGetUniformLocation(shader->ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model_transform));

		// render container
		glBindVertexArray(mesh->VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void destroy() {
		glDeleteVertexArrays(1, &mesh->VAO);
		glDeleteBuffers(1, &mesh->VBO);
		glDeleteBuffers(1, &mesh->EBO);
	}
};

class Scene {
public:
	glm::vec4 backgroundColor;
	

	Scene(glm::vec4 backgroundColor = glm::vec4(1)) {
		this->backgroundColor = backgroundColor;
	}

	void add(Sprite& model) {
		models.push_back(&model);
	}

	void update(double delta) {
		for (int i = 0; i < models.size(); i++) {
			models.at(i)->update(delta);
		}
	}

	void draw() {
		glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
		glClear(GL_COLOR_BUFFER_BIT);
		for (int i = 0; i < models.size(); i++) {
			models.at(i)->draw();
		}
	}

	void destroy() {
		for (int i = 0; i < models.size(); i++) {
			models.at(i)->destroy();
		}
	}

private:
	std::vector<Sprite*> models;
};

#endif
