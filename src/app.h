#ifndef _APP_H_
#define _APP_H_

#include "config.h"



class App {
private:
	Config *config;

public:
	App();
	~App();

	int Run(int argI, const char** argV);
};
#endif
