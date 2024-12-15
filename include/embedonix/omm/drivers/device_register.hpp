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
        std::bitset<NumDataBits> mActualValue;

        virtual void
        init(unsigned int address,
             unsigned int resetValue) = 0;
    };
}
