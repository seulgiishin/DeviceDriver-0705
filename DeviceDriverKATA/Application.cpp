#include <iostream>
#include <vector>

#include "DeviceDriver.h"

using namespace std;

class Application {
public:
	Application(DeviceDriver* driver)
		:driver(driver) {}

	void readAndPrint(long startAddr, long endAddr) {
		//vector<int> result;

		for (int i = 0; i < endAddr - startAddr+1; i++) {
			cout << driver->read(startAddr + i) << endl;
		}
	}

	void writeAll(int value) {
		for (int i = 0; i < 5; i++) {
			driver->write(i, value);
		}
	}

private:
	DeviceDriver* driver;
};