#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#define LARGURA_TELA 800
#define ALTURA_TELA 600
// funções

int main(void){
// iniciando
al_init();
al_init_image_addon();
al_install_keyboard();
al_install_mouse();

// variaveis
ALLEGRO_BITMAP *imagem = NULL;
ALLEGRO_DISPLAY *janela = NULL;
bool fim = false;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

// display FULLSCREEN
ALLEGRO_MONITOR_INFO info;
int res_x_comp, res_y_comp;
al_get_monitor_info(0,&info);
res_x_comp=info.x2 - info.x1;
res_y_comp = info.y2 - info.y1;
al_set_new_display_flags(ALLEGRO_FULLSCREEN);
janela = al_create_display(LARGURA_TELA,ALTURA_TELA);
if (!janela)
{
    al_show_native_message_box(NULL,"aviso!", "ERRO", "ERRO AO CRIAR O DISPLAY!",NULL,ALLEGRO_MESSAGEBOX_ERROR);
    return -1;
}
    float red_x= res_x_comp / (float) LARGURA_TELA;
    float red_y= res_y_comp / (float) ALTURA_TELA;
    ALLEGRO_TRANSFORM transformar;
    al_identity_transform(&transformar);
    al_scale_transform(&transformar,red_x,red_y);
    al_use_transform(&transformar);

// filas
fila_eventos = al_create_event_queue();

//SOURCES
al_register_event_source(fila_eventos, al_get_keyboard_event_source());

// codigo
    imagem = al_load_bitmap("MENU APAGADO.png");
    al_set_new_display_flags (ALLEGRO_FULLSCREEN_WINDOW);
    janela = al_create_display(res_x_comp,res_y_comp );

    al_flip_display();
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap_region(imagem,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
    al_flip_display();

while(!fim){
    ALLEGRO_EVENT evento_atual;
    al_wait_for_event(fila_eventos, &evento_atual);
    if (evento_atual.type==ALLEGRO_EVENT_KEY_DOWN)
    {
        if (evento_atual.keyboard.keycode==ALLEGRO_KEY_ESCAPE){
            fim=true;
        }

    }

}
// Finaliza a janela
al_destroy_display(janela);
al_destroy_event_queue(fila_eventos);
    return 0;
}
