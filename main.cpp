#include "mbed.h"
#include "lvgl.h"
#include "UI.h"

DigitalOut led(LED1);

UI& user_interface = UI::instance();

static void event_handler(lv_obj_t * obj, lv_event_t event)
{

}

int main()
{
    user_interface.Init();

    lv_group_t * g = lv_group_create();

    lv_obj_t * spinbox1 = lv_spinbox_create(lv_scr_act(), NULL);
    lv_spinbox_set_digit_format(spinbox1, 5, 3);
    lv_spinbox_step_prev(spinbox1);
    lv_obj_set_width(spinbox1, 100);
    lv_obj_align(spinbox1, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);
    lv_obj_set_event_cb(spinbox1, event_handler);

    lv_obj_t * spinbox2 = lv_spinbox_create(lv_scr_act(), NULL);
    lv_spinbox_set_digit_format(spinbox2, 5, 3);
    lv_spinbox_step_prev(spinbox2);
    lv_obj_set_width(spinbox2, 100);
    lv_obj_align(spinbox2, NULL, LV_ALIGN_IN_TOP_MID, 0, 40);
    lv_obj_set_event_cb(spinbox2, event_handler);

    lv_group_add_obj(g, spinbox1);
    lv_group_add_obj(g, spinbox2 );
    lv_indev_set_group(user_interface.indev, g);

    while(1)
    {
        user_interface.Update();
       led = !led;
       ThisThread::sleep_for(500); 
    }
}
