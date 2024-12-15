//
// Created by Saeid Yazdani on 12/14/2024.
//

#pragma once

#include "embedonix/omm/drivers/register_interface.hpp"
#include "embedonix/omm/drivers/device_register.hpp"

namespace embedonix::omm::drivers::ads_8699 {
    class ADS8699Register : public DeviceRegister<9, 32> {
    protected:
        void
        init(unsigned int address,
             unsigned int resetValue) override {
            this->mAddress = address;
            this->mResetValue = resetValue;
            this->mActualValue = 0;
        };

    public:
        ADS8699Register(unsigned int address, unsigned int resetValue) {
        };


        unsigned int
        read() override {
            throw std::runtime_error("ADS8699Register::read() is not implemented yet.");
        };

        bool
        write(unsigned int value) override {
            throw std::runtime_error("ADS8699Register::write() is not implemented yet.");
        }
    };
}
