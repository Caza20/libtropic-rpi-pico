/**
  ******************************************************************************
  * @file    Src/main.c
  * @author  Wuard
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/  
#include <stdio.h>
#include "../inc/main.h"

#include "hardware/spi.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "../inc/main.h"
#include "libtropic_examples.h"
#include "libtropic_functional_tests.h"
#include "libtropic_logging.h"
#include "lt_port_rpi_pico.h"   // versión adaptada del lt_port_stm32_nucleo_f439zi.h

/* Private macro -------------------------------------------------------------*/
#define LOG_OUT(f_, ...) printf(f_, ##__VA_ARGS__)
#define NUM_OF_PING_CMDS 1

/* Private variables ---------------------------------------------------------*/
// The Pico W LED is GPIO25, same for the regular Pico.
#define LED_PIN 25


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void) {
    
    // Initialize UART for printf (via USB)
    stdio_init_all();

    // Initialize GPIO for LED
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Wait for a while
    sleep_ms(5000);

    // libtropic related code BEGIN
    // libtropic related code BEGIN
    // libtropic related code BEGIN
    // libtropic related code BEGIN
    // libtropic related code BEGIN

    printf("=== Raspberry Pi Pico + libtropic ejemplo ===\n");

    // libtropic related code BEGIN
    lt_handle_t __lt_handle__ = {0};

#if LT_SEPARATE_L3_BUFF
    uint8_t l3_buffer[L3_PACKET_MAX_SIZE] __attribute__((aligned(16))) = {0};
    __lt_handle__.l3.buff = l3_buffer;
    __lt_handle__.l3.buff_len = sizeof(l3_buffer);
#endif

    // Device (adapted for Pico)
    lt_dev_pico device = {0};

    device.spi_instance = LT_SPI_PORT;
    device.spi_baudrate = SPI_BAUDRATE;
    device.cs_pin = SPI_CS_PIN;
    device.pin_miso = SPI_MISO_PIN;
    device.pin_mosi = SPI_MOSI_PIN;
    device.pin_sck = SPI_SCK_PIN;

    __lt_handle__.l2.device = &device;

#ifdef LT_BUILD_TESTS
#include "lt_test_registry.c.inc"
#endif

#ifdef LT_BUILD_EXAMPLES
#include "lt_ex_registry.c.inc"
    UNUSED(__lt_ex_return_val__);
#endif

    LT_FINISH_TEST();

    // libtropic related code END
    // libtropic related code END
    // libtropic related code END
    // libtropic related code END
    // libtropic related code END

    // Loop with blinking LED
    while (1) {
        gpio_put(LED_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
    }

    return 0;
}
