#define KEY_SEEN     1
#define KEY_RELEASED 2
#define PLAYER_ONE 1
#define PLAYER_TWO 2


#include "AllegroHelper.h"
#include "Winsock.h"
#include "library/SoldierManager.h"
#include "library/BulletManager.h"


int main() {


	InitializeAllegro();
    
    InitializeImageAddon();

	InstallKeyboard();

    al_install_mouse();

	ALLEGRO_TIMER* timer = CreateTimer(1.0, 30.0);

	ALLEGRO_EVENT_QUEUE* queue =  CreateQueue();

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

    

    
    SoldierManager man = SoldierManager();
    man.CreateSoldier(PLAYER_ONE, 0, 0);
    man.CreateSoldier(PLAYER_TWO, 400, 400);

    BulletManager ban = BulletManager();
    
    int playerTurn = PLAYER_ONE;

    al_start_timer(timer);
    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (key[ALLEGRO_KEY_ESCAPE])
                done = true;

            if (key[ALLEGRO_KEY_E]) {
                //end turn for now
                if (playerTurn == PLAYER_ONE) {
                    playerTurn = PLAYER_TWO;
                }
                else {
                    playerTurn = PLAYER_ONE;
                }
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
                man.SetPlayerTurn(playerTurn);
                man.HandleLeftClick(state.x, state.y);
            }
            else if (mousePressed) {
                //do nothing, it's a repeat from the same single click event
            }
        }
        else if (state.buttons & 2) {
            printf("mouse 2 is down\n");    //trackpad not working, may need mouse

            if (mousePressed == false) {
                mousePressed = true;
                man.SetPlayerTurn(playerTurn);
                Bullet newBullet = man.HandleRightClick(state.x, state.y);
                if (newBullet.GetIsNull()) {
                    //no new bullet was returned
                }
                else {
                    ban.AddBullet(newBullet);
                }
            }
            else if (mousePressed) {
                //do nothing, it's a repeat from the same single click event
            }

        }
        else {
            //printf("mouse is up\n");
            if (mousePressed) {
                mousePressed = false;
            }
            else if (mousePressed == false) {
                //do nothing, it's a repeat from the up event
            }
        }
        

        

        if (redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            man.Render();
            ban.Render();
            al_flip_display();

            redraw = false;
        }
    }

    
    man.Destroy();
    ban.Destroy();
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

	return 0;

}