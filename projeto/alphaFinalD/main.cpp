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
//--------VARIAVEIS GLOBAIS--------------
    int timeBit=0;
//largura e altura de cada sprite dentro da folha
    int altura_sprite=64, largura_sprite=64;
    //quantos sprites tem em cada linha da folha, e a atualmente mostrada
    int colunas_folha=4, coluna_atual=0;
    //quantos sprites tem em cada coluna da folha, e a atualmente mostrada
    int linha_atual=0, linhas_folha=4;
    //posicoes X e Y da folha de sprites que serao mostradas na tela
    int regiao_x_folha=0, regiao_y_folha=0;
    //quantos frames devem se passar para atualizar para o proximo sprite
    int frames_sprite=12, cont_frames=0;
    //posicao X Y da janela em que sera mostrado o sprite
    int pos_x_sprite=50, pos_y_sprite=150;
    //velocidade X Y que o sprite ira se mover pela janela
ALLEGRO_BITMAP *folha_sprite=NULL;
ALLEGRO_BITMAP *estrelaAzul=NULL;
bool fase1=true,fase2,fase3;
ALLEGRO_BITMAP *bossI =NULL;
float degrees=0.0f;
ALLEGRO_BITMAP *buracoN = NULL;
ALLEGRO_BITMAP *botao=NULL;
ALLEGRO_BITMAP *botaoA=NULL;
ALLEGRO_BITMAP *imagem = NULL;
bool menuu = false;
bool start=false;
ALLEGRO_BITMAP *propulsorF=NULL;
ALLEGRO_BITMAP *inimigo = NULL;
ALLEGRO_BITMAP *bala = NULL;
ALLEGRO_BITMAP *balaIn =NULL;
ALLEGRO_BITMAP *naveE = NULL;
ALLEGRO_SAMPLE *explosao = NULL;
ALLEGRO_SAMPLE *laser = NULL;
ALLEGRO_SAMPLE *fase01 = NULL;

ALLEGRO_SAMPLE_INSTANCE *inst_laser = NULL;
ALLEGRO_SAMPLE_INSTANCE *inst_explosao = NULL;
ALLEGRO_SAMPLE_INSTANCE *fase_01 = NULL;

const int numMinions =10;
const int numEstrelas = 100; //29/10
const int numPlanos = 3; //29/10
const int fps = 60;
const int numBalas =5;
enum teclas {cima,baixo,esquerda,direita,espaco,enter};
// -----------------------------------------

// --------PROTÓTIPOS------------------
void menu();
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
void BalaColidida (projeteis balas[], int b_tamanho, Inimigos minions[], int c_tamanho,naveEspacial &nave );
void BalaColididaIn (projeteis balas[], int b_tamanho, naveEspacial &nave);
void atiraInimigos (Inimigos minions [],int tamanho,projeteis balas[]);
void atualizaBalasIn (projeteis balas[], int tamanho,Inimigos minions[]);
void desenhaBalasIn (projeteis balas[], int tamanho,Inimigos minions[]);
void initBalasIn (projeteis balas[],int tamanho);

void initminions (Inimigos minions [],int tamanho);
void spawnminions (Inimigos minions [],int tamanho);
void atualizarminions (Inimigos minions [],int tamanho,naveEspacial &nave,astros &buraco);
void desenhaminions (Inimigos minions [],int tamanho);
void minionsColidido(Inimigos minions[],int c_tamanho,naveEspacial &nave);

void spawnBuraco (astros &buraco, Inimigos &boss);
void initBuraco (astros &buraco);
void atualizaBuraco (astros &buraco,naveEspacial &nave);
void desenhaBuraco (astros &buraco);
void buracoColidido(Inimigos minions[],int c_tamanho, astros &buraco);

void initPlanoFundo(Estrelas estrelasPF[][numEstrelas],int PF_tamanho, int e_tamanho); //29/10
void atualizarPlanoFundo(Estrelas estrelasPF[][numEstrelas],int PF_tamanho, int e_tamanho); //29/10
void desenhaPlanoFundo(Estrelas estrelasPF[][numEstrelas],int PF_tamanho, int e_tamanho); //29/10

