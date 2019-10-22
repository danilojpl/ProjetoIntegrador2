#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#define FPS 60.0
#define LARGURA_TELA 800
#define ALTURA_TELA 600
const int fps = 60;
// structs
int main(void){
// iniciando
al_init_font_addon();
al_init_ttf_addon();
al_init();
al_init_image_addon();
al_install_keyboard();
al_install_mouse();
al_init_primitives_addon ();
al_install_audio();
al_init_acodec_addon();

// variaveis
ALLEGRO_FONT *fonte = NULL;
int posx=50, dir_x=5;
int posy=100, dir_y=5;
int desenha = 1;
bool start=false;
ALLEGRO_AUDIO_STREAM *musica = NULL;
ALLEGRO_BITMAP *botao=NULL;
ALLEGRO_BITMAP *botaoA=NULL;
ALLEGRO_BITMAP *nave = NULL;
ALLEGRO_BITMAP *espaco = NULL;
al_reserve_samples(5);
ALLEGRO_BITMAP *imagem = NULL;
ALLEGRO_DISPLAY *janela = NULL;
bool fim = false;
ALLEGRO_TIMER *timer = NULL;
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
    timer = al_create_timer(1.0/fps);

//SOURCES
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos,al_get_mouse_event_source());
    al_register_event_source(fila_eventos,al_get_timer_event_source(timer));


// codigo
//audio
    musica = al_load_audio_stream("BeepBox-Song.wav", 4, 1024);
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);
//texto
    fonte = al_load_font("space age.ttf", 41, 0);

//imagem
    espaco= al_load_bitmap("primeira1.png");
    botao= al_load_bitmap("aceso.png");
    botaoA= al_load_bitmap("apagado.png");
    nave = al_load_bitmap("ship2.png");
    imagem = al_load_bitmap("menuteste2.bmp");
    al_set_new_display_flags (ALLEGRO_FULLSCREEN_WINDOW);
    janela = al_create_display(res_x_comp,res_y_comp);

al_clear_to_color(al_map_rgb(255, 255, 255));
al_draw_bitmap_region(imagem,0,0,res_x_comp,res_y_comp,0,0,0);

al_start_timer(timer);
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
    if (start==false){
        if (evento_atual.type == ALLEGRO_EVENT_MOUSE_AXES){
                // Verificamos se ele está sobre o botao
                al_set_target_bitmap(al_get_backbuffer(janela));
               if (evento_atual.mouse.x >= LARGURA_TELA/2- al_get_bitmap_width(botao) / 2 &&
                evento_atual.mouse.x <= LARGURA_TELA/2 + al_get_bitmap_width(botao) / 2 &&
                evento_atual.mouse.y >= ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2 &&
                evento_atual.mouse.y <= ALTURA_TELA/2 + al_get_bitmap_height(botao) / 2){
                    al_draw_bitmap(botao,LARGURA_TELA/2-al_get_bitmap_width(botao) / 2,ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2 ,0);

                }
                else{
                    al_draw_bitmap(botaoA,LARGURA_TELA/2-al_get_bitmap_width(botao) / 2,ALTURA_TELA/2 - al_get_bitmap_height(botao)/ 2 ,al_get_backbuffer);
                }

    }

    else if (evento_atual.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
                if (evento_atual.mouse.x >= LARGURA_TELA/2- al_get_bitmap_width(botao) / 2 &&
                evento_atual.mouse.x <= LARGURA_TELA/2 + al_get_bitmap_width(botao) / 2 &&
                evento_atual.mouse.y >= ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2 &&
                evento_atual.mouse.y <= ALTURA_TELA/2 + al_get_bitmap_height(botao) / 2){
                start = true;
                al_set_audio_stream_playing(musica,0);

                }
            }
    al_draw_text(fonte, al_map_rgb(0, 0, 0),LARGURA_TELA/2- al_get_bitmap_width(botao) / 2,ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2, 0, "Start");
    }
    else
        {
        al_clear_to_color(al_map_rgb(0, 0, 0));
         if (evento_atual.type==ALLEGRO_EVENT_KEY_DOWN){
            switch (evento_atual.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                posy -= 10;
                break;
            case ALLEGRO_KEY_DOWN:
                posy +=10;
                break;
            case ALLEGRO_KEY_RIGHT:
                posx +=10;
                break;
            case ALLEGRO_KEY_LEFT:
                posx -= 10;
                break;
            }
        }
    al_draw_bitmap (nave,posx,posy,0);

    }

      al_flip_display();

}

// Finaliza a janela
//al_destroy_bitmap(buffered);
al_destroy_audio_stream(musica);
al_destroy_display(janela);
al_destroy_event_queue(fila_eventos);
al_destroy_bitmap(imagem);
al_destroy_bitmap(botao);
    return 0;

}

