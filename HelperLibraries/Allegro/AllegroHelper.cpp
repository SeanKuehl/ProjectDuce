#include "AllegroHelper.h"

int InitializeAllegro() {
    if (!al_init())
    {
        printf("couldn't initialize allegro\n");
        return ERROR;
    }
    return SUCCESS;
}

int InitializeImageAddon() {
    if (!al_init_image_addon())
    {
        printf("couldn't initialize image addon\n");
        return ERROR;
    }
    return SUCCESS;
}

int InstallKeyboard() {
    if (!al_install_keyboard())
    {
        printf("couldn't initialize keyboard\n");
        return ERROR;
    }
    return SUCCESS;
}

ALLEGRO_TIMER* CreateTimer(double firstTime, double secondTime) {
    ALLEGRO_TIMER* timer = al_create_timer(firstTime / secondTime); //default 1.0 / 30.0
    if (!timer)
    {
        printf("couldn't initialize timer\n");
        return NULL;
    }

    return timer;
}

ALLEGRO_EVENT_QUEUE* CreateQueue() {
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    if (!queue)
    {
        printf("couldn't initialize queue\n");
        return NULL;
    }
    return queue;
}

ALLEGRO_DISPLAY* CreateDiplay(int screenWidth, int screenHieght) {
    ALLEGRO_DISPLAY* disp = al_create_display(screenWidth, screenHieght);
    if (!disp)
    {
        printf("couldn't initialize display\n");
        return NULL;
    }
    return disp;
}

ALLEGRO_FONT* CreateBuiltInFont() {
    ALLEGRO_FONT* font = al_create_builtin_font();
    if (!font)
    {
        printf("couldn't initialize font\n");
        return NULL;
    }
    return font;
}

ALLEGRO_BITMAP* CreateImage(std::string path) {
    ALLEGRO_BITMAP* image = al_load_bitmap(path.c_str());
    if (!image)
    {
        printf("couldn't load image\n");
        return NULL;
    }
    return image;
}

void RegisterEventSources(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer) {
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
}
