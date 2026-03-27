#include "serial.h"
#include "fatfs.h"
#include <stdio.h>
#include <string.h>

extern serial_t *console;

static char msg[128];

static void write_test_file(void)
{
    FIL fp;
    UINT bytes_written;

    const char *data =
        "Hello Hemu bro!\r\n"
        "STM32 SD Card Write Test Successful!\r\n";

    serial_println(console, "Creating file log.txt ...");

    // Create new file or overwrite if exists
    FRESULT fr = f_open(&fp, "log.txt", FA_CREATE_ALWAYS | FA_WRITE);

    if (fr != FR_OK) {
        serial_println(console, "Failed to create/open file!");
        return;
    }

    serial_println(console, "File opened successfully.");

    fr = f_write(&fp, data, strlen(data), &bytes_written);

    if (fr != FR_OK || bytes_written != strlen(data)) {
        serial_println(console, "Write failed!");
        f_close(&fp);
        return;
    }

    serial_println(console, "Data written successfully.");

    // VERY IMPORTANT: close file to save data
    f_close(&fp);

    serial_println(console, "File closed.");
}

void test_sd_card(void)
{
    write_test_file();
}
