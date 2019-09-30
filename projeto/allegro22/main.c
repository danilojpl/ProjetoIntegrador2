#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#define LARGURA_TELA 800
#define ALTURA_TELA 600
// funções
struct NaveEspacial
{
 int x;
 int y;
 int vidas;
 int velocidade;
 int borda_x;
 int borda_y;
 int pontos;

};
/*void initNave (NaveEspacial (&nave)){
    nave.x=20;
    nave.y=altura_t/2;
    nave.velocidade=7;
    nave.borda_x=6;
    nave.borda_y=7;
    nave.pontos=0;

} */

int main(void){
// iniciando
al_init();
al_init_image_addon();
al_install_keyboard();
al_install_mouse();
al_init_primitives_addon ();
al_install_audio();
al_init_acodec_addon();
//NaveEspacial nave;

// variaveis
bool start=false;
ALLEGRO_AUDIO_STREAM *musica = NULL;
ALLEGRO_BITMAP *botao=NULL;
ALLEGRO_BITMAP *botaoA=NULL;
botao= al_load_bitmap("acesso.png");
botaoA= al_load_bitmap("apagado.png");
al_reserve_samples(5);
ALLEGRO_FONT *fonte = NULL;
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
    al_register_event_source(fila_eventos,al_get_mouse_event_source());
// codigo
    musica = al_load_audio_stream("BeepBox-Song.wav", 4, 1024);
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);
    fonte = al_load_font("arial.ttf", 48, 0);

    imagem = al_load_bitmap("menuteste2.bmp");
    al_set_new_display_flags (ALLEGRO_FULLSCREEN_WINDOW);
    janela = al_create_display(res_x_comp,res_y_comp);

    //funções iniciais

   // initNave(nave);

    al_clear_to_color(al_map_rgb(255, 255, 255));
   al_draw_bitmap_region(imagem,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);


while(!fim){



    ALLEGRO_EVENT evento_atual;
    al_wait_for_event(fila_eventos, &evento_atual);
    if (evento_atual.type==ALLEGRO_EVENT_KEY_DOWN)
    {
        if (evento_atual.keyboard.keycode==ALLEGRO_KEY_ESCAPE){
            fim=true;
        }

    }
    // menu game
    else if (evento_atual.type == ALLEGRO_EVENT_MOUSE_AXES){

                // Verificamos se ele está sobre a região do retângulo central
               if (evento_atual.mouse.x >= LARGURA_TELA/2- al_get_bitmap_width(botao) / 2 &&
                evento_atual.mouse.x <= LARGURA_TELA/2 + al_get_bitmap_width(botao) / 2 &&
                evento_atual.mouse.y >= ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2 &&
                evento_atual.mouse.y <= ALTURA_TELA/2 + al_get_bitmap_height(botao) / 2){
                    al_draw_bitmap(botao,LARGURA_TELA/2-al_get_bitmap_width(botao) / 2,ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2 ,0);
                }
                else{
                    al_draw_bitmap(botaoA,LARGURA_TELA/2-al_get_bitmap_width(botao) / 2,ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2 ,0);
                }

    }
    else if (evento_atual.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
                if (evento_atual.mouse.x >= LARGURA_TELA/2- al_get_bitmap_width(botao) / 2 &&
                evento_atual.mouse.x <= LARGURA_TELA/2 + al_get_bitmap_width(botao) / 2 &&
                evento_atual.mouse.y >= ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2 &&
                evento_atual.mouse.y <= ALTURA_TELA/2 + al_get_bitmap_height(botao) / 2){
                     al_clear_to_color(al_map_rgb(255, 255, 255));
                    al_destroy_audio_stream(musica);
                    al_destroy_bitmap(imagem);
                    al_destroy_bitmap(botao);
                    al_destroy_bitmap(botaoA);
                }
            }


      al_flip_display();

}



// Finaliza a janela
al_destroy_audio_stream(musica);
al_destroy_display(janela);
al_destroy_event_queue(fila_eventos);
al_destroy_bitmap(imagem);
al_destroy_bitmap(botao);
    return 0;

}
