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

TEST_F(DriverFixture, DeviceDriverReadTest2) {
	EXPECT_CALL(memory, read(0x55))
		.WillOnce(Return(0xA))
		.WillOnce(Return(0xA))
		.WillOnce(Return(0xA))
		.WillOnce(Return(0xA))
		.WillOnce(Return(0xB));

	EXPECT_THROW({driver->read(0x55);
		}, std::exception);
}

TEST_F(DriverFixture, DeviceDriverWriteTest) {
	NiceMock<MockFlshMemoryDevice> mk;
	DeviceDriver dr(&mk);

	EXPECT_CALL(mk, read(0xDD))
		.Times(1)
		.WillRepeatedly(Return(0xFF));

	dr.write(0xDD, 0x72);
}

TEST_F(DriverFixture, WriteExceptionTest) {

	EXPECT_CALL(memory, read(0xDD))
		.WillRepeatedly(Return(0xFA));

	EXPECT_THROW({ driver->write(0xDD, 0xAA);
		},std::exception);
}

TEST_F(DriverFixture, DeviceDriverReadAndPrintTest) {

	EXPECT_CALL(memory, read(_))
		.WillRepeatedly(Return(0xfd));

	app->readAndPrint(0, 4);
}

TEST_F(DriverFixture, DeviceDriverWriteAllTest) {
	NiceMock<MockFlshMemoryDevice> mk;
	DeviceDriver dr(&mk);
	Application appi(&dr);

	EXPECT_CALL(mk, read(_))
		.Times(5)
		.WillRepeatedly(Return(0xFF));

	appi.writeAll(0xaf);
}

TEST_F(DriverFixture, DeviceDriverWriteAllTestException) {

	EXPECT_CALL(memory, read(_))
		.WillRepeatedly(Return(0xFA));

	EXPECT_THROW({ app->writeAll(0xdf);
		}, std::exception);
}

