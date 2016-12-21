#include "Application.hpp"
#include <iostream>

#ifdef _DEBUG
int main(int argc, char** argv)
#else
#include <Windows.h>
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	try
	{
		Application app{ "Wyspa wilków", { 1024, 768 } };
		app.run();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

