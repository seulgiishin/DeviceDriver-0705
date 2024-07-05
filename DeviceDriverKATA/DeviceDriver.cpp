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
            throw std::exception();
        }
        prevresult = result;
    }
    return result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    if ((int)(m_hardware->read(address)) != 0xFF) {
        throw std::exception();
    }
    m_hardware->write(address, (unsigned char)data);
}