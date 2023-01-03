#define KEY_SEEN     1
#define KEY_RELEASED 2
#include "AllegroHelper.h"
#include "Winsock.h"
#include "library/Entity.h"


int main() {


	InitializeAllegro();
    
    InitializeImageAddon();

	InstallKeyboard();

    al_install_mouse();

	ALLEGRO_TIMER* timer = CreateTimer(1.0, 30.0);

	ALLEGRO_EVENT_QUEUE* queue =  CreateQueue();

	ALLEGRO_DISPLAY* display = CreateDiplay(800, 600);

	

       
    Entity sol = Entity("soldier.png");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    ALLEGRO_MOUSE_STATE state;

    float x = 100.0;
    float y = 100.0;
    float dx = 0.0;
    float dy = 0.0;
    

    al_start_timer(timer);
    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (key[ALLEGRO_KEY_ESCAPE])
                done = true;

            if (key[ALLEGRO_KEY_D]) {
                printf("fun\n");
            }

            x += dx;
            y += dy;

            if (x < 0)
            {
                x *= -1;
                dx *= -1;
            }
            if (x > 640)
            {
                x -= (x - 640) * 2;
                dx *= -1;
            }
            if (y < 0)
            {
                y *= -1;
                dy *= -1;
            }
            if (y > 480)
            {
                y -= (y - 480) * 2;
                dy *= -1;
            }

            dx *= 0.9;
            dy *= 0.9;

            for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;

            redraw = true;
            break;

        case ALLEGRO_EVENT_MOUSE_AXES:
            dx += event.mouse.dx * 0.1;
            dy += event.mouse.dy * 0.1;
            
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= KEY_RELEASED;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }


        al_get_mouse_state(&state);
        if (state.buttons & 1) {
            /* Primary (e.g. left) mouse button is held. */
            //printf("Mouse position: (%d, %d)\n", state.x, state.y);
            //printf("mouse 1 is down\n");
        }
        else if (state.buttons & 2) {
            //printf("mouse 2 is down\n");
        }
        else {
            //printf("mouse is up\n");
        }
        

        

        if (redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            sol.Render(x,y);
            
            al_flip_display();

            redraw = false;
        }
    }

    
    sol.Destroy();
    
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

	return 0;

}