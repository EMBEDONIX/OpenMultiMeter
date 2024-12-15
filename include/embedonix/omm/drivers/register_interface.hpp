//
// Created by Saeid Yazdani on 12/13/2024.
//

#pragma once

#include <concepts>
#include <variant>
#include <bitset>
#include <vector>
#include <memory>

//! @class RegisterInterface
//! @brief Abstract base class for hardware register interfacing.
//!
//! The RegisterInterface defines a set of methods that concrete
//! classes must implement to facilitate hardware communication
//! involving register read and write operations.
namespace
embedonix::omm::drivers {
    class RegisterInterface {
    public:
        virtual ~RegisterInterface() = default;

        //! @brief Read the current value from the register.
        //! @return The current value of the register.
        virtual unsigned int
        read() = 0;

        //! @brief Write a new value to the register.
        //! @param value The new value to be written to the register as a bitset.
        //! @return True if the operation is successful, false otherwise.
        virtual bool
        write(unsigned int value) = 0;
    };
}
