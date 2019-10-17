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
#include "objeto.h"
#define LARGURA_TELA 800
#define ALTURA_TELA 600
#include <ctime>
//variaveis globais
ALLEGRO_BITMAP *inimigo = NULL;
ALLEGRO_BITMAP *fase1 = NULL;
ALLEGRO_BITMAP *bala = NULL;
ALLEGRO_BITMAP *naveE = NULL;
const int numCometas =10;
const int fps = 60;
const int numBalas =5;
enum teclas {cima,baixo,esquerda,direita,espaco};
// structs
void Initnave(naveEspacial &nave);
void desenhanave (naveEspacial &nave);
void MoveNaveCima (naveEspacial &nave);
void MoveNaveBaixo (naveEspacial &nave);
void MoveNaveDireita (naveEspacial &nave);
void MoveNaveEsquerda (naveEspacial &nave);

void initBalas (projeteis balas[],int tamanho);
void atiraBalas (projeteis balas[], int tamanho, naveEspacial nave );
void atualizaBalas (projeteis balas[], int tamanho);
void desenhaBalas (projeteis balas[], int tamanho);

void initCometas (cometas cometa [],int tamanho);
void spawnCometas (cometas cometa [],int tamanho);
void atualizarCometas (cometas cometa [],int tamanho,naveEspacial &nave);
void desenhaCometas (cometas cometa [],int tamanho);

void initFase(fase &space);
void desenhafase(fase &space);
int main(void){
// iniciando
    cometas cometa[numCometas];
    fase space;
    naveEspacial nave;
    projeteis balas [numBalas];
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
    //ALLEGRO_BITMAP *fase1 = NULL;
    bool teclas []={false,false,false,false,false};
    ALLEGRO_FONT *fonte = NULL;
    bool desenha = true;
    bool start=false;
    ALLEGRO_AUDIO_STREAM *musica = NULL;
    //ALLEGRO_BITMAP *bala = NULL;
    ALLEGRO_BITMAP *botao=NULL;
    ALLEGRO_BITMAP *botaoA=NULL;
   //ALLEGRO_BITMAP *espacof = NULL;
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
    srand(time(NULL));
    initCometas(cometa,numCometas);
    initFase(space);
    Initnave(nave);
    initBalas(balas,numBalas);
//audio
    musica = al_load_audio_stream("BeepBox-Song.wav", 4, 1024);
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);
//texto
    fonte = al_load_font("space age.ttf", 41, 0);

//imagem
    inimigo =al_load_bitmap("boarder.png");
    fase1 = al_load_bitmap("primeira1.png");
    bala = al_load_bitmap("shot2.png");
    //espacof= al_load_bitmap("primeira1.png");
    botao= al_load_bitmap("aceso.png");
    botaoA= al_load_bitmap("apagado.png");
    naveE = al_load_bitmap("ship2.png");
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
                evento_atual.mouse.y <= ALTURA_TELA/2 + al_get_bitmap_height(botao) / 2)
                {
                    al_draw_bitmap(botao,LARGURA_TELA/2-al_get_bitmap_width(botao) / 2,ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2 ,0);
                }
                else
                {
                    al_draw_bitmap(botaoA,LARGURA_TELA/2-al_get_bitmap_width(botao) / 2,ALTURA_TELA/2 - al_get_bitmap_height(botao)/ 2 ,0);
                }
        }

        else if (evento_atual.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
                if (evento_atual.mouse.x >= LARGURA_TELA/2- al_get_bitmap_width(botao) / 2 &&
                evento_atual.mouse.x <= LARGURA_TELA/2 + al_get_bitmap_width(botao) / 2 &&
                evento_atual.mouse.y >= ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2 &&
                evento_atual.mouse.y <= ALTURA_TELA/2 + al_get_bitmap_height(botao) / 2)
                {
                start = true;
                al_set_audio_stream_playing(musica,0);

                }
        }
    al_draw_text(fonte, al_map_rgb(0, 0, 0),LARGURA_TELA/2- al_get_bitmap_width(botao) / 2,ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2, 0, "Start");
    al_flip_display();
    }
    else{
        if (evento_atual.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (evento_atual.keyboard.keycode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    fim =true;
                    break;
                case ALLEGRO_KEY_UP:
                    teclas [cima]=true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    teclas [baixo]=true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    teclas [direita] =true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    teclas [esquerda] = true;
                    break;
                case ALLEGRO_KEY_SPACE:
                    teclas [espaco]=true;
                    atiraBalas(balas,numBalas,nave);
                    break;
            }
        }
        else if (evento_atual.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch (evento_atual.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                    teclas [cima]=false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    teclas [baixo]=false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    teclas [direita] =false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    teclas [esquerda] = false;
                    break;

            }
        }
        else if (evento_atual.type == ALLEGRO_EVENT_TIMER)
        {
            desenha = true;
        if (teclas[esquerda])
            MoveNaveEsquerda(nave);
        if (teclas[cima])
            MoveNaveCima (nave);
        if (teclas[baixo])
            MoveNaveBaixo (nave);
        if (teclas[direita])
            MoveNaveDireita(nave);
        if (teclas[espaco])
            atualizaBalas(balas,numBalas);
        al_clear_to_color(al_map_rgb(0, 0, 0));

        spawnCometas(cometa,numCometas);
        atualizarCometas(cometa,numCometas,nave);
      //  desenhafase(space);
       if (desenha && al_is_event_queue_empty(fila_eventos))
        {

            desenha = false;
             desenhanave(nave);
             desenhaBalas(balas,numBalas);
             desenhaCometas(cometa,numCometas);
            al_flip_display();
            al_clear_to_color (al_map_rgb(0,0,0));
        }
    }
    }

    }

