#include <stdexcept>
#include <string>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../DeviceDriverKATA/DeviceDriver.cpp"
#include "../DeviceDriverKATA/Application.cpp"

using namespace std;
using namespace testing;

class MockFlshMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), ());
	MOCK_METHOD(void, write, (long address, unsigned char data), ());
};

class DriverFixture : public testing::Test {
protected:
	void SetUp() override{
		driver = new DeviceDriver(&memory);
		app = new  Application(driver);
	}
public:
	void checkRead(int count) {
		EXPECT_CALL(memory, read(_))
			.Times(count);
	}

	MockFlshMemoryDevice memory;
	DeviceDriver* driver;
	Application* app;
};

TEST_F(DriverFixture, DeviceDriverReadTest) {
	checkRead(5);
	driver->read(1);
}

TEST_F(DriverFixture, DeviceDriverWriteTest) {
	checkRead(5);
	try {
		//act
		driver->write(1, 1);
		FAIL();
	}
	catch (std::runtime_error& e) {
		//assert
		EXPECT_EQ(string(e.what()), string("WRITE ERROR"));
	}
}

TEST_F(DriverFixture, DeviceDriverWriteTest2) {
	checkRead(10);

	for (int i = 0; i < 2; i++) {
		try {
			//act
			driver->write(1, 1);
			FAIL();
		}
		catch (std::runtime_error& e) {
			//assert
			EXPECT_EQ(string(e.what()), string("WRITE ERROR"));
		}
	}
}

TEST_F(DriverFixture, DeviceDriverReadAndPrintTest) {

	checkRead(25);

	app->readAndPrint(0, 4);
}

TEST_F(DriverFixture, DeviceDriverWriteAllTest) {
	checkRead(5);

	try {
		//act
		app->writeAll(1111);
		FAIL();
	}
	catch (std::runtime_error& e) {
		//assert
		EXPECT_EQ(string(e.what()), string("WRITE ERROR"));
	}
}

