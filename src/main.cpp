#include "application.hpp"

int main()
{
	const Application app;

	while (!app.ShouldClose())
	{
		app.Render();
	}
}
