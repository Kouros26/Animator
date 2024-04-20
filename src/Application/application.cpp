#include "Application/application.hpp"

#include <filesystem>

Application::Application()
{
	gameObjectManager.CreateGameObject("Cube");

	//GameObject vegas = gameObjectManager.CreateGameObject("Vegas", "resources/models/Big Vegas.fbx");
	//vegas.CreateAnimator();

	//Animation breakDance(std::string(PROJECT_PATH) + "resources/animations/Flair.fbx", &vegas.GetModel());
	//vegas.GetAnimator()->PlayAnimation(breakDance);
}

Application::~Application()
{

}

void Application::Update()
{
	renderer.Clear();
	time.UpdateDeltaTime();

	ProcessInput(time.GetDeltaTime());

	renderer.Render(gameObjectManager.GetGameObjects(), gameObjectManager.GetMainCamera());

	window.SwapBuffers();
	window.PollEvents();
}

bool Application::ShouldClose() const
{
	return window.ShouldClose();
}

void Application::ProcessInput(const double& deltaTime)
{
	GLFWwindow* windowRef = window.GetWindow();

	if (glfwGetKey(windowRef, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(windowRef, true);

	if (glfwGetKey(windowRef, GLFW_KEY_MINUS) == GLFW_PRESS)
		renderer.ToggleWireFrame();

	if (glfwGetKey(windowRef, GLFW_KEY_W) == GLFW_PRESS)
		gameObjectManager.GetMainCamera().GetTransform().AddPosition(glm::vec3{ 0, 0, 100 } *= deltaTime);

	if (glfwGetKey(windowRef, GLFW_KEY_A) == GLFW_PRESS)
		gameObjectManager.GetMainCamera().GetTransform().AddPosition(glm::vec3{ 100, 0, 0 } *= deltaTime);

	if (glfwGetKey(windowRef, GLFW_KEY_S) == GLFW_PRESS)
		gameObjectManager.GetMainCamera().GetTransform().AddPosition(glm::vec3{ 0, 0, -100 } *= deltaTime);

	if (glfwGetKey(windowRef, GLFW_KEY_D) == GLFW_PRESS)
		gameObjectManager.GetMainCamera().GetTransform().AddPosition(glm::vec3{ -100, 0, 0 } *= deltaTime);
}
