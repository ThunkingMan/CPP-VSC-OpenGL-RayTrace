#include "SysClass.h"
#include <memory>

int main() {
	// Create the system object.
	std::unique_ptr<SysClass> c_SysClass = std::make_unique<SysClass>();
 	if (! c_SysClass)
	{
		std::printf("Error: Creating System Core Class.\n");
		return 1;
	}

	//Initialize the system core class
	if (! c_SysClass->Init()) return  1;
	return 0;
}
