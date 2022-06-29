// testallegrotext.c

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#define MAX_IN  20
#define SEXIT   "q"

#define BLACK al_map_rgb(0, 0, 0)
#define WHITE al_map_rgb(255, 255, 255)
#define RED al_map_rgb(255, 0, 0)
#define BLUE al_map_rgb(0, 0, 255)
#define GREEN al_map_rgb(0, 255, 0)

#define RESOURCES_DIR "resources"
#define TEST_TEXT "Hello World"
#define NORMAL_TEXT  "Normal Text"
#define INVERTED_TEXT "Inverted Text"
#define STRIKE_THRU_TEXT "Strike Thru Text"
#define UNDER_LINE_TEXT  "Under Line Text"
#define BLINKING_TEXT   "Blinking Text"
//#define FONT_FILE "YARDSALE.TTF"
#define FONT_FILE "UbuntuMono-R.ttf"
#define FONT_SIZE 18
#define LINE_WIDTH  1
#define DROP    2

// Normal
#define NX  20
#define NY  20
#define YSPACE  40

// Inverted
#define IX  NX
#define IY  NY+YSPACE

// Strike thru
#define SX  NX
#define SY  IY+YSPACE

// Under-line
#define UX  NX
#define UY  SY+YSPACE

// Blinking
#define BX  NX
#define BY  UY+YSPACE



int main()  {
    
    int toggle=1;
    bool running = true;
    int bbx;
    int bby;
    int bbw;
    int bbh;
    char in[MAX_IN];

    ALLEGRO_DISPLAY *display;
    ALLEGRO_FONT *font;

    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, RESOURCES_DIR);
    al_change_directory(al_path_cstr(path, '/'));
    al_destroy_path(path);

    display = al_create_display(640, 480);
    
    font = al_load_ttf_font(FONT_FILE, FONT_SIZE, 0);

    while (running) {

        al_clear_to_color(BLACK);
        
        //al_draw_line(0, 0, al_get_display_width(display), al_get_display_height(display), RED, 5.0);
        //al_draw_rectangle(100, 100, 300, 300, GREEN, 1);
        //al_draw_ellipse(300, 300, 120, 50, al_map_rgb(0, 0, 255), 3);
        //al_draw_spline(points, al_map_rgb(128, 128, 0), 8);
        //al_draw_polygon(polygon, 8, ALLEGRO_LINE_JOIN_BEVEL, al_map_rgb(255, 15, 15),3,1);
        //al_draw_filled_polygon(polygon, 8, al_map_rgb(255, 0, 0));

        //al_get_text_dimensions(font, TEST_TEXT, &bbx, &bby, &bbw, &bbh);

        //printf("bbx=%d, bby=%d, bbw=%d, bbh=%d\n", bbx, bby, bbw, bbh);
        //al_draw_rectangle(bbx, bby, bbx+bbw, bby+bbh, GREEN, 1);

        // Normal
        al_draw_text(font, WHITE, NX, NY, 0, NORMAL_TEXT);

        // Inverted
        al_get_text_dimensions(font, INVERTED_TEXT, &bbx, &bby, &bbw, &bbh);
        al_draw_filled_rectangle(IX+bbx, IY+bby-DROP, IX+bbx+bbw, IY+bby+bbh+DROP, WHITE);
        al_draw_text(font, BLACK, IX, IY, 0, INVERTED_TEXT);

        // Strike thru
        al_get_text_dimensions(font, STRIKE_THRU_TEXT, &bbx, &bby, &bbw, &bbh);
        al_draw_text(font, WHITE, SX, SY, 0, STRIKE_THRU_TEXT);
        al_draw_line(SX+bbx, SY+bby+(bbh/2)+DROP, SX+bbx+bbw, SY+bby+(bbh/2)+DROP, WHITE, LINE_WIDTH);

        // Under-line
        al_get_text_dimensions(font, UNDER_LINE_TEXT, &bbx, &bby, &bbw, &bbh);
        al_draw_text(font, WHITE, UX, UY, 0, UNDER_LINE_TEXT);
        al_draw_line(UX+bbx, UY+bby+bbh+DROP, UX+bbx+bbw, UY+bby+bbh+DROP, WHITE, LINE_WIDTH);        

        // blinking
        if (toggle) {
            al_draw_text(font, WHITE, BX, BY, 0, TEST_TEXT);
            toggle=0;
        }
        else {
            al_draw_text(font, BLACK, BX, BY, 0, TEST_TEXT);
            toggle=1;
        }
        
        al_flip_display();
        
        // 2 Hz rate
        usleep(250*1000);

        #if 0
            if(fgets(in, sizeof(in), stdin) > 0){
                if (strcmp(SEXIT, in) == 0) {
                    // quit
                    al_destroy_font(font);
                    al_destroy_display(display);
                    return 0;
                }
            }
        #endif

    }
}

