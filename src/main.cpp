#pragma once
#include "ShaderProgram.h"
#include "Texture.h"
#include "MeshGen.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 480, "OpenGL Template", NULL, NULL);	

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	ShaderProgram shaderProgram("./Assets/Shaders/Standard.vert",
		"./Assets/Shaders/UnlitTextured.frag");
	shaderProgram.activate();
	
	glm::mat4 modelMat = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, 5.0f));
	modelMat = glm::rotate(modelMat, glm::radians(-25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMat = glm::rotate(modelMat, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shaderProgram.setUniform("Model", modelMat);

	glm::vec3 viewPoint = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 viewFwd = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 viewUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 viewMat = glm::lookAt(viewPoint, viewPoint + viewFwd, viewUp);
	shaderProgram.setUniform("View", viewMat);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 300.0f);
	shaderProgram.setUniform("Projection", projection);

	Texture checkerboardTexture("./Assets/Textures/checkerboard.png", GL_RGB);
	checkerboardTexture.activate(0);
	shaderProgram.setUniform("DiffuseTexture", 0);
		
	Mesh mesh = MeshGen::createCubeMesh();
	mesh.activate();

	float timeAtPreviousFrame = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		float deltaTime = glfwGetTime() - timeAtPreviousFrame;
		timeAtPreviousFrame = glfwGetTime();

		modelMat = glm::rotate(modelMat, glm::radians(45.0f * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderProgram.setUniform("Model", modelMat);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mesh.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}