#include "app.h"


App::App() {
	config = new Config();
	config->LoadConfig("config.cfg");
}

App::~App() {
	delete(config);
}

int App::Run(int argI, const char** argV) {
	return 0;
}
