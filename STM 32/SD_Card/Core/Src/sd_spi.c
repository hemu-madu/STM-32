#include "sd_spi.h"
#include "stdio.h"

extern SPI_HandleTypeDef hspi1;

#define SD_CS_LOW()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define SD_CS_HIGH()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

#define CMD0    0
#define CMD8    8
#define CMD17   17
#define CMD55   55
#define CMD41   41
#define CMD58   58
#define CMD24 24

static uint8_t SPI_TxRx(uint8_t data)
{
    uint8_t rx;
    HAL_SPI_TransmitReceive(&hspi1, &data, &rx, 1, HAL_MAX_DELAY);
    return rx;
}

static uint8_t SD_SendCmd(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    uint8_t frame[6];
    uint8_t response;

    frame[0] = 0x40 | cmd;
    frame[1] = (arg >> 24) & 0xFF;
    frame[2] = (arg >> 16) & 0xFF;
    frame[3] = (arg >> 8) & 0xFF;
    frame[4] = arg & 0xFF;
    frame[5] = crc;

    SPI_TxRx(0xFF);
    HAL_SPI_Transmit(&hspi1, frame, 6, HAL_MAX_DELAY);

    for (int i = 0; i < 10; i++)
    {
        response = SPI_TxRx(0xFF);
        if (!(response & 0x80))
            return response;
    }

    return 0xFF;
}

uint8_t SD_Init(void)
{
    printf("SD_Init Start\r\n");

    SD_CS_HIGH();

    // 80+ clock cycles with CS HIGH
    for (int i = 0; i < 20; i++)
        SPI_TxRx(0xFF);

    HAL_Delay(20);   // give card time to reset

    SD_CS_LOW();
    SPI_TxRx(0xFF);

    // Force CMD0 retry loop
    uint8_t r;
    uint32_t retry = 100;

    do
    {
        r = SD_SendCmd(CMD0, 0, 0x95);
        printf("CMD0 resp: %02X\r\n", r);
    } while ((r != 0x01) && retry--);

    if (r != 0x01)
    {
        SD_CS_HIGH();
        return 1;
    }
uint8_t SD_ReadBlock(uint8_t *buff, uint32_t sector)
{
    uint8_t token;
    uint32_t timeout;

    SD_CS_LOW();
    SPI_TxRx(0xFF);

    if (SD_SendCmd(CMD17, sector, 0xFF) != 0x00)
    {
        SD_CS_HIGH();
        return 1;
    }

    timeout = 0xFFFF;

    do
    {
        token = SPI_TxRx(0xFF);
    } while ((token == 0xFF) && --timeout);

    if (token != 0xFE)
    {
        SD_CS_HIGH();
        return 2;
    }

    for (int i = 0; i < 512; i++)
        buff[i] = SPI_TxRx(0xFF);

    SPI_TxRx(0xFF);
    SPI_TxRx(0xFF);

    SD_CS_HIGH();
    SPI_TxRx(0xFF);

    return 0;
}


uint8_t SD_WriteBlock(const uint8_t *buff, uint32_t sector)
{
    uint8_t resp;
    uint32_t timeout;
    uint16_t i;

    SD_CS_LOW();
    SPI_TxRx(0xFF);

    resp = SD_SendCmd(24, sector, 0xFF);
    if (resp != 0x00)
    {
        SD_CS_HIGH();
        return 1;
    }

    SPI_TxRx(0xFF);
    SPI_TxRx(0xFE);

    for (i = 0; i < 512; i++)
        SPI_TxRx(buff[i]);

    SPI_TxRx(0xFF);
    SPI_TxRx(0xFF);

    resp = SPI_TxRx(0xFF);
    if ((resp & 0x1F) != 0x05)
    {
        SD_CS_HIGH();
        return 2;
    }

    timeout = 0xFFFF;
    while ((SPI_TxRx(0xFF) == 0x00) && timeout--)
        ;

    if (timeout == 0)
    {
        SD_CS_HIGH();
        return 3;
    }

    SD_CS_HIGH();
    SPI_TxRx(0xFF);

    return 0;
}
