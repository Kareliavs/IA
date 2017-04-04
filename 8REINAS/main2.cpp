#include <stdio.h>
#include <iostream>
#include <vector>

#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
/*g++ -std=c++11  main2.cpp -o ale `pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`
*/
using namespace std;
int kiwi=0,tab=0;
const float FPS = 60;
const int SCREEN_W = 600;
const int SCREEN_WP = 800;
const int SCREEN_H = 600;
const int BOUNCER_SIZE = 20;
vector<pair<float,float> >coordenadas;
vector<vector<int>>reinas;
int num_reinas=0;
#include "8.cpp"
int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_BITMAP  *image   = NULL;
   ALLEGRO_BITMAP  *queen   = NULL;
   ALLEGRO_BITMAP  *queen2   = NULL;
   ALLEGRO_BITMAP  *win   = NULL;
   ALLEGRO_BITMAP  *gameover   = NULL;
   ALLEGRO_BITMAP  *tryagain  = NULL;
   ALLEGRO_BITMAP  *help   = NULL;
   ALLEGRO_BITMAP  *tablero   = NULL;
   ALLEGRO_BITMAP  *exit   = NULL;
   ALLEGRO_BITMAP  *fondo  = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP *bouncer = NULL;
   float bouncer_x = SCREEN_WP / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
   bool redraw = true;
   
////INICIALIZAR MATRIZ
vector<int>k;
for(int i=0; i<8;i++)
	k.push_back(0);
