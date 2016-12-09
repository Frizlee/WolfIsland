#include "Application.hpp"
#include <iostream>

int main(int argc, char** argv)
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

