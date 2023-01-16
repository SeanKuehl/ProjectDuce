#include "Menu.h"





/*! Show the user a menu with "start server",
*   "start client", and "exit" buttons. Return
*    2 if they choose to start server, and 1
*    if they choose client.
*/
int Menu() {


    

    
    



    InitializeAllegro();

    InitializeImageAddon();

    InstallKeyboard();

    al_install_mouse();

    ALLEGRO_TIMER* timer = CreateTimer(1.0, 30.0);

    ALLEGRO_EVENT_QUEUE* queue = CreateQueue();

    ALLEGRO_DISPLAY* display = CreateDiplay(800, 600);






    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    bool done = false;
    bool redraw = true;
    bool mousePressed = false;
    
    ALLEGRO_EVENT event;

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    ALLEGRO_MOUSE_STATE state;

    ALLEGRO_BITMAP* startServerButton = CreateImage("assets/images/menu/button.png");
    ALLEGRO_BITMAP* startClientButton = CreateImage("assets/images/menu/button.png");
    ALLEGRO_BITMAP* exitButton = CreateImage("assets/images/menu/button.png");
    ALLEGRO_FONT* text = CreateBuiltInFont();

    int firstButton[] = { 300, 150, 200, 60 };
    int secondButton[] = { 300, 300, 200, 60 };
    int thirdButton[] = { 300, 450, 200, 60 };


    al_start_timer(timer);
    while (done == false)
    {
        
        
            al_wait_for_event(queue, &event);

            switch (event.type)
            {
            case ALLEGRO_EVENT_TIMER:
                if (key[ALLEGRO_KEY_ESCAPE]){
                    done = true;


                }

                




                for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;

                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                //when mouse moves

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


                if (mousePressed == false) {
                    mousePressed = true;

                    
                    if (state.x > firstButton[0] && state.x < (firstButton[0] + firstButton[2])) {
                        if (state.y > firstButton[1] && state.y < (firstButton[1] + firstButton[3])) {
                            //start server
                            al_destroy_bitmap(startServerButton);
                            al_destroy_bitmap(startClientButton);
                            al_destroy_bitmap(exitButton);
                            al_destroy_font(text);
                            al_destroy_display(display);
                            al_destroy_timer(timer);
                            al_destroy_event_queue(queue);
                            return 2;
                        }
                    }

                    if (state.x > secondButton[0] && state.x < (secondButton[0] + secondButton[2])) {
                        if (state.y > secondButton[1] && state.y < (secondButton[1] + secondButton[3])) {
                            //start client
                            al_destroy_bitmap(startServerButton);
                            al_destroy_bitmap(startClientButton);
                            al_destroy_bitmap(exitButton);
                            al_destroy_font(text);
                            al_destroy_display(display);
                            al_destroy_timer(timer);
                            al_destroy_event_queue(queue);
                            return 1;
                        }
                    }

                    if (state.x > thirdButton[0] && state.x < (thirdButton[0] + thirdButton[2])) {
                        if (state.y > thirdButton[1] && state.y < (thirdButton[1] + thirdButton[3])) {
                            //exit
                            done = true;
                            

                        }
                    }
                    



                }
                else if (mousePressed) {
                    //do nothing, it's a repeat from the same single click event
                }
            }
           

            if (redraw && al_is_event_queue_empty(queue))
            {
                //300 + 200, horizontal
                //x + 60
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_bitmap(startServerButton, 300, 150, 0);
                al_draw_bitmap(startClientButton, 300, 300, 0);
                al_draw_bitmap(exitButton, 300, 450, 0);
                al_draw_text(text, al_map_rgb(255, 255, 255), 350, 175, 0, "Start Server");
                al_draw_text(text, al_map_rgb(255, 255, 255), 350, 325, 0, "Start Client");
                al_draw_text(text, al_map_rgb(255, 255, 255), 375, 475, 0, "Exit");

                al_flip_display();

                redraw = false;


                


            }

        
        






    }

    al_destroy_bitmap(startServerButton);
    al_destroy_bitmap(startClientButton);
    al_destroy_bitmap(exitButton);
    al_destroy_font(text);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    

    return 0;

}