# Tropic01 with Raspberry Pi Pico (RP2040)

Devboard's web: https://www.raspberrypi.com/documentation/microcontrollers/pico-series.html#pico-1-family


## Wiring

Use TROPIC01 shield (Arduino form factor), or wire chip according to following diagram:

```
|------------|------------------|
|  TROPIC01  |   Rpi Pico       |
|------------|------------------|
|  GND       |  GND             |
|  3V3       |  3V3             |
|  MISO      |  GPIO_4          |
|  MOSI      |  GPIO_3          |
|  SCK       |  GPIOA_2         |
|  CS        |  GPIOD_5         |
|------------|------------------|
```

Use TROPIC01 shield (Mikroe form factor), or wire chip according to following diagram:

```
|------------|------------------|
|  TROPIC01  |   Rpi Pico       |
|------------|------------------|
|  GND       |  GND             |
|  3V3       |  3V3             |
|  SDO       |  GPIO_4          |
|  SDI       |  GPIO_3          |
|  SCK       |  GPIO_2          |
|  CS        |  GPIO_5          |
|------------|------------------|
```

# Wuard - v0.1 - 08-2025
