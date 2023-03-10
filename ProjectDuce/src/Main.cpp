#define KEY_SEEN     1
#define KEY_RELEASED 2
#define PLAYER_ONE 1
#define PLAYER_TWO 2


#include "AllegroHelper.h"
#include "Winsock.h"
#include "library/SoldierManager.h"
#include "library/BulletManager.h"
#include "library/GridManager.h"
#include "library/BuildingManager.h"
#include "library/NetworkManager.h"
#include <string>
#include <iostream>

#include "startMenu/Menu.h"

int main() {

    int clientOrServer = Menu();
    
    if (clientOrServer == 0) {
        exit(1);
    }
    
    
    SOCKET s = NULL;
    SOCKET client = NULL;
    int myPlayer = -1;

    if (clientOrServer == 1) {
        //client
        myPlayer = PLAYER_TWO;
        InitializeWinsock();

        s = CreateSocket();

        ConnectToServer(s, "127.0.0.1", 8080);

        
    }
    else if (clientOrServer == 2) {
        //server
        myPlayer = PLAYER_ONE;
        InitializeWinsock();

        s = CreateSocket();


        BindServer(s, 8080);

        listen(s, 2);

        client =  AcceptConnection(s);
        


    }



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
    bool eKeyPressed = false;
    ALLEGRO_EVENT event;

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    ALLEGRO_MOUSE_STATE state;

    NetworkManager nman = NetworkManager();
    
    GridManager gman = GridManager(0, 0, 10);
    gman.CreateGrid();
    
    BuildingManager buildman = BuildingManager();
    buildman.CreateBase(gman.GetSoldierCoords(5, 1), PLAYER_ONE, 5, 1);
    buildman.CreateBase(gman.GetSoldierCoords(5, 10), PLAYER_TWO, 5, 10);
    
    SoldierManager man = SoldierManager(gman.GetTileWidth(), gman.GetTileHieght(), gman.GetXOffset(), gman.GetYOffset());
    man.CreateSoldier(PLAYER_ONE, gman.GetSoldierCoords(1, 1));
    man.CreateSoldier(PLAYER_TWO, gman.GetSoldierCoords(10, 10));

    

    BulletManager ban = BulletManager(gman.GetTileWidth(), gman.GetTileHieght(), gman.GetXOffset(), gman.GetYOffset());
    
    int playerTurn = PLAYER_ONE;

    
    al_start_timer(timer);
    while (1)
    {

        if (myPlayer == playerTurn) {
            al_wait_for_event(queue, &event);

            switch (event.type)
            {
            case ALLEGRO_EVENT_TIMER:
                if (key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                if (key[ALLEGRO_KEY_E]) {
                    
                    //end turn for now
                    if (eKeyPressed == false) {
                        man.EndTurn();
                        eKeyPressed = true;
                        if (playerTurn == PLAYER_ONE) {
                            playerTurn = PLAYER_TWO;
                        }
                        else {
                            playerTurn = PLAYER_ONE;
                        }

                        if (clientOrServer == 2) {
                            std::cout << "server message sent" << std::endl;
                            int check = SendString(client, "end turn pressed");
                            std::cout << check << std::endl;
                        }
                        else {
                            std::cout << "client message sent" << std::endl;
                            int check = SendString(s, "end turn pressed");
                            std::cout << check << std::endl;
                        }
                    }
                    else {
                        //duplicate from same key down event
                    }
                    
                    
                }

                if (!key[ALLEGRO_KEY_E]) {
                    if (eKeyPressed) {
                        eKeyPressed = false;
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
                    std::vector<int> moveInfo = man.HandleLeftClick(state.x, state.y, gman.GetSoldierCoordsFromMouse(state.x, state.y));

                    if (moveInfo.at(0) != -1) {
                        if (clientOrServer == 2) {
                            //M for move soldier, then which soldier it is in the list(i),  then coord x, then coord y
                            std::string sendMessage = "MX" + std::to_string(moveInfo.at(0)) + "X" + std::to_string(moveInfo.at(1)) + "X" + std::to_string(moveInfo.at(2)) + "X";
                            SendString(client, sendMessage);
                        }
                        else {
                            //M for move soldier, then which soldier it is in the list(i),  then coord x, then coord y
                            std::string sendMessage = "MX" + std::to_string(moveInfo.at(0)) + "X" + std::to_string(moveInfo.at(1)) + "X" + std::to_string(moveInfo.at(2)) + "X";
                            SendString(s, sendMessage);
                        }
                    }

                    buildman.SetPlayerTurn(playerTurn);
                    std::vector<int> coords = buildman.HandleLeftClick(state.x, state.y);
                    
                    if (coords.at(0) == -1) {
                        //null case, don't create soldier
                    }
                    else {
                        coords = man.GetSoldierGridCoords(coords, gman.GetDimension());
                        printf("%d, %d\n", coords.at(0), coords.at(1));
                        man.CreateSoldier(playerTurn, gman.GetSoldierCoords(coords.at(0), coords.at(1)));

                        if (clientOrServer == 2) {
                            //C for create soldier, next is allegiance, then coord x, then coord y
                            std::string sendMessage = "CX" + std::to_string(playerTurn) + "X" + std::to_string(coords.at(0)) + "X" + std::to_string(coords.at(1)) + "X";
                            SendString(client, sendMessage);
                        }
                        else {
                            //C for create soldier, next is allegiance, then coord x, then coord y
                            std::string sendMessage = "CX" + std::to_string(playerTurn) + "X" + std::to_string(coords.at(0)) + "X" + std::to_string(coords.at(1)) + "X";
                            SendString(s, sendMessage);
                        }

                    }

                    
                    
                }
                else if (mousePressed) {
                    //do nothing, it's a repeat from the same single click event
                }
            }
            else if (state.buttons & 2) {
               

                if (mousePressed == false) {
                    mousePressed = true;
                    man.SetPlayerTurn(playerTurn);
                    Bullet newBullet = man.HandleRightClick(state.x, state.y, gman.GetSoldierCoordsFromMouse(state.x, state.y));
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
                gman.Render();
                man.Render();
                std::vector<int> coords = ban.Render();
                buildman.Render();
                
                al_flip_display();

                redraw = false;


                if (coords.at(0) == -1) {
                    //null case, ignore
                }
                else {
                    //figure out what square the bullet hit and hit any
                    //enemy soldiers there
                    //do hit locally
                    coords = gman.GetGridCoords(coords.at(0), coords.at(1));
                    std::vector<int> xyCoords = gman.GetTileCoordsFromGridCoords(coords.at(0), coords.at(1));
        
                    std::vector<int> hitEvent = man.GetSoldierHit(playerTurn, xyCoords);


                    //do hit across network
                    if (clientOrServer == 2) {
                        //H is for hit, as a bullet struck a square, turn is to tell who it should hurt(not current turn player), then it's grid x coord, then it's grid y coord
                        std::string sendMessage = "HX" + std::to_string(playerTurn) + "X" + std::to_string(coords.at(0)) + "X" + std::to_string(coords.at(1)) + "X";
                        SendString(client, sendMessage);
                    }
                    else {
                        //H is for hit, as a bullet struck a square, turn is to tell who it should hurt(not current turn player), then it's grid x coord, then it's grid y coord
                        std::string sendMessage = "HX" + std::to_string(playerTurn) + "X" + std::to_string(coords.at(0)) + "X" + std::to_string(coords.at(1)) + "X";
                        SendString(s, sendMessage);
                    }

                }


            }

        }
        else {
            if (redraw && al_is_event_queue_empty(queue))
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                gman.Render();
                man.Render();
                ban.Render();
                buildman.Render();
                
                al_flip_display();

                redraw = false;
            }

            //wait for message from other
            std::string message = "";
            
            if (clientOrServer == 2) {
                while (message != "end turn pressed") {
                    message = ReceiveString(client); //this should be blocking
                    if (message != "ERROR" && message != "end turn pressed") {
                        std::cout << message << std::endl;
                        
                        man.SetPlayerTurn(playerTurn);
                        std::vector<int> command = nman.InterperetNetworkMessage(message, man, gman, buildman);
                        
                        if (command.at(0) ==  -1) {
                            if (playerTurn == PLAYER_ONE) {
                                std::cout << "Player one wins!" << std::endl;
                            }
                            else {
                                std::cout << "Player two wins!" << std::endl;
                            }
                        }
                        else if (command.at(0) == -2) {
                            //send soldier kill command across network
                            //K for kill, then player soldier belonged to(allegiance), then index of soldier in list
                            std::string sendMessage = "KX" + std::to_string(command.at(0)) + "X" + std::to_string(command.at(1)) + "X";
                            if (clientOrServer == 2) {
                                
                                
                                SendString(client, sendMessage);
                            }
                            else {
                                
                                SendString(s, sendMessage);
                            }
                        }

                    }
                }
                
            }
            else {
                while (message != "end turn pressed") {
                    message = ReceiveString(s); //this should be blocking
                    if (message != "ERROR" && message != "end turn pressed") {
                        std::cout << message << std::endl;
                        
                        man.SetPlayerTurn(playerTurn);
                        std::vector<int> command = nman.InterperetNetworkMessage(message, man, gman, buildman);

                        if (command.at(0) == -1) {
                            if (playerTurn == PLAYER_ONE) {
                                std::cout << "Player one wins!" << std::endl;
                            }
                            else {
                                std::cout << "Player two wins!" << std::endl;
                            }
                        }
                        else if (command.at(0) == -2) {
                            //send soldier kill command across network
                            //K for kill, then player soldier belonged to(allegiance), then index of soldier in list
                            std::string sendMessage = "KX" + std::to_string(command.at(0)) + "X" + std::to_string(command.at(1)) + "X";
                            if (clientOrServer == 2) {


                                SendString(client, sendMessage);
                            }
                            else {

                                SendString(s, sendMessage);
                            }
                        }
                    }
                }

                
            }
            
            std::cout << message << std::endl;
            //if we got message it means player turn changed
            if (playerTurn == PLAYER_ONE) {
                playerTurn = PLAYER_TWO;
            }
            else {
                playerTurn = PLAYER_ONE;
            }

        }
        
        

        

        
    }

    
    man.Destroy();
    ban.Destroy();
    gman.Destroy();
    buildman.Destroy();
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    if (clientOrServer == 2) {
        closesocket(s);
        WSACleanup();
    }

	return 0;

}