#include "AllegroHelper.h"

/*! Start allegro lib resources.
*   Return -1 if there is an error initializing
*	or 1 if everything worked.
*/
int InitializeAllegro() {
    if (!al_init())
    {
        printf("couldn't initialize allegro\n");
        return ERROR;
    }
    return SUCCESS;
}

/*! Start allegro image addon resources.
*   Return -1 if there is an error initializing
*	or 1 if everything worked.
*/
int InitializeImageAddon() {
    if (!al_init_image_addon())
    {
        printf("couldn't initialize image addon\n");
        return ERROR;
    }
    return SUCCESS;
}

/*! install allegro keyboard resources.
*   Return -1 if there is an error initializing
*	or 1 if everything worked.
*/
int InstallKeyboard() {
    if (!al_install_keyboard())
    {
        printf("couldn't initialize keyboard\n");
        return ERROR;
    }
    return SUCCESS;
}

/*! Create an allegro timer object
*   Return NULL if there is an error initializing
*	or a new ALLEGRO_TIMER* object if everything worked.
*   \param firstTime this is the first part of the timer fps equation(currently 1.0)
*   \param secondTime this is the second part of the timer fps equation(currently 30.0)
*/
ALLEGRO_TIMER* CreateTimer(double firstTime, double secondTime) {
    ALLEGRO_TIMER* timer = al_create_timer(firstTime / secondTime); //default 1.0 / 30.0
    if (!timer)
    {
        printf("couldn't initialize timer\n");
        return NULL;
    }

    return timer;
}

/*! Create an allegro event queue object
*   Return NULL if there is an error initializing
*	or a new ALLEGRO_EVENT_QUEUE* object if everything worked.
*/
ALLEGRO_EVENT_QUEUE* CreateQueue() {
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    if (!queue)
    {
        printf("couldn't initialize queue\n");
        return NULL;
    }
    return queue;
}

/*! Create an allegro display object
*   Return NULL if there is an error initializing
*	or a new ALLEGRO_DISPLAY* object if everything worked.
*   \param screenWidth width of new screen to create
*   \param screenHieght hieght of new screen to create
*/
ALLEGRO_DISPLAY* CreateDiplay(int screenWidth, int screenHieght) {
    ALLEGRO_DISPLAY* disp = al_create_display(screenWidth, screenHieght);
    if (!disp)
    {
        printf("couldn't initialize display\n");
        return NULL;
    }
    return disp;
}

/*! Create an allegro font object
*   Return NULL if there is an error initializing
*	or a new ALLEGRO_FONT* object if everything worked.
*/
ALLEGRO_FONT* CreateBuiltInFont() {
    ALLEGRO_FONT* font = al_create_builtin_font();
    if (!font)
    {
        printf("couldn't initialize font\n");
        return NULL;
    }
    return font;
}

/*! Create an allegro image object
*   Return NULL if there is an error initializing
*	or a new ALLEGRO_BITMAP* object if everything worked.
*   \param path this is the path to the image to load
*/
ALLEGRO_BITMAP* CreateImage(std::string path) {
    ALLEGRO_BITMAP* image = al_load_bitmap(path.c_str());
    if (!image)
    {
        printf("couldn't load image\n");
        return NULL;
    }
    return image;
}

/*! Register various allegro event sources
*   \param queue the event queue to register
*   \param display the display to register
*   \param timer the timer to register
*/
void RegisterEventSources(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer) {
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
}