// Finaliza a janela
//al_destroy_bitmap(buffered);
al_destroy_audio_stream(musica);
al_destroy_display(janela);
al_destroy_event_queue(fila_eventos);
al_destroy_bitmap(imagem);
al_destroy_bitmap(botao);
al_destroy_timer(timer);
    return 0;

}
void Initnave(naveEspacial &nave)
{
    nave.x=20;
    nave.y=ALTURA_TELA/2;
    nave.id=jogador;
    nave.vidas =3;
    nave.velocidade=7;
    nave.borda_x=6;
    nave.borda_y=7;
    nave.pontos = 0;

}
void desenhanave (naveEspacial &nave)
{
   al_draw_bitmap (naveE,nave.x,nave.y,0);
}
void MoveNaveCima (naveEspacial &nave)
{
  nave.y -= nave.velocidade;
  if (nave.y<0)
    nave.y = 0;

}
void MoveNaveBaixo (naveEspacial &nave)
{
    nave.y+= nave.velocidade;
    if (nave.y>ALTURA_TELA)
        nave.y=ALTURA_TELA;

}
void MoveNaveDireita (naveEspacial &nave)
{
    nave.x += nave.velocidade;
    if (nave.x> LARGURA_TELA/2)
        nave.x= LARGURA_TELA/2;

}
void MoveNaveEsquerda (naveEspacial &nave)
{
    nave.x -= nave.velocidade;
    if (nave.x <0)
        nave.x =0;

}

void initBalas (projeteis balas[],int tamanho)
{
    for (int i=0;i<tamanho;i++){
        balas[i].id= projetil;
        balas[i].velocidade = 10;
        balas [i].ativo=false;

    }
}
void atiraBalas (projeteis balas[], int tamanho, naveEspacial nave )
{
    for (int i=0;i<tamanho;i++){
        if (!balas[i].ativo){
            balas[i].x = nave.x+24;
            balas[i].y = nave.y+9;
            balas[i].ativo=true;
            break;
        }

    }

}
void atualizaBalas (projeteis balas[], int tamanho)
{
   for (int i=0;i<tamanho;i++){
        if (balas[i].ativo)
        {
            balas[i].x+=balas[i].velocidade;
            if (balas[i].x> LARGURA_TELA)
                balas[i].ativo=false;
        }
   }

}
void desenhaBalas (projeteis balas[], int tamanho)
{
    for (int i=0;i<tamanho;i++)
    {
        if (balas[i].ativo)
        {
            al_draw_bitmap(bala,balas[i].x,balas[i].y,0);
            //al_draw_filled_circle(balas[i].x,balas[i].y,2,al_map_rgb(255,255,255));
        }
    }

}
void initFase (fase &space){
    space.velocidade=10;
    space.x = 800;
}
void desenhafase(fase &space){
    while (1){
    al_draw_bitmap(fase1,space.x-=space.velocidade,0,0);
     if (space.x<0)
            al_draw_bitmap(fase1,space.x-=space.velocidade,0,0);
            break;
    }
}

void initCometas (cometas cometa [],int tamanho)
{
    for (int i =0;i<tamanho;i++){
        cometa[i].id=inimigos;
        cometa[i].velocidade = 5;
        cometa[i].bordaX=29;
        cometa[i].bordaY=29;
        cometa[i].ativo= false;
    }
}
void spawnCometas (cometas cometa [],int tamanho)
{
    for (int i=0;i<tamanho;i++){
        if (!cometa[i].ativo)
        {
            if (rand()%500==0)
            {
                cometa[i].x=LARGURA_TELA;
                cometa[i].y =30+rand()%(ALTURA_TELA-60);
                cometa[i].ativo=true;
                break;
            }
        }
    }

}
void atualizarCometas (cometas cometa [],int tamanho,naveEspacial &nave)
{
 for (int i=0;i<tamanho;i++)
 {
     if (cometa[i].ativo)
     {
         cometa[i].x-=cometa[i].velocidade;
         if (cometa[i].x<0)
         {
             cometa[i].ativo=false;
         }
         if (cometa[i].x<LARGURA_TELA/2)
         {
             while (cometa[i].y!=nave.y){
                if (cometa[i].x>nave.x){
                    if(cometa[i].y>nave.y){
                        cometa[i].y-=cometa[i].velocidade;
                        break;
                    }
                    else if(cometa[i].y<nave.y){
                        cometa[i].y+=cometa[i].velocidade;
                        break;
                    }

                    }
                    break;
            }
         }
     }
 }

}
void desenhaCometas (cometas cometa [],int tamanho)
{
    for (int i =0;i<tamanho;i++)
    {
        if (cometa[i].ativo)
        {
            //al_draw_bitmap(inimigo,cometa[i].x,cometa[i].y-20);
            al_draw_bitmap(inimigo,cometa[i].x,cometa[i].y,0);
        }

    }

}



