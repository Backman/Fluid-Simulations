#include "Application.h"

int main(int argc, const char** argv) {
	srand(time(NULL));

	Application app;
	app.init(1024, 768, "Ragdoll Simulation");

	app.run();

	app.shutdown();

	return 0;
}