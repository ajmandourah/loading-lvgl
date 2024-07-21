SET(SOURCES screens/ui_Screen1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_logo_png.c
    fonts/ui_font_mainport.c)

add_library(ui ${SOURCES})
