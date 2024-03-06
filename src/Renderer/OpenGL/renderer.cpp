#include "Renderer/OpenGL/renderer.hpp"

#include <glad/glad.h>
#include <iostream>

#include "EngineObjects/gameObject.hpp"
#include "Renderer/OpenGL/shader.hpp"
#include "Renderer/OpenGL/texture.hpp"
#include "Resources/model.hpp"

Renderer::Renderer()
{
	CreateShaders();
	LinkAttributes();
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
}

void Renderer::Clear() const
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Render(const std::vector<GameObject>& objects) const
{
	for (const auto& object : objects)
	{
		object.GetModel().Draw();
	}
}

void Renderer::CreateShaders()
{
	const Shader vertexShader("resources/shaders/vertex.vert", 0);

	const Shader fragmentShader("resources/shaders/frag.frag", 1);

	shaders.push_back(vertexShader);
	shaders.push_back(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader.GetId());
	glAttachShader(shaderProgram, fragmentShader.GetId());
	glLinkProgram(shaderProgram);

	char infoLog[512]{};
	int success;

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKING\n" << infoLog << std::endl;
	}

	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader.GetId());
	glDeleteShader(fragmentShader.GetId());
}

void Renderer::LinkAttributes()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
		static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);
}

void Renderer::ToggleWireFrame()
{
	drawWireFrame = !drawWireFrame;
	drawWireFrame ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

bool Renderer::GetDrawWireFrame() const
{
	return drawWireFrame;
}