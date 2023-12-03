#pragma once
#include "ShaderProgram.h"
#include "Texture.h"
#include "Mesh.h"
#include "MeshGen.h"
#include "MatrixUtils.h"
#include "OffAxisProjection.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 640, "OpenGL Template", NULL, NULL);	

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

		
	Mesh skyboxMesh = MeshGen::createCubeMesh(true);
	glm::mat4 skyboxModelMat = MatrixUtils::createTransformation(
		glm::vec3(0.0f),
		glm::vec3(0.0f),
		glm::vec3(1.0f) * 100.0f
	);

	Mesh cubeMesh = MeshGen::createCubeMesh();
	glm::mat4 cubeModelMat = MatrixUtils::createTransformation(
		glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec3(-15.0f, 45.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	);

	Mesh screenMesh = MeshGen::createQuadMesh();
	glm::mat4 screenModelMat = MatrixUtils::createTransformation(
		glm::vec3(0.1f, 0.0f, 2.0f),
		glm::vec3(0.0f, 30.0f, 10.0f),
		glm::vec3(1.0f)
	);

	ShaderProgram shaderProgram("./Assets/Shaders/Standard.vert",
		"./Assets/Shaders/UnlitTextured.frag");
	shaderProgram.activate();

	Texture checkerboardTexture("./Assets/Textures/checkerboard.png", GL_RGB);
	checkerboardTexture.activate(0);
	shaderProgram.setUniform("DiffuseTexture", 0);
	shaderProgram.setUniform("TintColor", glm::vec4(1.0f));

	glm::vec3 viewPoint = glm::vec3(0.0f, 0.0f, -5.0f);
	glm::vec3 screenBL_WS = screenModelMat * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
	glm::vec3 screenBR_WS = screenModelMat * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
	glm::vec3 screenTL_WS = screenModelMat * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);

	glm::mat4 viewMat = OffAxisProjection::offAxisViewManual2(viewPoint, screenBL_WS, screenBR_WS, screenTL_WS);
	shaderProgram.setUniform("View", viewMat);

	glm::vec3 screenBL_VS = viewMat * glm::vec4(screenBL_WS, 1.0f);
	glm::vec3 screenBR_VS = viewMat * glm::vec4(screenBR_WS, 1.0f);
	glm::vec3 screenTL_VS = viewMat * glm::vec4(screenTL_WS, 1.0f);
	glm::mat4 projectionOffAxis = OffAxisProjection::offAxisFrustum(screenBL_VS, screenBR_VS, screenTL_VS, 0.1f, 20.0f);
	glm::mat4 projectionPerspective = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 50.0f);
	glm::mat4 projection = projectionOffAxis;
	std::cout << glm::to_string(projection) << std::endl;
	shaderProgram.setUniform("Projection", projection);

	float timeAtPreviousFrame = glfwGetTime();
	bool wasOneKeyDown = false;
	while (!glfwWindowShouldClose(window))
	{
		float deltaTime = glfwGetTime() - timeAtPreviousFrame;
		timeAtPreviousFrame = glfwGetTime();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*
		screenModelMat = MatrixUtils::createTransformation(
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, glm::sin(timeAtPreviousFrame) * 45.0f, 0.0f),
			glm::vec3(1.0f)
		);
		*/

		cubeMesh.activate();
		shaderProgram.setUniform("Model", cubeModelMat);
		shaderProgram.setUniform("TintColor", glm::vec4(1.0f));
		cubeMesh.draw();

		// Transparent objects don't write to the z buffer
		glDepthMask(false);

		screenMesh.activate();
		shaderProgram.setUniform("Model", screenModelMat);
		shaderProgram.setUniform("TintColor", glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
		screenMesh.draw();

		glDepthMask(true);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}