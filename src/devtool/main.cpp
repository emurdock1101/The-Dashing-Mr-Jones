#include "DevTool.h"
#include <iostream>

using namespace std;

int main(int argc, char ** argv) {
	DevTool* devtool = new DevTool();
	devtool->start();

	delete devtool;
	return 0;
}
