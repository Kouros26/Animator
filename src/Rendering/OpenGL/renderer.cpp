#include "Rendering/OpenGL/renderer.hpp"

#include <glad/glad.h>
#include <iostream>

#include "EngineObjects/gameObject.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Rendering/OpenGL/shader.hpp"
#include "Resources/model.hpp"
#include "Resources/resourceManager.hpp"

Renderer::Renderer(const Camera& camera)
{
	CreateShaders();
	LinkAttributes();
	SetupCamera(camera);
	glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
	glDeleteProgram(shaderProgram);
}

void Renderer::Clear() const
{
	glClearColor(1, 1, 1, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(std::vector<GameObject>& objects, Camera& camera) const
{
	const unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
	const unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.GetTransform().GetMatrix()));

	for (auto& object : objects)
	{
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(object.GetTransform().GetMatrix()));
		object.GetModel().Draw(shaderProgram);
	}
}

void Renderer::CreateShaders()
{
	const std::shared_ptr<Shader> vertexShader = ResourceManager::Get<Shader>("resources/shaders/vertex.vert", 0);

	const std::shared_ptr<Shader> fragmentShader = ResourceManager::Get<Shader>("resources/shaders/frag.frag", 1);

	shaders.push_back(vertexShader);
	shaders.push_back(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader->GetId());
	glAttachShader(shaderProgram, fragmentShader->GetId());
	glLinkProgram(shaderProgram);

	char infoLog[512]{};
	int success;

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::LINKING\n" << infoLog << std::endl;
	}

	glUseProgram(shaderProgram);
}

void Renderer::LinkAttributes()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
		static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);
}

void Renderer::SetupCamera(const Camera& camera) const
{
	const unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera.GetProjectionMatrix()));
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