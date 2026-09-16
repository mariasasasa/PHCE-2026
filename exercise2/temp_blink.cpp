#include <stdio.h>
   #include "pico/stdlib.h"
   #include "hardware/adc.h"
   #include "hardware/gpio.h"

   int main() {
       // TODO 1: initialize stdio so printf reaches the Serial Monitor
       stdio_init_all();

       // TODO 2: initialize the PicoBricks LED (GPIO 7) as an output
       gpio_init(7);
       gpio_set_dir(7, GPIO_OUT);

       printf("BUILD: RAM\n");  // Provided: flip to RAM in the Flash vs. RAM step

       // Temperature sensor initialization is provided. ADC itself is a later session.
       adc_init();
       adc_set_temp_sensor_enabled(true);
       adc_select_input(4);

       while (true) {
           // Provided: read the sensor and convert to a temperature.
           uint16_t raw = adc_read();                                    // 12-bit
           const float voltage = raw * 3.3f / (1 << 12);                 // full scale 3.3 V
           const float temp_c = 27.0f - (voltage - 0.706f) / 0.001721f;  // RP2040 datasheet

           // Provided: blink delay from the temperature (hotter = faster).
           int delay_ms = static_cast<int>(1000 - 50 * (temp_c - 20));
           if (delay_ms < 100) delay_ms = 100;
           if (delay_ms > 950) delay_ms = 950;

           sleep_ms(500);  // Provided: keep the Serial Monitor readable

           // TODO 3: print the temperature and the raw value
           printf("Temperature: %.2f C, Raw: %d\n", temp_c, raw);

           // TODO 4: blink the LED (on, wait, off, wait)
            gpio_put(7, 1);  // Turn on the LED
            sleep_ms(delay_ms);  // Wait for the calculated delay
            gpio_put(7, 0);  // Turn off the LED
            sleep_ms(delay_ms);  // Wait for the calculated delay
       }
       return 0;
   }