/**
  ******************************************************************************
  * @file    Src/main.c
  * @author  Wuard
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include <stdio.h>

/* ---------------- Debug UART ---------------- */
#define UART_ID uart0
#define UART_TX_PIN 0   // GPIO0 → TX
#define UART_RX_PIN 1   // GPIO1 → RX
#define UART_BAUDRATE 115200

/* ---------------- SPI ---------------- */
#define LT_SPI_PORT spi0
#define SPI_BAUDRATE 1000000  // 1 MHz, can be adjusted according to the device

// SPI pins (adjust them to your actual connection)
#define SPI_SCK_PIN  2   // GPIO2 → SCK
#define SPI_MOSI_PIN 3   // GPIO3 → MOSI
#define SPI_MISO_PIN 4   // GPIO4 → MISO
#define SPI_CS_PIN   5   // GPIO5 → Chip Select

/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

#endif /* __MAIN_H */
