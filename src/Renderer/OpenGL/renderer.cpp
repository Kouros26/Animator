#include "Renderer/OpenGL/renderer.hpp"

#include <iostream>
#include <glad/glad.h>
#include "Renderer/OpenGL/shader.hpp"

Renderer::Renderer()
{
	GenerateBuffers();
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

void Renderer::Render() const
{
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

void Renderer::GenerateBuffers()
{
	constexpr float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	constexpr unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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