void colisaoB (projeteis balas[],int b_tamanho,naveEspacial &nave,Inimigos &boss );
void initboss (Inimigos &boss);
void spawnboss (Inimigos &boss, naveEspacial &nave);
void atualizaBoss (Inimigos &boss);
void desenhaBoss (Inimigos &boss);

void propulsor (astros &buraco,naveEspacial &nave,bool teclas[]);
void desenhaProp (naveEspacial &nave);

void initEstrelaAz (astros &eAzul);
void spawnEstrelaAz (astros &eAzul, naveEspacial &nave);
void atualizaEstrelaAz (astros &eAzul,naveEspacial &nave);
void desenhaEstrelaAz (astros &eAzul);
void boom(Inimigos minions[],int tamanho);
//------------------------------------------------------

int main(void){
// iniciando
    Inimigos boss;
    Inimigos minions[numMinions];
    astros eAzul;
    astros buraco;
    naveEspacial nave;
    projeteis balas [numBalas];
    projeteis balasIn [numBalas];
    Estrelas estrelasPF[numPlanos][numEstrelas]; //29/10
    al_init_font_addon();
    al_init_ttf_addon();
    al_init();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon ();
    al_install_audio();
    al_init_acodec_addon();

    al_reserve_samples(10); // 29/10

// variaveis
    int vX=0;
    int vY=0;
    bool atiraIn=false;
    bool gameOver = false;
    bool teclas []={false,false,false,false,false,false};
    ALLEGRO_FONT *fonte = NULL;
    bool desenha = true;
    ALLEGRO_AUDIO_STREAM *musica = NULL;
    al_reserve_samples(5);
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


    laser = al_load_sample("laser.wav"); //29/10
    explosao = al_load_sample("explosao.wav"); //29/10
    fase01=al_load_sample("buracoNegro.wav");

    inst_laser = al_create_sample_instance(laser); //29/10
    inst_explosao = al_create_sample_instance(explosao); //29/10
    fase_01=al_create_sample_instance(fase01);
    al_attach_sample_instance_to_mixer(fase_01, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(inst_laser, al_get_default_mixer()); //29/10
    al_attach_sample_instance_to_mixer(inst_explosao, al_get_default_mixer());//29/10


//SOURCES
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos,al_get_mouse_event_source());
    al_register_event_source(fila_eventos,al_get_timer_event_source(timer));


// codigo
    initEstrelaAz(eAzul);
    initboss(boss);
    srand(time(NULL));
    initminions(minions,numMinions);
    initBuraco(buraco);
    Initnave(nave);
    initBalas(balas,numBalas);
    initBalasIn (balasIn,numBalas);
    initPlanoFundo(estrelasPF, numPlanos,numEstrelas);


//audio
    musica = al_load_audio_stream("BeepBox-Song.wav", 4, 1024);
    al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
//texto
    fonte = al_load_font("space age.ttf", 41, 0);

//imagem
   folha_sprite=al_load_bitmap("exp2_0.png");
    estrelaAzul=al_load_bitmap("estrelaAzul.png");
    propulsorF=al_load_bitmap("hiclipart4.png");
    bossI = al_load_bitmap("rocketship.png");
    buracoN = al_load_bitmap("download.png");
    balaIn = al_load_bitmap("shot7.png");
    inimigo =al_load_bitmap("boarder.png");
    bala = al_load_bitmap("shot2.png");
    botao= al_load_bitmap("aceso.png");
    botaoA= al_load_bitmap("apagado.png");
    naveE = al_load_bitmap("ship2.png");
    imagem = al_load_bitmap("menuteste2.bmp");
    al_set_new_display_flags (ALLEGRO_FULLSCREEN_WINDOW);
    janela = al_create_display(res_x_comp,res_y_comp);

    al_clear_to_color(al_map_rgb(255, 255, 255));
   //al_draw_bitmap_region(imagem,0,0,res_x_comp,res_y_comp,0,0,0);

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
                case ALLEGRO_KEY_ENTER:
                    teclas[enter]=true;
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
                case ALLEGRO_KEY_ENTER:
                    teclas[enter]=false;
                    break;
            }
        }
        if (rand()%10==0)
            {
                atiraInimigos(minions,numBalas,balasIn);
                atiraIn=true;
            }
   else if (evento_atual.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
                if (evento_atual.mouse.x >= LARGURA_TELA/2- al_get_bitmap_width(botao) / 2 &&
                evento_atual.mouse.x <= LARGURA_TELA/2 + al_get_bitmap_width(botao) / 2 &&
                evento_atual.mouse.y >= ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2 &&
                evento_atual.mouse.y <= ALTURA_TELA/2 + al_get_bitmap_height(botao) / 2)
                {
                start = true;
                gameOver=false;
                Initnave(nave);
                initminions(minions,numMinions);
                initBalas(balas,numBalas);
                nave.vidas=3;
                }
        }
        else if (evento_atual.type == ALLEGRO_EVENT_TIMER)
        {

            timeBit++;
            //explosao nave
            for (int i =0;i<numMinions;i++)
            {
                if (!minions[i].ativo && minions[i].explosao)
                {
                cont_frames++;
             if (cont_frames >= frames_sprite){
                //reseta cont_frames
                cont_frames=0;
                minions[i].explosao=false;
             }
                //incrementa a coluna atual, para mostrar o proximo sprite
                coluna_atual++;
                //se coluna atual passou da ultima coluna
                if (coluna_atual >= colunas_folha){
                    //volta pra coluna inicial
                    coluna_atual=0;
                    //incrementa a linha, se passar da ultima, volta pra primeira
                    linha_atual = (linha_atual+1) % linhas_folha;
                    //calcula a posicao Y da folha que sera mostrada
                    regiao_y_folha = linha_atual * altura_sprite;
                }
                //calcula a regiao X da folha que sera mostrada
                regiao_x_folha = coluna_atual * largura_sprite;



                }

            }

        //-----menu---------
        if (!start){
            Initnave(nave);
           // al_draw_bitmap_region(imagem,0,0,res_x_comp,res_y_comp,0,0,0);
            al_set_audio_stream_playing(musica,1);
        if (evento_atual.type == ALLEGRO_EVENT_MOUSE_AXES){
                // Verificamos se ele está sobre o botao
               if (evento_atual.mouse.x >= LARGURA_TELA/2- al_get_bitmap_width(botao) / 2 &&
                evento_atual.mouse.x <= LARGURA_TELA/2 + al_get_bitmap_width(botao) / 2 &&
                evento_atual.mouse.y >= ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2 &&
                evento_atual.mouse.y <= ALTURA_TELA/2 + al_get_bitmap_height(botao) / 2)
                {
                  al_draw_bitmap(botao,LARGURA_TELA/2-al_get_bitmap_width(botao) / 2,ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2 ,0);
                    //menuu =true;
                }
                else
                {
                   al_draw_bitmap(botaoA,LARGURA_TELA/2-al_get_bitmap_width(botao) / 2,ALTURA_TELA/2 - al_get_bitmap_height(botao)/ 2 ,0);
                    //menuu=false;
                }

            }

            al_draw_text(fonte, al_map_rgb(0, 0, 0),LARGURA_TELA/2- al_get_bitmap_width(botao) / 2,ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2, 0, "Start");
            al_flip_display();

        }else{
             al_set_audio_stream_playing(musica,0);
            desenha = true;
            if (!buraco.gravidade){
        if (teclas[esquerda])
            MoveNaveEsquerda(nave);
        if (teclas[cima])
            MoveNaveCima (nave);
        if (teclas[baixo])
            MoveNaveBaixo (nave);
        if (teclas[direita])
            MoveNaveDireita(nave);
        }else {
            if (nave.x<buraco.x)
                nave.x=nave.x+1;
            else
                nave.x-=1;
            if(nave.y>buraco.y)
                nave.y-=1;
            else
                nave.y+=1;
        }
        if (buraco.ativo)
            propulsor(buraco,nave,teclas);
        if (teclas[espaco])
            atualizaBalas(balas,numBalas);
        if (atiraIn==true)
            atualizaBalasIn(balasIn,numBalas,minions);
        if (!gameOver)
        {
            spawnEstrelaAz(eAzul,nave);
            atualizaEstrelaAz(eAzul,nave);
            spawnboss(boss, nave);
            atualizaBoss(boss);
            colisaoB(balas,numBalas,nave,boss);
            spawnBuraco(buraco,boss);
            atualizaBuraco(buraco,nave);
            buracoColidido(minions,numMinions,buraco);
            atualizarPlanoFundo(estrelasPF,numPlanos,numEstrelas); // 29/10
            spawnminions(minions,numMinions);
            atualizarminions(minions,numMinions,nave,buraco);
            BalaColidida(balas,numBalas, minions, numMinions,nave);
            minionsColidido(minions, numMinions,nave);
            BalaColididaIn (balasIn,numBalas,nave);
            if(nave.vidas <= 0)
                gameOver = true;
        }
        else {
            start=false;
        }
        }
      //  desenhafase(space);

    }
       if (desenha && al_is_event_queue_empty(fila_eventos))
        {
            desenha = false;
            if (!start){
            al_draw_bitmap_region(imagem,0,0,res_x_comp,res_y_comp,0,0,0);
            if (menu){
            al_draw_bitmap(botao,LARGURA_TELA/2-al_get_bitmap_width(botao) / 2,ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2 ,0);
            }else
            al_draw_bitmap(botaoA,LARGURA_TELA/2-al_get_bitmap_width(botao) / 2,ALTURA_TELA/2 - al_get_bitmap_height(botao)/ 2 ,0);
            }else{
             if(!gameOver)
            {
                desenhaEstrelaAz(eAzul);
                desenhaPlanoFundo(estrelasPF, numPlanos,numEstrelas);   //29/10
                desenhaBuraco(buraco);
                desenhaBoss(boss);
                desenhaProp(nave);
                desenhanave(nave);
                desenhaBalas(balas,numBalas);
                desenhaminions(minions,numMinions);
                boom(minions,numMinions);
                desenhaBalasIn(balasIn,numBalas,minions);
                desenhaminions(minions,numMinions);
                al_draw_textf(fonte,al_map_rgb(255,255,255),0,0,NULL,"VIDAS: %d  /  PONTOS: %d",nave.vidas,nave.pontos);
            }
            al_flip_display();
            al_clear_to_color (al_map_rgb(0,0,0));
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
al_destroy_sample(laser);
al_destroy_sample(explosao);
al_destroy_sample_instance(inst_explosao);

al_destroy_sample_instance(inst_laser);
    return 0;

}
// ---------- NAVE ---------------
void Initnave(naveEspacial &nave)
{
    nave.x=20;
    nave.y=ALTURA_TELA/2;
    nave.id=jogador;
    nave.vidas =3;
    nave.velocidade=7;
    nave.borda_x=12;
    nave.borda_y=14;
    nave.pontos = 0;
    nave.propulsor=false;

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
// -----------------------------------------

// -----PROJÉTEIS ----------------------------
void initBalasIn (projeteis balas[],int tamanho)
{
    for (int i=0;i<tamanho;i++){
        balas[i].id= projetil;
        balas[i].velocidade = 10;
        balas [i].ativo=false;

    }
}
void atiraInimigos (Inimigos minions [],int tamanho,projeteis balas[])
{
    for (int i=0;i<tamanho;i++){
        if (!balas[i].ativo && minions[i].ativo){
            balas[i].x = minions[i].x-28;
            balas[i].y = minions[i].y+17;
            balas[i].ativo=true;
            break;
        }

    }

}
void atualizaBalasIn (projeteis balas[], int tamanho,Inimigos minions[])
{
   for (int i=0;i<tamanho;i++){
        if (balas[i].ativo)
        {
            balas[i].x-=balas[i].velocidade;
            if (balas[i].x< 0)
                balas[i].ativo=false;
        }
   }

}
void desenhaBalasIn (projeteis balas[], int tamanho,Inimigos minions[])
{
    for (int i=0;i<tamanho;i++)

        if (balas[i].ativo)
        {
            al_draw_bitmap(balaIn,balas[i].x,balas[i].y,0);
        }

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

            al_stop_sample_instance(inst_laser); //29/10
			al_play_sample_instance(inst_laser); //29/10
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

        if (balas[i].ativo)
        {
            al_draw_bitmap(bala,balas[i].x,balas[i].y,0);
        }
}
void BalaColididaIn (projeteis balas[], int b_tamanho, naveEspacial &nave)
{
    for(int i = 0; i < b_tamanho; i++)
    {
        if(balas[i].ativo)
        {
            if(balas[i].x > (nave.x - nave.borda_x) &&
            balas[i].x < (nave.x + nave.borda_x) &&
            balas[i].y > (nave.y - nave.borda_y) &&
            balas[i].y < (nave.y + nave.borda_y))
                {
                    balas[i].ativo = false;
                    nave.vidas-=1;
                    printf("%d",nave.vidas);
                }
        }
    }

}



void BalaColidida (projeteis balas[], int b_tamanho, Inimigos minions[], int c_tamanho,naveEspacial &nave )
{
    for(int i = 0; i < b_tamanho; i++)
    {
        if(balas[i].ativo)
        {
            for(int j = 0; j < c_tamanho; j++)
            {
                if(minions[j].ativo)
                {
                    if(balas[i].x > (minions[j].x - minions[j].bordaX) &&
                       balas[i].x < (minions[j].x + minions[j].bordaX) &&
                       balas[i].y > (minions[j].y - minions[j].bordaY) &&
                       balas[i].y < (minions[j].y + minions[j].bordaY))
                    {

                        al_stop_sample_instance(inst_explosao); //29/10
						al_play_sample_instance(inst_explosao); //29/10
                        balas[i].ativo = false;
                        minions[j].ativo = false;
                        minions[j].explosao=true;
                        nave.pontos++;
                    }

            }
        }
    }
    }

}

// ---------- minions ------------------------
void initminions (Inimigos minions [],int tamanho)
{
    for (int i =0;i<tamanho;i++){
        minions[i].id=inimigos;
        minions[i].velocidade = 5;
        minions[i].bordaX=29;
        minions[i].bordaY=29;
        minions[i].ativo= false;
    }
}
void spawnminions (Inimigos minions [],int tamanho)
{
    for (int i=0;i<tamanho;i++){
        if (!minions[i].ativo)
        {
            if (rand()%500==0)
            {
                minions[i].x=LARGURA_TELA;
                minions[i].y =30+rand()%(ALTURA_TELA-60);
                minions[i].ativo=true;
                break;
            }
        }
    }

}
void atualizarminions (Inimigos minions [],int tamanho,naveEspacial &nave, astros &buraco)
{

 for (int i=0;i<tamanho;i++)
 {
    if (!buraco.ativo){
     if (minions[i].ativo)
     {
         minions[i].x-=minions[i].velocidade;

         if (minions[i].x<0)
         {
             minions[i].ativo=false;
         }

         if (minions[i].x<LARGURA_TELA/2)
         {
             while (minions[i].y<nave.y +10 || minions[i].y>nave.y -10){
                if (minions[i].x>nave.x){
                    if(minions[i].y>nave.y){
                        minions[i].y-=minions[i].velocidade;
                        break;
                    }
                    else if(minions[i].y<nave.y){
                        minions[i].y+=minions[i].velocidade;
                        break;
                    }

                    }
                    break;
            }
         }
     }
 }else {
                if (minions[i].x>buraco.x)
                    minions[i].x-=minions[i].velocidade;
                else
                    minions[i].x+=minions[i].velocidade;
                if(minions[i].y>buraco.y){
                    minions[i].y-=minions[i].velocidade;
                }else if(minions[i].y<buraco.y){
                        minions[i].y+=minions[i].velocidade;

                    }

        }
 }
}
void desenhaminions (Inimigos minions [],int tamanho)
{
    for (int i =0;i<tamanho;i++)
    {
        if (minions[i].ativo)
        {
            al_draw_bitmap(inimigo,minions[i].x,minions[i].y,0);
        }
    }

}

void minionsColidido(Inimigos minions[],int c_tamanho,naveEspacial &nave)
{
    for(int i = 0; i < c_tamanho; i++)
    {
        if(minions[i].ativo)
        {
           if((minions[i].x - minions[i].bordaX) < (nave.x + nave.borda_x) &&
              (minions[i].x + minions[i].bordaX) > (nave.x - nave.borda_x) &&
              (minions[i].y - minions[i].bordaY) < (nave.y + nave.borda_y) &&
              (minions[i].y + minions[i].bordaY) > (nave.y - nave.borda_y))
           {
               minions[i].ativo = false;
               nave.vidas--;
           }
            else if (minions[i].x<0)
            {
             minions[i].ativo=false;
             nave.vidas--;
            }
        }
    }


}
// -------------------- PLANO DE FUNDO -----------------------------------------------

void initPlanoFundo(Estrelas estrelasPF[][numEstrelas],int PF_tamanho, int e_tamanho)
{
    for(int i = 0; i < PF_tamanho; i++)
    {
        for(int j = 0; j <e_tamanho; j++)
        {
            if(i == 0)
            {
                //estrelasPF[i][j].id = ESTRELA;
                estrelasPF[i][j].x = 5 + rand() % (LARGURA_TELA - 10);
                estrelasPF[i][j].y = 5 + rand() % (ALTURA_TELA - 10);
                estrelasPF[i][j].velocidade = 8;
            }
            else if (i == 1)
            {
                //estrelasPF[i][j].id = ESTRELA;
                estrelasPF[i][j].x = 5 + rand() % (LARGURA_TELA - 10);
                estrelasPF[i][j].y = 5 + rand() % (ALTURA_TELA - 10);
                estrelasPF[i][j].velocidade = 3;
            }
            else if(i == 2)
            {
                //estrelasPF[i][j].id = ESTRELA;
                estrelasPF[i][j].x = 5 + rand() % (LARGURA_TELA - 10);
                estrelasPF[i][j].y = 5 + rand() % (ALTURA_TELA - 10);
                estrelasPF[i][j].velocidade = 1;
            }
        }
    }


}
void atualizarPlanoFundo(Estrelas estrelasPF[][numEstrelas],int PF_tamanho, int e_tamanho)
{
  for(int i = 0; i < PF_tamanho; i++)
    {
        for(int j = 0; j <e_tamanho; j++)
        {
            if(i == 0)
            {
                estrelasPF[i][j].x -= estrelasPF[i][j].velocidade;

                if (estrelasPF[i][j].x < 0)
                    estrelasPF[i][j].x = LARGURA_TELA;
            }
            else if (i == 1)
            {
                estrelasPF[i][j].x -= estrelasPF[i][j].velocidade;

                if (estrelasPF[i][j].x < 0)
                    estrelasPF[i][j].x = LARGURA_TELA;
            }
            else if(i == 2)
            {
                estrelasPF[i][j].x -= estrelasPF[i][j].velocidade;

                if (estrelasPF[i][j].x < 0)
                    estrelasPF[i][j].x = LARGURA_TELA;;
            }
        }
    }


}
void desenhaPlanoFundo(Estrelas estrelasPF[][numEstrelas],int PF_tamanho, int e_tamanho)
{
      for(int i = 0; i < PF_tamanho; i++)
    {
        for(int j = 0; j <e_tamanho; j++)
        {
            if(i == 0)
            {
                al_draw_pixel(estrelasPF[i][j].x, estrelasPF[i][j].y, al_map_rgb(255,255,255));
            }
            else if (i == 1)
            {
                al_draw_pixel(estrelasPF[i][j].x, estrelasPF[i][j].y, al_map_rgb(255,255,255));
            }
            else if(i == 2)
            {
                al_draw_pixel(estrelasPF[i][j].x, estrelasPF[i][j].y, al_map_rgb(255,255,255));
            }
        }
    }
}
// -------------------- Buraco Negro -----------------------------------------------
void initBuraco (astros &buraco){
    buraco.ativo=false;
    buraco.velocidade=3;
    buraco.bordaX=78;
    buraco.bordaY=78;
}
void spawnBuraco (astros &buraco,Inimigos &boss){
    if (!buraco.ativo ){
            if(boss.vidas==0 && fase1 ==true){
             al_play_sample_instance(fase_01);
              buraco.x=LARGURA_TELA;
              buraco.y=ALTURA_TELA/2;
              buraco.ativo=true;
              buraco.gravidade=true;
            }
    }
}

void atualizaBuraco (astros &buraco,naveEspacial &nave){
    if (buraco.x>LARGURA_TELA/2 || nave.propulsor ){
        buraco.x=buraco.x-buraco.velocidade;
    }
    else if(buraco.x<0){
        buraco.ativo=false;
        buraco.gravidade=false;
        fase1=false;
        fase2=true;
    }
    degrees++;

}
void desenhaBuraco (astros &buraco){
   if (buraco.ativo)
   al_draw_rotated_bitmap(buracoN,127,127,buraco.x,buraco.y,degrees*3.1415/180,0);
}

// -------------------- Boss -----------------------------------------------
void initboss (Inimigos &boss){
    boss.velocidade=2;
    boss.ativo=false;
    boss.vidas=3;
    boss.bordaX=44;
    boss.bordaY=39;
}
void spawnboss (Inimigos &boss,naveEspacial &nave){
            if(!boss.ativo){
            if (nave.pontos==10){
                boss.x=LARGURA_TELA;
                boss.y=ALTURA_TELA/2;
                boss.ativo=true;

            }
            if (boss.vidas==0){
                    boss.ativo=false;
             }
            }

}
void atualizaBoss (Inimigos &boss){
if(boss.vidas!=0){
    if(boss.ativo){
     if(boss.x>0)
     {
         boss.x=boss.x-boss.velocidade;

        } else boss.ativo=false;
    }
}else
    boss.ativo=false;
}
void desenhaBoss (Inimigos &boss){
    if(boss.ativo)
   al_draw_bitmap(bossI,boss.x,boss.y,0);

}

void colisaoB (projeteis balas[], int b_tamanho,naveEspacial &nave,Inimigos &boss )
{
    for(int i = 0; i < b_tamanho; i++)
    {
        if(balas[i].ativo)
        {
                if(boss.ativo)
                {
                    if(balas[i].x > (boss.x - boss.bordaX) &&
                       balas[i].x < (boss.x + boss.bordaX) &&
                       balas[i].y > (boss.y - boss.bordaY) &&
                       balas[i].y < (boss.y + boss.bordaY))
                    {

                        al_stop_sample_instance(inst_explosao); //29/10
						al_play_sample_instance(inst_explosao); //29/10
                        balas[i].ativo = false;
                        boss.vidas -=1;
                        nave.pontos++;
                    }

            }
    }
    }

}
void buracoColidido(Inimigos minions[],int c_tamanho, astros &buraco)
{
    for(int i = 0; i < c_tamanho; i++)
    {
        if(minions[i].ativo)
        {
           if((minions[i].x - minions[i].bordaX) < (buraco.x + buraco.bordaX) &&
              (minions[i].x + minions[i].bordaX) > (buraco.x - buraco.bordaX) &&
              (minions[i].y - minions[i].bordaY) < (buraco.y + buraco.bordaY) &&
              (minions[i].y + minions[i].bordaY) > (buraco.y - buraco.bordaY))
           {
               minions[i].ativo = false;
           }
        }
    }
}
void propulsor (astros &buraco,naveEspacial &nave,bool teclas[]){

    if (teclas[enter]){

        buraco.gravidade=false;
        nave.propulsor=true;

    }else{
        buraco.gravidade=true;
        nave.propulsor=false;
    }

}
void desenhaProp (naveEspacial &nave){
    if (nave.propulsor){
        al_draw_bitmap(propulsorF,nave.x-100,nave.y-136,0);
    }
}
void initEstrelaAz (astros &eAzul){
    eAzul.ativo=false;
    eAzul.velocidade=1;
}
void spawnEstrelaAz (astros &eAzul, naveEspacial &nave){
    if (!eAzul.ativo){
        if (nave.pontos>30 && fase2){
              eAzul.x=LARGURA_TELA;
              eAzul.y=ALTURA_TELA/2;
              eAzul.ativo=true;
        }

    }

}
void atualizaEstrelaAz (astros &eAzul,naveEspacial &nave){
    if (eAzul.x>0){
        eAzul.x-=eAzul.velocidade;
    }else{
        eAzul.ativo=false;
    }


}
void desenhaEstrelaAz (astros &eAzul){
    al_draw_bitmap(estrelaAzul,eAzul.x,eAzul.y,0);

}
void boom(Inimigos minions[],int tamanho){
    for (int i =0;i<tamanho;i++)
    {
        if (!minions[i].ativo&&minions[i].explosao)
        {
            al_draw_bitmap_region(folha_sprite,
                    regiao_x_folha,regiao_y_folha,
                    largura_sprite,altura_sprite,
                    minions[i].x,minions[i].y,0);
        }

}

}

