#pragma once

#define ERROR -1
#define SUCCESS 1

#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>


int InitializeAllegro();

int InstallKeyboard();

ALLEGRO_TIMER* CreateTimer(double firstTime, double secondTime);

ALLEGRO_EVENT_QUEUE* CreateQueue();

ALLEGRO_DISPLAY* CreateDiplay(int screenWidth, int screenHieght);

ALLEGRO_FONT* CreateBuiltInFont();

void RegisterEventSources(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer);