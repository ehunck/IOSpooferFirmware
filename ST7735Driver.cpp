#include "ST7735Driver.h"

ST7735Driver::ST7735Driver(PinName cs, PinName dc, PinName mosi, PinName miso, PinName sclk, PinName rst) :
    _spi( mosi, miso, sclk, cs, use_gpio_ssel ),
    _dc(dc),
    _rst(rst),
    _height(ST7735_TFTHEIGHT),
    _width(ST7735_TFTWIDTH)
{

}

ST7735Driver::~ST7735Driver()
{

}

void ST7735Driver::WriteCommand(uint8_t data)
{
    _dc = 0;
    _spi.write(data);
}

void ST7735Driver::WriteData(uint8_t data)
{
    _dc = 1;
    _spi.write(data);
}

void ST7735Driver::Init()
{
    _rst = 0;
    // configure SPI
	_spi.frequency();

    _rst = 1;
    ThisThread::sleep_for(5);
    _rst =  0;
    ThisThread::sleep_for(20);
    _rst = 1;
    ThisThread::sleep_for(150);

    //************* Start Initial Sequence **********// 
 	WriteCommand(0xb1);		//Frame rate 80Hz
	WriteData(0x02);	       
	WriteData(0x35);
	WriteData(0x36);
	
	WriteCommand(0xb2);		//Frame rate 80Hz
	WriteData(0x02);	         
	WriteData(0x35);
	WriteData(0x36);
	
	WriteCommand(0xb3);		//Frame rate 80Hz
	WriteData(0x02);	         
	WriteData(0x35);
	WriteData(0x36);
	WriteData(0x02);	         
	WriteData(0x35);
	WriteData(0x36);
	WriteCommand(0xb4);		//Column inversion
	WriteData(0x07);	         
	WriteCommand(0xc0);		//
	WriteData(0xa2);	         
	WriteData(0x02);//02
	WriteData(0x84);//84
	
	WriteCommand(0xc1);		//
	WriteData(0x45);	         
	
	WriteCommand(0xc2);		//
	WriteData(0x0a);	         
	WriteData(0x00);
	
	WriteCommand(0xc3);		//
	WriteData(0x8a);	         
	WriteData(0x2a);
	
	WriteCommand(0xc4);		//
	WriteData(0x8a);	         
	WriteData(0xee);
	
	WriteCommand(0xc5);		//VCOM
	WriteData(0x03);	         
	
	WriteCommand(0x36);		//
	WriteData(0xC8);	         
	
	WriteCommand(0xe0);		
	WriteData(0x12);	         
	WriteData(0x1c);
	WriteData(0x10);
	WriteData(0x18);	         
	WriteData(0x33);
	WriteData(0x2c);
	WriteData(0x25);	         
	WriteData(0x28);
	WriteData(0x28);
	WriteData(0x27);	         
	WriteData(0x2f);
	WriteData(0x3c);
	WriteData(0x00);	         
	WriteData(0x03);
	WriteData(0x03);
	WriteData(0x10);	         
	
	WriteCommand(0xe1);		
	WriteData(0x12);	         
	WriteData(0x1c);
	WriteData(0x10);
	WriteData(0x18);	         
	WriteData(0x2d);
	WriteData(0x28);
	WriteData(0x23);	         
	WriteData(0x28);
	WriteData(0x28);
	WriteData(0x26);	         
	WriteData(0x2f);
	WriteData(0x3d);
	WriteData(0x00);	         
	WriteData(0x03);
	WriteData(0x03);
	WriteData(0x10);
	
	WriteCommand(0x3A); //65k mode 
	WriteData(0x05); 	

    WriteCommand(0x11);    //Exit Sleep 
    ThisThread::sleep_for(120); 		
    WriteCommand(0x29);    //Display on 
}

void ST7735Driver::SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    WriteCommand(ST7735_CASET); // Column addr set
    WriteData(x0 >> 8);
    WriteData(x0+0x02);     // XSTART 
    WriteData(x1 >> 8);
    WriteData(x1+0x02);     // XEND

    WriteCommand(ST7735_PASET); // Row addr set
    WriteData(y0>>8);
    WriteData(y0+0x03);     // YSTART
    WriteData(y1>>8);
    WriteData(y1+0x03);     // YEND

    WriteCommand(ST7735_RAMWR); // write to RAM

	_dc = 1; // setup for subsequent pixel writes
}

void ST7735Driver::SetPixel(uint16_t color)
{
	uint8_t hi = color >> 8, lo = color;
	_spi.write(hi);
	_spi.write(lo);
}

void ST7735Driver::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) 
{
    // rudimentary clipping (drawChar w/big text requires this)
    if((x >= _width) || (y >= _height)) 
    {   
        return;
    }
    if((x + w - 1) >= _width)
    {
        w = _width  - x;
    }
    if((y + h - 1) >= _height)
    {
        h = _height - y;
    }

    SetAddressWindow(x, y, x+w-1, y+h-1);

    uint8_t hi = color >> 8, lo = color;

    _dc = 1;

    for(y=h; y>0; y--) 
    {
        for(x=w; x>0; x--) 
        {
            _spi.write(hi);
            _spi.write(lo);
        }
    }
}