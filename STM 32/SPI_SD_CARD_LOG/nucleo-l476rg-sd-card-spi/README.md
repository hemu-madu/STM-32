# SD card tests on Nucleo L476RG

Tests with SD card on Nucleo L476RG - via SPI interface.

## Serial interface

Log output is sent on USART2.

Pinout:
    - TX: PA2
    - RX: PA3
(This is attached to the Virtual Coms Port - i.e. the USB interface - by default, so you can hopefully just plug in your USB cable.)

Baud-rate: 115200
No hardware flow-control.

## SPI bus

The SPI pins are
    - MOSI: PB5
    - MISO: PB4
    - SCK: PB3
    - CS: PB8

## Usage

By default the firmware will simply

1. list the files in the root folder on the SD card.
2. read the contents of a file called /test1.txt in the root folder (if it exists)

The results are printed via the serial interface (see above).

## Porting to another STM32 microcontroller

Porting to another STM32 microcontroller will require the use of STM32CubeMX (or STM32CubeIDE - which has STM32CubeMX built in).
These steps assume you are familiar with using STM32CubeMX.

### SPI configuration

1. Enable the SPI peripheral of your choice.
2. In the peripheral configuration, choose
    1. Data size: 8 bits
    2. Prescaler: whatever is necessary to ensure that the baud rate is between 1 MHz and 20 MHz.
    3. CPOL: Low
    4. CPHA: 1 Edge
    5. NSSP Mode: DISABLED
3. Under 'Project manager' -> 'Advanced settings', choose 'LL' for the SPI driver

### FatFS configuration

1. In the 'Middleware' category, select FATFS.
2. Enable the 'User defined' mode

### SD card - SPI bridge

Copy the folder 'Drivers/sd_card_spi_wrapper' to the 'Drivers' folder in your new project.

In STM32CubeIDE

1. Right click on the project name and select 'Properties'.
2. Expand the 'C/C++ General' section
3. Select the 'Paths and Symbols' sub-section.
4. Select the 'Includes' tab
5. Add 'Drivers/sd_card_spi_wrapper' to the list of paths.
    1. Ensure 'Add to all configurations' is ticked.

You then need to verify that the driver is using the correct SPI peripheral.

In the folder you just copied, open the file `low_level_spi.c` and find the line

```
static SPI_TypeDef *spi = SPI1;
```

If you chose SPI1 in STM32CubeMX you don't need to change anything.
If not, just change SPI1 to the appropriate value (e.g. SPI2).

### Point FATFS library to the driver

In STM32CubeIDE, navigate to the folder `FATFS` -> `Target`, and open the file `user_diskio.c`.

Add
```
#include "sd_card_spi.h"
```
to the list of includes, and then update each of the placeholder functions `USER_initialize()`, `USER_status()`, `USER_read()`, `USER_write()` and `USER_ioctl()` as shown in the example in this project.

