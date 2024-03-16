#include "Application/application.hpp"

Application::Application()
{
	for (int i = 0; i < 1000; i ++)
	{
		GameObject& obj = gameObjectManager.CreateGameObject("Cube");
		obj.GetTransform().SetPosition({ i * 4, 0, 0 });
	}
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
