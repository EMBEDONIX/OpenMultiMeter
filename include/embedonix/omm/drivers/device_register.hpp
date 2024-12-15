//
// Created by Saeid Yazdani on 12/15/2024.
//

#pragma once
#include "register_interface.hpp"

namespace embedonix::omm::drivers {
    template<unsigned int AddressBits = 8, unsigned int RegisterBits = 16>
        requires (AddressBits < RegisterBits && RegisterBits <= 32)
    class DeviceRegister : public RegisterInterface {
    protected:
        //! @brief Register address as a bitset.
        std::bitset<AddressBits> mAddress;

        //! @brief Reset value of the register, represented as a bitset.
        std::bitset<RegisterBits> mResetValue;

        //! @brief Current/actual value of the register, representing its state.
        std::bitset<RegisterBits> mValue;

        //! @brief Short name of the register.
        std::string mName;
        //! @brief Description of the register.
        std::string mDescription;

        virtual void
        init(unsigned int address, unsigned int resetValue,
             const std::string &name, const std::string &description) = 0;

    public:
        //! @brief Address of the register.
        //! @return The address as a bitset.
        const std::bitset<AddressBits> &address() const {
            return mAddress;
        }

        //! @brief Reset value of the register.
        //! @return The reset value as a bitset.
        const std::bitset<RegisterBits> &resetValue() const {
            return mResetValue;
        }

        //! @brief Actual value of the register.
        //! @return The current/actual value as a bitset.
        const std::bitset<RegisterBits> &value() const {
            return mValue;
        }

        //! @brief Name of the register.
        //! @return The name of the register as a string.
        const std::string &name() const {
            return mName;
        }

        //! @brief Description of the register.
        //! @return The description of the register as a string.
        const std::string &description() const {
            return mDescription;
        }


        //! @brief Returns a formatted string representation of the device register fields.
        //! @return A string with the formatted details of the register in tabular form.
        std::string toString() const {
            // "{:<20}: 0x{:09X}\n", "Address",
            return fmt::format(
                "{:<20}: 0x{:0{}X}\n"
                "{:<20}: 0x{:0{}X}\n"
                "{:<20}: 0x{:0{}X}\n"
                "{:<20}: {}\n"
                "{:<20}: {}\n",
                "Address", mAddress.to_ulong(), AddressBits / 4 + (AddressBits % 4 != 0),
                "Reset Value", mResetValue.to_ulong(), RegisterBits / 4 + (RegisterBits % 4 != 0),
                "Actual Value", mValue.to_ulong(), RegisterBits / 4 + (RegisterBits % 4 != 0),
                "Name", mName,
                "Description", mDescription
            );
        }
    };
}
