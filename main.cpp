#include <iostream>
#include <pigpio.h>

#include <thread>
#include <chrono>

#include "include/embedonix/omm/drivers/ads8699.hpp"

using namespace std::chrono_literals;

constexpr auto i2cBus = 1;
constexpr auto tmpSensorRight = 0x40;
constexpr auto tmpSensorLeft = 0x4f;

constexpr auto adcRestPin = 4;
constexpr auto mod2EnablePin = 17;

double convert_temperature(const char *buf) {
    int temp = ((buf[0] << 8) | buf[1]) >> 3; // Drop the last 3 bits
    if (temp > 0x7FF0) {
        // 2's complement
        temp |= 0xF000; // toggle MSB sign bit
    }
    return temp * 0.0625; // Each bit represents 0.125°C
}

// Function to configure the ADC
void configureADC(int spiHandle) {
    uint8_t configCmd[] = {0b1100'1000, 0b00100000, 0x00, 0x00}; // Example: Write command, register, data MSB, data LSB
    if (spiWrite(spiHandle, reinterpret_cast<char *>(configCmd), sizeof(configCmd)) < 0) {
        std::cerr << "Failed to configure ADC" << std::endl;
    } else {
        std::cout << "ADC configured successfully" << std::endl;
    }
}

// Function to read ADC data
uint16_t readADC(int spiHandle) {
    uint8_t readCmd[] = {0x10, 0x00, 0x00}; // Example read command + two dummy bytes
    uint8_t response[3] = {0};

    if (spiXfer(spiHandle, reinterpret_cast<char *>(readCmd), reinterpret_cast<char *>(response),
                sizeof(readCmd)) < 0) {
        std::cerr << "Failed to read ADC data" << std::endl;
        return 0;
    }

    // Combine response bytes into a 16-bit value
    uint16_t adcValue = (response[1] << 8) | response[2];
    return adcValue;
}


// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    embedonix::omm::drivers::ads_8699::ADS8699 ads8699VoltMeter;
    ads8699VoltMeter.printRegistersInfo();

    // MAX6633 I2C address.
    int MAX6633_ADDR = tmpSensorRight; // Adjust based on your device's datasheet


    // Initialize the pigpio library
    if (gpioInitialise() < 0) {
        std::cerr << "Failed to initialize PIGPIO.\n";
        return 1;
    }

    // Open an I2C connection to the MAX6633
    int i2cHandle = i2cOpen(1, MAX6633_ADDR, 0);
    if (i2cHandle < 0) {
        std::cerr << "Failed to open I2C bus.\n";
        gpioTerminate();
        return 1;
    }

    for (int i = 0; i < 2; ++i) {
        char buf[2];
        if (i2cReadDevice(i2cHandle, buf, 2) != 2) {
            std::cerr << "Failed to read temperature data.\n";
        } else {
            // Usage:
            double temperature = convert_temperature(buf);
            std::cout << "Temperature: " << temperature << " °C" << std::endl;
        }
        std::this_thread::sleep_for(500ms); // Add a 500ms delay
    }

    // Close the I2C connection
    i2cClose(i2cHandle);

    // Work on ADC
    gpioSetMode(mod2EnablePin, PI_OUTPUT);
    gpioSetMode(adcRestPin, PI_OUTPUT);

    // Enable access to voltage module by enabling ADUM1400 digital isolator
    gpioWrite(mod2EnablePin, 1);
    std::this_thread::sleep_for(100ms);

    gpioWrite(adcRestPin, 1); // Set ADC rst pin to high

    // Bring down ADC rest pin for a few ms to reset it and then bring it back up
    gpioWrite(adcRestPin, 0);
    std::this_thread::sleep_for(10ms);
    gpioWrite(adcRestPin, 1);


    // Enable SPI functionality

    // Set SPI channel
    int spiChannel = 0; // SPI channel (0 or 1 based on your setup)
    int spiBaudRate = 500000; // SPI speed in Hz (adjust as needed)

    // Open an SPI connection
    int spiHandle = spiOpen(spiChannel, spiBaudRate, 0);
    if (spiHandle < 0) {
        std::cerr << "Failed to open SPI bus.\n";
        gpioTerminate();
        return 1;
    }

    std::cout << "SPI bus enabled on channel " << spiChannel << " with baud rate " << spiBaudRate << ".\n";

    // Perform SPI operations here if needed
    configureADC(spiHandle);

    readADC(spiHandle);

    // Close SPI connection
    spiClose(spiHandle);


    // Terminate the pigpio library
    gpioTerminate();

    return 0;
}


// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.