for(int i=0; i<8;i++)
	reinas.push_back(k);
		

 ///ERRORES
   if(!al_init()) {
      fprintf(stderr, "fallo inicializacion de allegro\n");
      return -1;
   }
 
    if(!al_init_image_addon()) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }

   if(!al_install_mouse()) {
      fprintf(stderr, "fallo inicializacion de  mouse!\n");
      return -1;
   }

   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "fallo inicializacion de timer!\n");
      return -1;
   }
 
   display = al_create_display(SCREEN_WP, SCREEN_H);
   if(!display) {
      fprintf(stderr, "fallo creación de display!\n");
      al_destroy_timer(timer);
      return -1;
   }
 
   bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   if(!bouncer) {
      fprintf(stderr, "fallo crear bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
   image = al_load_bitmap("image.png");
   queen = al_load_bitmap("queen.png");
   queen2 = al_load_bitmap("queen2.png");
   win = al_load_bitmap("win.png");
   gameover = al_load_bitmap("gameover.png");
   tryagain = al_load_bitmap("tryagain.png");
   help = al_load_bitmap("help.png");
   tablero= al_load_bitmap("tablero.png");
   exit = al_load_bitmap("exit.png");
   fondo = al_load_bitmap("fondo.jpg");

   if(!image) {
      al_show_native_message_box(display, "Error", "Error", "Failed to load image!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(display);
      return 0;
   }
   if(!queen) {
      al_show_native_message_box(display, "Error", "Error", "Failed to load queen!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(display);
      return 0;
   }
   if(!queen2 or !win or !gameover or !tryagain or !help or !exit or !fondo or !tablero) {
      al_show_native_message_box(display, "Error", "Error", "Failed to load resources!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(display);
      return 0;
   }
   al_flip_display();
   //al_rest(2);

   //al_set_target_bitmap(bouncer);
 
   al_clear_to_color(al_map_rgb(255, 0, 255));
 
   al_set_target_bitmap(al_get_backbuffer(display));
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(bouncer);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));

   al_register_event_source(event_queue, al_get_mouse_event_source());

   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_start_timer(timer);
 
   while(1)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) 
      {
         redraw = true;
	
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
              ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

         bouncer_x = ev.mouse.x;
         bouncer_y = ev.mouse.y;
      }
      else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) 
	{
	 
	  
	  //cout<<"dibujo reina"<<bouncer_x<<" "<<bouncer_y<<endl;
	  if(bouncer_x<=600)
          {    
		  if(reinas[(int)bouncer_x/(int)(SCREEN_W/8)][(int)bouncer_y/(int)(SCREEN_W/8)]==0)
		  {
			for(int i=0; i<8;i++)
			{
				for(int j=0; j<8;j++)
				{  //cout<<"see: "<<j<<"-"<<(int)bouncer_x/(int)(SCREEN_W/8)<<"+"<<i<<"-"<<(int)bouncer_y/(int)(SCREEN_W/8)<<endl;
					if(j==(int)bouncer_x/(int)(SCREEN_W/8) or i==(int)bouncer_y/(int)(SCREEN_W/8) or j-(int)bouncer_x/(int)(SCREEN_W/8)==i-(int)bouncer_y/(int)(SCREEN_W/8) or j-(int)bouncer_x/(int)(SCREEN_W/8)+i+7-(int)bouncer_y/(int)(SCREEN_W/8)==7) 
						reinas[j][i]=2;
				}
			}
			reinas[(int)bouncer_x/(int)(SCREEN_W/8)][(int)bouncer_y/(int)(SCREEN_W/8)]=1;
			num_reinas++;
		  
			/*for(int i=0; i<8;i++)
			{
				for(int j=0; j<8;j++)
					cout<<" "<<reinas[j][i];
				cout<<endl;	
			} */
		}       
	}  
	

	else if(bouncer_x>650 and bouncer_x<750 and bouncer_y>300 and bouncer_y<400)////HELP
		{ 
		  reinas.clear();
			for(int i=0; i<8;i++)
		  		reinas.push_back(k);
			
			num_reinas=0;
			ocho_reinas();
			
		  /*if(kiwi==0)
		  	ocho_reinas();
		  reinas=para_graficar[kiwi];
		  if(kiwi<91)		 
			kiwi++;*/
		  tab=1;
		}
	else if(bouncer_x>600 and bouncer_x<800 and bouncer_y>400 and bouncer_y<600 and tab==1)////HELP
		{ 
		  reinas.clear();
			for(int i=0; i<8;i++)
		  		reinas.push_back(k);
			
			num_reinas=0;
		  if((int)(bouncer_x-600)/20+(int)(bouncer_y-400)/20*10<92)
		 	 reinas=para_graficar[(int)(bouncer_x-600)/20+(int)(bouncer_y-400)/20*10];
		  cout<<"Solución: "<<(int)(bouncer_x-600)/20+(int)(bouncer_y-400)/20*10+1<<endl;
		  
		  tab=1;
		}

        else if(bouncer_x>650 and bouncer_x<750 and bouncer_y>180 and bouncer_y<280)///TRYAGAIN
 		{
			reinas.clear();
			for(int i=0; i<8;i++)
		  		reinas.push_back(k);
			
			num_reinas=0;	
			tab=0;			
		}
	else if(bouncer_x>650 and bouncer_x<750 and bouncer_y>10 and bouncer_y<160)///EXIT
         	break;
	
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
 
         al_clear_to_color(al_map_rgb(0,0,0));
	 al_draw_bitmap(fondo,0,0,0);	
 	 al_draw_scaled_bitmap(image,0,0,258,258,0,0,SCREEN_W,SCREEN_H,0);
	 
	int espacios_vacios=0;
	 for(int i=0; i<8;i++)
	{
		for(int j=0; j<8;j++)
		{
			if(reinas[i][j]==1)
			{
				al_draw_scaled_bitmap(queen,0,0,256,256,(SCREEN_W/8)*i+5,(SCREEN_W/8)*j+5,(int)(SCREEN_W/8-10),(int)(SCREEN_W/8-10),0);
			}
			else if(reinas[i][j]==2)
			{
				al_draw_scaled_bitmap(queen2,0,0,256,256,(SCREEN_W/8)*i+5,(SCREEN_W/8)*j+5,(int)(SCREEN_W/8-10),(int)(SCREEN_W/8-10),0);
			}	
			else
				espacios_vacios++;
		}	
	} 
	if(num_reinas==8)	
	{ 
	  al_draw_bitmap(win,50,200,0);	
		  //cout<<"usted gano"<<endl;
	}
	if(espacios_vacios==0 and num_reinas!=8)
	{ 
	  al_draw_bitmap(gameover,50,200,0);
	  //cout<<"usted perdió"<<endl;
	}
	 al_draw_scaled_bitmap(tryagain,0,0,889,889,650,180,100,100,0);
	 al_draw_scaled_bitmap(help,0,0,256,256,650,300,100,100,0);
	 if (tab==1)al_draw_scaled_bitmap(tablero,0,0,324,338,600,400,200,200,0);
	 al_draw_scaled_bitmap(exit,0,0,400,567,650,10,100,150,0);
         al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
 
         al_flip_display();
      }
   }
   //al_rest(2);
   al_destroy_bitmap(bouncer);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_bitmap(image);
   al_destroy_bitmap(queen);
   al_destroy_bitmap(queen2);
   al_destroy_bitmap(win);
   al_destroy_bitmap(gameover);
   al_destroy_bitmap(tryagain);
   al_destroy_bitmap(help);
   al_destroy_bitmap(tablero);
   al_destroy_bitmap(exit);
   al_destroy_bitmap(fondo);	
   al_destroy_event_queue(event_queue);
 
   return 0;
}
