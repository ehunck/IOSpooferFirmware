#ifndef __UI_H__
#define __UI_H__

#include "mbed.h"
#include "lvgl.h"


class UI
{
public:
    static UI& instance()
    {
        static UI singleton;
        return singleton;
    }
    
    void Init();
    void Update();
    lv_indev_t * indev;

private:
    UI();
    virtual ~UI();
    
    void UpdateTime();
    Ticker _time_update;

    
};

#endif // __UI_H__
