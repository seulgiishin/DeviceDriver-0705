#include <stdexcept>
#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int result = (int)(m_hardware->read(address));
    int prevresult = result;
    for (int i = 0; i < 4; i++) {
        result = (int)(m_hardware->read(address));
        
        if (prevresult != result) {
            throw std::runtime_error("READ ERROR");
        }
        prevresult = result;
    }
    return result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    if (read(address) != 0xFF) {
        throw std::runtime_error("WRITE ERROR");
    }
    m_hardware->write(address, (unsigned char)data);
}