#include <stdint.h>
#include <stdio.h>
#include <serial.h>
#include <parsing.h>

// Define the interpolation function
int interpolation(uint16_t channel) {
    const uint16_t INPUT_MAX = 2047;
    const int OUTPUT_MAX = 254;
    return (channel * OUTPUT_MAX) / INPUT_MAX;
}

int main(int argc, char** argv) {
    // File pointers for serial ports
    FILE *sbus; 
    FILE *sabertooth;

    // To store sbus packets
    uint8_t sbus_packet[15];

    // To store value of individual RC channel
    uint16_t *channel;

    // PWM value after interpolation 
    int pwm;

    // Open serial ports
    sbus = open_file(argv[1], "rb");
    sabertooth = open_file(argv[2], "w+");
    
    // Read data from RC transmitter using SBUS
    read_SBUS(sbus_packet, uint8_t, 25, sbus);

    // Parse SBUS packet
    channel = parse_buffer(sbus_packet);

    // Interpolate and write data to Sabertooth
    pwm = interpolation(channel[0]); // Interpolate first channel value
    write_to_SB(sabertooth, "%d", pwm); // Send the interpolated PWM value

    // Close serial ports
    close_file(sbus);
    close_file(sabertooth);

    return 0;
}
