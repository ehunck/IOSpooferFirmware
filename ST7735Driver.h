#ifndef _ST7735DRIVER_H_
#define _ST7735DRIVER_H_

#include "mbed.h"

#define ST7735_TFTWIDTH  128
#define ST7735_TFTHEIGHT 128

#define ST7735_CASET   0x2A
#define ST7735_PASET   0x2B
#define ST7735_RAMWR   0x2C

// Color definitions
#define	ST7735_BLACK   0x0000
#define	ST7735_BLUE    0x001F
#define	ST7735_RED     0xF800
#define	ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW  0xFFE0  
#define ST7735_WHITE   0xFFFF

class ST7735Driver
{
public:
    ST7735Driver(PinName cs, PinName dc, PinName mosi, PinName miso,
				   PinName sclk, PinName rst);
    virtual ~ST7735Driver();
    void Init();
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
    void SetPixel(uint16_t color);
private:
    void WriteCommand(uint8_t data);
    void WriteData(uint8_t data);
    
    SPI _spi;
    DigitalOut _dc;
    DigitalOut _rst;

    int16_t _height;
    int16_t _width;

};

#endif // _ST7735DRIVER_H_