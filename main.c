#include "lvgl/lvgl.h"
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "lvgl/src/display/lv_display.h"
#include "ui/ui.h"
static const char *getenv_default(const char *name, const char *dflt)
{
    return getenv(name) ? : dflt;
}

static void lv_linux_disp_init(void)
{
    lv_area_t render_area; 

    render_area.x1 = 0;
    render_area.x2 = 640;
    render_area.y1 = 0;
    render_area.y2 = 480;
    const char *device = getenv_default("LV_LINUX_FBDEV_DEVICE", "/dev/fb0");
    lv_display_t * disp = lv_linux_fbdev_create();
    lv_display_set_resolution(disp, 480, 640);

    lv_disp_set_rotation(disp,LV_DISPLAY_ROTATION_90);
    lv_display_rotate_area(disp,&render_area);
    lv_linux_fbdev_set_file(disp, device);
}
int main(int args, char * argv[])
{
 

    lv_init();

    /*Linux display device init*/
    lv_linux_disp_init();

    ui_init();
    // lv_display_set_resolution(NULL, 640, 480);


    if (args ==1){
        _ui_label_set_property(ui_Label1, _UI_LABEL_PROPERTY_TEXT, "loading");
    }else {  
        _ui_label_set_property(ui_Label1, _UI_LABEL_PROPERTY_TEXT, argv[1]);
    }
    /*Handle LVGL tasks*/
    lv_timer_handler();
    usleep(100);

    return 0;
}
