//
// Created by Saeid Yazdani on 12/15/2024.
//

#pragma once
#include "register_interface.hpp"

namespace embedonix::omm::drivers {
    template<unsigned int NumAddressBits = 8, unsigned int NumDataBits = 16>
        requires (NumAddressBits < NumDataBits && NumDataBits <= 32)
    class DeviceRegister : public RegisterInterface {
    protected:
        //! @brief Register address as a bitset.
        std::bitset<NumAddressBits> mAddress;

        //! @brief Reset value of the register, represented as a bitset.
        std::bitset<NumDataBits> mResetValue;

        //! @brief Current/actual value of the register, representing its state.
        std::bitset<NumDataBits> mValue;

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
        const std::bitset<NumAddressBits> &address() const {
            return mAddress;
        }

        //! @brief Reset value of the register.
        //! @return The reset value as a bitset.
        const std::bitset<NumDataBits> &resetValue() const {
            return mResetValue;
        }

        //! @brief Actual value of the register.
        //! @return The current/actual value as a bitset.
        const std::bitset<NumDataBits> &value() const {
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
    };
}
