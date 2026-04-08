#include "Application/application.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

Application::Application()
{
	CreateObjects();
	AddComponents();
}

Application::~Application()
{
	delete animator;
}

void Application::Update()
{
	renderer.Clear();
	time.UpdateDeltaTime();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ProcessInput(time.GetDeltaTime());

	renderer.Render(gameObjectManager.GetGameObjects(), gameObjectManager.GetMainCamera());

	window.GetUIManager().Draw();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	window.SwapBuffers();
	window.PollEvents();
}

bool Application::ShouldClose() const
{
	return window.ShouldClose();
}

void Application::CreateObjects()
{
	GameObject& obj = gameObjectManager.CreateGameObject("bob", "resources/models/Gunan/Head/default.fbx", "resources/models/Gunan/Head/textures/diffuse.png");
	obj.GetTransform().SetPosition({ 50, 0, -300 });

	GameObject& ground = gameObjectManager.CreateGameObject("ground", "resources/models/cube.obj");
	ground.GetTransform().SetPosition({ 0, -100, -300 });
	ground.GetTransform().SetScale({ 200, 1, 200 });
}

void Application::AddComponents()
{
	animator = new MorphTargetAnimator(gameObjectManager.GetGameObjects()[0].GetModel());
	animator->Init("resources/models/GunanAnims/");
	window.GetUIManager().SetAnimator(*animator);
	window.GetUIManager().SetRenderer(renderer);
}

void Application::ProcessInput(const double& deltaTime)
{
	GLFWwindow* windowRef = window.GetWindow();

	if (glfwGetKey(windowRef, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(windowRef, true);

	//if (glfwGetKey(windowRef, GLFW_KEY_MINUS) == GLFW_PRESS)
	//	renderer.ToggleWireFrame();

	if (glfwGetKey(windowRef, GLFW_KEY_W) == GLFW_PRESS)
		gameObjectManager.GetMainCamera().GetTransform().AddPosition(glm::vec3{ 0, 0, 100 } *= deltaTime);

	if (glfwGetKey(windowRef, GLFW_KEY_A) == GLFW_PRESS)
		gameObjectManager.GetMainCamera().GetTransform().AddPosition(glm::vec3{ 100, 0, 0 } *= deltaTime);

	if (glfwGetKey(windowRef, GLFW_KEY_S) == GLFW_PRESS)
		gameObjectManager.GetMainCamera().GetTransform().AddPosition(glm::vec3{ 0, 0, -100 } *= deltaTime);

	if (glfwGetKey(windowRef, GLFW_KEY_D) == GLFW_PRESS)
		gameObjectManager.GetMainCamera().GetTransform().AddPosition(glm::vec3{ -100, 0, 0 } *= deltaTime);
}
