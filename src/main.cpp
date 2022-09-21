#pragma once
#include "ShaderProgram.h"
#include "Texture.h"
#include "Mesh.h"
#include "MeshGen.h"
#include "MatrixUtils.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	ShaderProgram shaderProgram("./Assets/Shaders/Standard.vert",
		"./Assets/Shaders/UnlitTextured.frag");
	shaderProgram.activate();
	
	std::vector<glm::mat4> cubeModelMats = std::vector<glm::mat4>();

	glm::mat4 cubeModelMat = MatrixUtils::createTransformation(
		glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec3(-15.0f, 45.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	);

	glm::mat4 screenModelMat = MatrixUtils::createTransformation(
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	);
	glm::vec3 screenBL = screenModelMat * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
	glm::vec3 screenBR = screenModelMat * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
	glm::vec3 screenTL = screenModelMat * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);

	glm::vec3 viewPoint = glm::vec3(0.0f, 0.0f, -5.0f);
	glm::vec3 viewFwd = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 viewUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 viewMat = glm::lookAt(viewPoint, viewPoint + viewFwd, viewUp);
	shaderProgram.setUniform("View", viewMat);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 300.0f);
	shaderProgram.setUniform("Projection", projection);

	Texture checkerboardTexture("./Assets/Textures/checkerboard.png", GL_RGB);
	checkerboardTexture.activate(0);
	shaderProgram.setUniform("DiffuseTexture", 0);
	shaderProgram.setUniform("TintColor", glm::vec4(1.0f));
		
	Mesh cubeMesh = MeshGen::createCubeMesh();
	Mesh screenMesh = MeshGen::createQuadMesh();

	float timeAtPreviousFrame = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		float deltaTime = glfwGetTime() - timeAtPreviousFrame;
		timeAtPreviousFrame = glfwGetTime();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cubeMesh.activate();
		shaderProgram.setUniform("Model", cubeModelMat);
		shaderProgram.setUniform("TintColor", glm::vec4(1.0f));
		cubeMesh.draw();

		screenMesh.activate();
		shaderProgram.setUniform("Model", screenModelMat);
		shaderProgram.setUniform("TintColor", glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
		screenMesh.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}