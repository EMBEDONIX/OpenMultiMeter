//
// Created by Saeid Yazdani on 12/14/2024.
//

#pragma once

#include <iostream>
#include <fmt/core.h>

#include "embedonix/omm/drivers/register_interface.hpp"

#include "embedonix/omm/drivers/device_register.hpp"

namespace embedonix::omm::drivers::ads_8699 {

    /// @brief The number of address bits used in the ADS8699 ADC device.
    /// This value specifies the width of the address field for the device's registers.
    /// It determines the maximum number of unique register addresses supported by the device.    
    constexpr unsigned int NUM_ADDRESS_BITS = 9;


    /// @brief The number of data bits used in the ADS8699 ADC device.
    /// This value specifies the size of the device's registers in bits.
    /// It determines the maximum resolution of the data handled by the device.
    constexpr unsigned int NUM_DATA_BITS = 32;

    class ADS8699Register : public DeviceRegister<9, 32> {
    protected:
        void
        init(unsigned int address, unsigned int resetValue,
             const std::string &name, const std::string &description) override {
            this->mAddress = address;
            this->mResetValue = resetValue;
            this->mValue = 0;
            this->mName = name;
            this->mDescription = description;
        };

    public:
        ADS8699Register(unsigned int address, unsigned int resetValue,
                        const std::string &name,
                        const std::string &description) {
            mName = name;
            mDescription = description;
            init(address, resetValue, name, description);
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

    /// @brief Enumeration of the register addresses for the ADS8699 ADC device.
    /// This enum class provides named constants for various registers of the device,
    /// along with a description of their purpose.
    ///
    /// Each register serves specific functionality within the ADS8699 device:
    /// - **DeviceId**: Contains the unique identifier for the device.
    /// - **Power**: Manages power and reset functionality.
    /// - **SDI**: Configures the serial data input settings.
    /// - **SDO**: Configures the serial data output settings.
    /// - **DataOut**: Controls the output data from the ADC.
    /// - **RangeSelect**: Selects the input voltage range.
    /// - **AlarmOut**: Indicates alarm or error statuses.
    /// - **AlarmHighThreshold**: Sets the upper threshold for alarms.
    /// - **AlarmLowThreshold**: Sets the lower threshold for alarms.
    enum class RegisterAddress : unsigned int {
        DeviceId = 0x00, //< Device ID register: Contains the unique identifier for the device.
        Power = 0x04, //< Reset and power control register: Manages power and reset functionality.
        SDI = 0x08, //< Serial Data Input control register: Configures the serial data input settings.
        SDO = 0x0C, //< Serial Data Output control register: Configures the serial data output settings.
        DataOut = 0x10, //< Output data control register: Controls the output data from the ADC.
        RangeSelect = 0x14, //< Input range selection control register: Selects the input voltage range.
        AlarmOut = 0x20, //< ALARM output register: Indicates alarm or error statuses.
        AlarmHighThreshold = 0x24, //< ALARM high threshold/hysteresis register: Sets the upper threshold for alarms.
        AlarmLowThreshold = 0x28, //< ALARM low threshold register: Sets the lower threshold for alarms.
    };

    class ADS8699 {
    private:
        /*
        // std::vector<std::unique_ptr<RegisterInterface*> > mRegisters = {
        std::vector<RegisterInterface *> mRegisters = {
            // {std::make_unique<RegisterInterface>(0x00, 0x00, "DEVICE_ID_REG", "Device ID register")},
            // {std::make_unique<RegisterInterface>(0x04, 0x00, "RST_PWRCTL_REG", "Reset and power control register")},

            {
                new ADS8699Register(static_cast<unsigned int>(RegisterAddress::DeviceId),
                                    0x00, "DEVICE_ID_REG", "Device ID register")
            },
            {new ADS8699Register(0x04, 0x00, "RST_PWRCTL_REG", "Reset and power control register")},

        };
        */

        std::vector<std::unique_ptr<RegisterInterface> > mRegisters;

    private:
        void initRegisters() {
            mRegisters.emplace_back(std::make_unique<ADS8699Register>(
                static_cast<unsigned int>(RegisterAddress::DeviceId),
                0x00, "DEVICE_ID_REG",
                "Contains the unique identifier for the device."));
            mRegisters.emplace_back(std::make_unique<ADS8699Register>(
                static_cast<unsigned int>(RegisterAddress::Power),
                0x00, "RST_PWRCTL_REG",
                "Manages power and reset functionality."));
            mRegisters.emplace_back(std::make_unique<ADS8699Register>(
                static_cast<unsigned int>(RegisterAddress::SDI),
                0x00, "SDI_CTRL_REG",
                "Configures the serial data input settings."));
            mRegisters.emplace_back(std::make_unique<ADS8699Register>(
                static_cast<unsigned int>(RegisterAddress::SDO),
                0x00, "SDO_CTRL_REG",
                "Configures the serial data output settings."));
            mRegisters.emplace_back(std::make_unique<ADS8699Register>(
                static_cast<unsigned int>(RegisterAddress::DataOut),
                0x00, "DATA_OUT_CTRL_REG",
                "Controls the output data from the ADC."));
            mRegisters.emplace_back(std::make_unique<ADS8699Register>(
                static_cast<unsigned int>(RegisterAddress::RangeSelect),
                0x00, "RANGE_SEL_CTRL_REG",
                "Selects the input voltage range."));
            mRegisters.emplace_back(std::make_unique<ADS8699Register>(
                static_cast<unsigned int>(RegisterAddress::AlarmOut),
                0x00, "ALARM_OUT_REG",
                "Indicates alarm or error statuses."));
            mRegisters.emplace_back(std::make_unique<ADS8699Register>(
                static_cast<unsigned int>(RegisterAddress::AlarmHighThreshold),
                0x00, "ALARM_HIGH_THR_REG",
                "Sets the upper threshold for alarms."));
            mRegisters.emplace_back(std::make_unique<ADS8699Register>(
                static_cast<unsigned int>(RegisterAddress::AlarmLowThreshold),
                0x000000FF, "ALARM_LOW_THR_REG",
                "Sets the lower threshold for alarms."));
        }

    public:
        ADS8699() {
            initRegisters();
        }

    public:
        void printRegistersInfo() const {
            for (const auto &reg: mRegisters) {
                std::cout << dynamic_cast<DeviceRegister<NUM_ADDRESS_BITS, NUM_DATA_BITS> *>(reg.get())->toString() << std::endl;
            }
        }

        ADS8699(const ADS8699 &) = delete;
    };
}
