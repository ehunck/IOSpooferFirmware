#include "UI.h"
#include "ST7735Driver.h"
#include "Encoder.h"

#define TICKER_UPDATE_TIME_US   1000
#define TICKER_UPDATE_TIME_MS   1

// #define SCE_PIN     PA_4
// #define RST_PIN     D7
// #define DC_PIN      D6
// #define DN_PIN      PB_5
// #define SCLK_PIN    PB_3

static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];                     /*Declare a buffer for 10 lines*/
static lv_disp_drv_t disp_drv;               /*Descriptor of a display driver*/
static lv_indev_drv_t indev_drv;

static ST7735Driver lcd(D5, D6, PB_15, PC_2, PB_13, D7);
static Encoder encoder(D4, D3, D2);

static void DisplayFlush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p)
{
    int32_t x, y;

    lcd.SetAddressWindow(area->x1, area->y1, area->x2, area->y2);

    for(y = area->y1; y <= area->y2; y++)
    {
        for(x = area->x1; x <= area->x2; x++)
        {
            /* Put a pixel to the display.*/
            lcd.SetPixel(color_p->full);
            color_p++;
        }
    }

    /* Indicate you are ready with the flushing*/
    lv_disp_flush_ready(disp);
}

static bool encoder_read(lv_indev_drv_t * drv, lv_indev_data_t*data)
{
    data->enc_diff = encoder.GetEncoderChange();

    if(encoder.GetButtonState())
    {
        data->state = LV_INDEV_STATE_PR;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
    return false; /*No buffering now so no more data read*/
}

UI::UI() :
    indev(NULL)
{
    
}

UI::~UI()
{
    
}

void UI::Init()
{
    lcd.Init();
    encoder.Init();

    lv_init();
    
    // Initialize the display buffer
    lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);
    lv_disp_drv_init(&disp_drv); 
    disp_drv.flush_cb = DisplayFlush;       
    disp_drv.buffer = &disp_buf;       
    lv_disp_drv_register(&disp_drv);   

    // Initialize input device
    
    lv_indev_drv_init(&indev_drv);      /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = encoder_read;
    /*Register the driver in LittlevGL and save the created input device object*/
    indev = lv_indev_drv_register(&indev_drv); 
    
    _time_update.attach_us(callback(this, &UI::UpdateTime), TICKER_UPDATE_TIME_US);
}

void UI::Update()
{
    lv_task_handler();
}

void UI::UpdateTime()
{
    lv_tick_inc(TICKER_UPDATE_TIME_MS);
}


