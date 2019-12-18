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
//--------VARIAVEIS GLOBAIS--------------
//---------------FILA SPRITE EXPLOSÃO--------------------
    int dir_x=5,dir_y=5;
    int velEstrelas=0;
    int timeBit=0;
    int controleF=0;
    int controle2=0;
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

ALLEGRO_BITMAP *balaBossF =NULL;
ALLEGRO_BITMAP *bossFinal =NULL;
ALLEGRO_BITMAP *sun=NULL;
ALLEGRO_BITMAP *balaBoss=NULL;
ALLEGRO_BITMAP *wormHole=NULL;
ALLEGRO_BITMAP *escudo=NULL;
ALLEGRO_BITMAP *folha_sprite=NULL;
ALLEGRO_BITMAP *terra=NULL;
ALLEGRO_BITMAP *estrelaAzul=NULL;
bool fase1=true,fase2=false,fase3=false,faseFinal=false;
ALLEGRO_BITMAP *bossI =NULL;
float degrees=0.0f;
ALLEGRO_BITMAP *buracoN = NULL;
ALLEGRO_BITMAP *botao=NULL;
ALLEGRO_BITMAP *botaoA=NULL;
ALLEGRO_BITMAP *imagem = NULL;
bool start=false;
ALLEGRO_BITMAP *propulsorF=NULL;
ALLEGRO_BITMAP *inimigo = NULL;
ALLEGRO_BITMAP *bala = NULL;
ALLEGRO_BITMAP *balaIn =NULL;
ALLEGRO_BITMAP *naveE = NULL;
ALLEGRO_SAMPLE *explosao = NULL;
ALLEGRO_SAMPLE *laser = NULL;
ALLEGRO_SAMPLE *fase01 = NULL;
ALLEGRO_SAMPLE *fase02 = NULL;
ALLEGRO_SAMPLE *fase03 = NULL;
ALLEGRO_SAMPLE *fasefinal = NULL;


ALLEGRO_SAMPLE_INSTANCE *inst_laser = NULL;
ALLEGRO_SAMPLE_INSTANCE *inst_explosao = NULL;
ALLEGRO_SAMPLE_INSTANCE *fase_01 = NULL;
ALLEGRO_SAMPLE_INSTANCE *fase_02 = NULL;
ALLEGRO_SAMPLE_INSTANCE *fase_03 = NULL;
ALLEGRO_SAMPLE_INSTANCE *fase_final = NULL;
const int numMinions =10;
const int numEstrelas = 100; //29/10
const int numPlanos = 3; //29/10
const int fps = 60;
const int numBalas =5;
enum teclas {cima,baixo,esquerda,direita,espaco,enter,E};
// -----------------------------------------

// --------PROTÓTIPOS------------------
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
void colisaoBN (Inimigos &boss, naveEspacial &nave);
void initboss (Inimigos &boss);
void spawnboss (Inimigos &boss, naveEspacial &nave);
void atualizaBoss (Inimigos &boss,naveEspacial &nave);
void desenhaBoss (Inimigos &boss);
void atiraBoss (Inimigos &boss,int tamanho,projeteis balas[]);
void BalaColididaBoss (projeteis balas[], int b_tamanho, naveEspacial &nave);
void atualizaBalasBoss (projeteis balas[], int tamanho,Inimigos &boss);
void desenhaBalasBoss(projeteis balas[], int tamanho,Inimigos &boss);
void initBalasBoss (projeteis balas[],int tamanho);

void propulsor (astros &buraco,naveEspacial &nave,bool teclas[]);
void desenhaProp (naveEspacial &nave);

void escudoA (astros &eAzul,naveEspacial &nave,bool teclas[]);
void desenhaEscudo (naveEspacial &nave);

void initEstrelaAz (astros &eAzul);
void spawnEstrelaAz (astros &eAzul);
void atualizaEstrelaAz (astros &eAzul,naveEspacial &nave);
void desenhaEstrelaAz (astros &eAzul);
void boom(Inimigos minions[],int tamanho);

void initMin (astros &worm);
void spawnWorm (astros &worm, naveEspacial &nave, astros &buraco);
void atualizaWorm (astros &worm);
void desenhaWorm (astros &worm);
void colisaoWorm (naveEspacial &nave, astros &worm,Estrelas estrelasPF[][numEstrelas],int PF_tamanho, int e_tamanho);

void initEarth(astros &earth,astros &sol);
void atualizaEarth(astros &earth,astros &sol);
void desenhaEarth (astros &earth, astros &sol);
void spawnEarth (astros &earth,naveEspacial &nave);

void initbossF (Inimigos &bossF);
void spawnbossF (Inimigos &bossF, naveEspacial &nave,astros &earth);
void atualizaBossF (Inimigos &bossF,naveEspacial &nave);
void desenhaBossF (Inimigos &bossF);
void atiraBossF (Inimigos &boss,int tamanho,projeteis balas[]);
void BalaColididaBossF (projeteis balas[], int b_tamanho, naveEspacial &nave,projeteis balasBossf []);
void atualizaBalasBossF (projeteis balas[], int tamanho,Inimigos &boss);
void desenhaBalasBossF(projeteis balas[], int tamanho,Inimigos &boss);
void initBalasBossF (projeteis balas[],int tamanho);
void balasColididas(projeteis balasBossF[],int b_tamanho,naveEspacial &nave);
//------------------------------------------------------

int main(void){
// iniciando
    Inimigos boss;
    Inimigos bossF;
    Inimigos minions[numMinions];
    astros eAzul;
    astros earth;
    astros worm;
    astros sol;
    astros buraco;
    naveEspacial nave;
    projeteis balas [numBalas];
    projeteis balasIn [numBalas];
    projeteis balasBoss [numBalas];
    projeteis balasBossF [numBalas];
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
    bool atiraIn=false;
    bool gameOver = false;
    bool teclas []={false,false,false,false,false,false,false};
    ALLEGRO_FONT *fonte = NULL;
    bool desenha = true;
    ALLEGRO_AUDIO_STREAM *musica = NULL;
    ALLEGRO_AUDIO_STREAM *musicaGame = NULL;
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
    fase02=al_load_sample("GaZ.wav");
    fase03=al_load_sample("buracoDeMinhoca .wav");
    fasefinal=al_load_sample("audioBossFinal.wav");

    inst_laser = al_create_sample_instance(laser); //29/10
    inst_explosao = al_create_sample_instance(explosao); //29/10
    fase_01=al_create_sample_instance(fase01);
    fase_02=al_create_sample_instance(fase02);
    fase_03=al_create_sample_instance(fase03);
    fase_final=al_create_sample_instance(fasefinal);
    al_attach_sample_instance_to_mixer(fase_01, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(fase_02, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(fase_03, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(fase_final, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(inst_laser, al_get_default_mixer()); //29/10
    al_attach_sample_instance_to_mixer(inst_explosao, al_get_default_mixer());//29/10


//SOURCES
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos,al_get_mouse_event_source());
    al_register_event_source(fila_eventos,al_get_timer_event_source(timer));


// codigo
    initEarth(earth,sol);
    initMin(worm);
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
    musica = al_load_audio_stream("menu.wav", 4, 1024);
    al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    musicaGame = al_load_audio_stream("jogo.wav", 4, 1024);
    al_set_audio_stream_playmode(musicaGame, ALLEGRO_PLAYMODE_LOOP);
    al_attach_audio_stream_to_mixer(musicaGame, al_get_default_mixer());
    al_set_audio_stream_playing(musicaGame,0);
//texto
    fonte = al_load_font("space age.ttf", 41, 0);

//imagem
    balaBossF=al_load_bitmap("flamer.png");
    bossFinal=al_load_bitmap("shieldship.png");
    sun=al_load_bitmap("5-2-sun-png-hd.png");
    balaBoss=al_load_bitmap("shotwave.png");
    wormHole=al_load_bitmap("Portal600x600.png");
    escudo=al_load_bitmap("Escudo.png");
    folha_sprite=al_load_bitmap("exp2_0.png");
    terra=al_load_bitmap("planet_22.png");
    estrelaAzul=al_load_bitmap("estrelaAzul.png");
    propulsorF=al_load_bitmap("hiclipart4.png");
    bossI = al_load_bitmap("rocketship.png");
    buracoN = al_load_bitmap("buracoNegro.png");
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
                case ALLEGRO_KEY_E:
                    teclas[E]=true;
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
                case ALLEGRO_KEY_E:
                    teclas[E]=false;
                    break;
            }
        }
        if (rand()%10==0)
            {
                atiraInimigos(minions,numBalas,balasIn);
                atiraBoss(boss,numBalas,balasBoss);
                atiraBossF(bossF,numBalas,balasBossF);
                atiraIn=true;
            }

         if (!start){
            if (evento_atual.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
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
                nave.vidas=5;
                }
        }

         if (evento_atual.type == ALLEGRO_EVENT_MOUSE_AXES){
                // Verificamos se ele está sobre o botao
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
                al_draw_text(fonte, al_map_rgb(0, 0, 0),LARGURA_TELA/2- al_get_bitmap_width(botao) / 2,ALTURA_TELA/2 - al_get_bitmap_height(botao) / 2, 0, "Start");


            }
              al_flip_display();
         }


         if (evento_atual.type == ALLEGRO_EVENT_TIMER)
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

            if (timeBit==500 && fase2 && !nave.escudo){
                nave.vidas-=1;
            }
                if (timeBit>500)
                timeBit=0;
                if (faseFinal){
                    velEstrelas=0;
                    controleF++;
                    if (controleF==500){
                        initPlanoFundo(estrelasPF, numPlanos,numEstrelas);
                    }
                    if (earth.ativo && !bossF.ativo && earth.x==LARGURA_TELA){
                        al_draw_text(fonte, al_map_rgb(0, 255, 64),LARGURA_TELA/2-al_get_bitmap_width(botao) / 2-200,ALTURA_TELA/2 , 0, "missao concluida");
                        controle2++;
                        if (controle2==1500){
                            start=false;
                        }
                    }
                }

        //-----menu---------
        if (!start){
        controleF=0;
        initbossF(bossF);
        initEarth(earth,sol);
        initMin(worm);
        initEstrelaAz(eAzul);
        initboss(boss);
        srand(time(NULL));
        initminions(minions,numMinions);
        initBuraco(buraco);
        Initnave(nave);
        initBalas(balas,numBalas);
        initBalasIn (balasIn,numBalas);
        initBalasBossF(balasBossF,numBalas);
        initBalasIn(balasBoss,numBalas);
        initPlanoFundo(estrelasPF, numPlanos,numEstrelas);
        fase1=true;fase2=false; fase3=false; faseFinal=false;
            al_set_audio_stream_playing(musicaGame,0);
            al_set_audio_stream_playing(musica,1);
            al_stop_sample_instance(fase_01);
            al_stop_sample_instance(fase_02);
            al_stop_sample_instance(fase_03);

        }else{
             al_set_audio_stream_playing(musica,0);
             al_set_audio_stream_playing(musicaGame,1);
            desenha = true;
            if (!buraco.habilidade){
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
        if (eAzul.ativo)
            escudoA(eAzul,nave,teclas);
        if (buraco.ativo)
            propulsor(buraco,nave,teclas);
        if (teclas[espaco])
            atualizaBalas(balas,numBalas);
        if (atiraIn==true){
            atualizaBalasIn(balasIn,numBalas,minions);
            atualizaBalasBoss(balasBoss,numBalas,boss);
            atualizaBalasBossF(balasBossF,numBalas,bossF);
        }
        if (!gameOver)
        {
            spawnbossF(bossF,nave,earth);
            atualizaBossF(bossF,nave);
            spawnEarth(earth,nave);
            atualizaEarth(earth,sol);
            spawnEstrelaAz(eAzul);
            atualizaEstrelaAz(eAzul,nave);
            spawnboss(boss, nave);
            atualizaBoss(boss,nave);
            colisaoB(balas,numBalas,nave,bossF);
            colisaoBN(bossF,nave);
            colisaoB(balas,numBalas,nave,boss);
            colisaoBN(boss,nave);
            spawnBuraco(buraco,boss);
            atualizaBuraco(buraco,nave);
            buracoColidido(minions,numMinions,buraco);
            atualizarPlanoFundo(estrelasPF,numPlanos,numEstrelas);

            if (!faseFinal){
            spawnminions(minions,numMinions);
            }

            atualizarminions(minions,numMinions,nave,buraco);
            BalaColidida(balas,numBalas, minions, numMinions,nave);
            minionsColidido(minions, numMinions,nave);
            BalaColididaBossF(balas,numBalas,nave,balasBossF);
            balasColididas(balasBossF,numBalas,nave);
            BalaColididaIn (balasIn,numBalas,nave);
            BalaColididaIn(balasBoss,numBalas,nave);
            spawnWorm(worm,nave,buraco);
            atualizaWorm(worm);
            colisaoWorm(nave,worm,estrelasPF, numPlanos,numEstrelas);
            if(nave.vidas <= 0)
                gameOver = true;
        }
        else {
            start=false;
        }
        }
    }
       if (desenha && al_is_event_queue_empty(fila_eventos))
        {
            desenha = false;
            if (!start){
            al_draw_bitmap_region(imagem,0,0,LARGURA_TELA,ALTURA_TELA,0,0,0);
            }else{
             if(!gameOver)
            {
                desenhaEstrelaAz(eAzul);
                desenhaEarth(earth,sol);
                desenhaPlanoFundo(estrelasPF, numPlanos,numEstrelas);   //29/10
                desenhaBuraco(buraco);
                desenhaBoss(boss);
                desenhaWorm(worm);
                desenhaProp(nave);
                desenhanave(nave);
                desenhaBossF(bossF);
                desenhaEscudo(nave);
                desenhaBalas(balas,numBalas);
                desenhaminions(minions,numMinions);
                boom(minions,numMinions);
                desenhaBalasIn(balasIn,numBalas,minions);
                desenhaBalasBoss(balasBoss,numBalas,boss);
                desenhaBalasBossF(balasBossF,numBalas,bossF);
                desenhaminions(minions,numMinions);
                al_draw_textf(fonte,al_map_rgb(255,255,255),0,0,NULL,"VIDAS: %d  /  PONTOS: %d",nave.vidas,nave.pontos);
            }
            al_flip_display();
            al_clear_to_color (al_map_rgb(0,0,0));
            }


        }




    }

// Finaliza a janela
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
    nave.vidas =5;
    nave.velocidade=7;
    nave.borda_x=12;
    nave.borda_y=14;
    nave.pontos = 0;
    nave.propulsor=false;
    nave.escudo=false;
    nave.desenho=true;

}
void desenhanave (naveEspacial &nave)
{
    if (nave.desenho)
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
    if (nave.x> LARGURA_TELA)
        nave.x= LARGURA_TELA;

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
                estrelasPF[i][j].velocidade = 8+velEstrelas;
            }
            else if (i == 1)
            {
                //estrelasPF[i][j].id = ESTRELA;
                estrelasPF[i][j].x = 5 + rand() % (LARGURA_TELA - 10);
                estrelasPF[i][j].y = 5 + rand() % (ALTURA_TELA - 10);
                estrelasPF[i][j].velocidade = 3+velEstrelas;
            }
            else if(i == 2)
            {
                //estrelasPF[i][j].id = ESTRELA;
                estrelasPF[i][j].x = 5 + rand() % (LARGURA_TELA - 10);
                estrelasPF[i][j].y = 5 + rand() % (ALTURA_TELA - 10);
                estrelasPF[i][j].velocidade = 1+velEstrelas;
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
              buraco.habilidade=true;
            }
    }
}

void atualizaBuraco (astros &buraco,naveEspacial &nave){
    if (buraco.ativo){
    if (buraco.x>LARGURA_TELA/2 || nave.propulsor ){
        buraco.x=buraco.x-buraco.velocidade;
    }
    else if(buraco.x<0){
        buraco.ativo=false;
        buraco.habilidade=false;
        fase1=false;
        fase2=true;
    }
    degrees++;
    }

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
    boss.habilidade=false;
    boss.rotacao=5;
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
void atualizaBoss (Inimigos &boss,naveEspacial &nave){
if(boss.vidas!=0){
        boss.rotacao++;
    if(boss.ativo){
     if(boss.vidas==3)
     {
         boss.x-=boss.velocidade;
         if (boss.y>nave.y)
         boss.y=boss.y-boss.velocidade;
         else
            boss.y=boss.y+boss.velocidade;

        } else{

        boss.habilidade=true;
            boss.x+=dir_x;
            boss.y+=dir_y;
            if (boss.x<=0 || boss.x>=LARGURA_TELA){
                dir_x*=-1;
            }
            if (boss.y<=0 || boss.y>=ALTURA_TELA){
                dir_y*=-1;
                }
        }

    }
}else
    boss.ativo=false;
}

void atiraBoss (Inimigos &boss,int tamanho,projeteis balas[]){
    for (int i=0;i<tamanho;i++){
        if (!balas[i].ativo && boss.ativo){
            balas[i].x = boss.x-45;
            balas[i].y = boss.y+35;
            balas[i].ativo=true;
            break;
        }

    }

}
void atualizaBalasBoss (projeteis balas[], int tamanho,Inimigos &boss){
     for (int i=0;i<tamanho;i++){
        if (balas[i].ativo)
        {
            balas[i].x-=balas[i].velocidade;
            if (balas[i].x< 0)
                balas[i].ativo=false;
        }
   }

}
void desenhaBalasBoss(projeteis balas[], int tamanho,Inimigos &boss){
    for (int i=0;i<tamanho;i++)

        if (balas[i].ativo)
        {
            al_draw_bitmap(balaBoss,balas[i].x,balas[i].y,0);
        }
}



void desenhaBoss (Inimigos &boss){
    if(boss.ativo && !boss.habilidade)
   al_draw_bitmap(bossI,boss.x,boss.y,0);
   if (boss.ativo && boss.habilidade){
    al_draw_rotated_bitmap(bossI,42,42,boss.x,boss.y,boss.rotacao*20.1415/180,0);
   }

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
void colisaoBN (Inimigos &boss, naveEspacial &nave){
    if(boss.ativo)
        {
           if((boss.x - boss.bordaX) < (nave.x + nave.borda_x) &&
              (boss.x + boss.bordaX) > (nave.x - nave.borda_x) &&
              (boss.y - boss.bordaY) < (nave.y + nave.borda_y) &&
              (boss.y + boss.bordaY) > (nave.y - nave.borda_y))
           {
               nave.vidas--;
           }

        }
}
//--------------------Buraco Negro-----------------------------------

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

        buraco.habilidade=false;
        nave.propulsor=true;

    }else{
        buraco.habilidade=true;
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
void spawnEstrelaAz (astros &eAzul){
    if (!eAzul.ativo){
        if (fase2){
              eAzul.ativo=true;
              al_stop_sample_instance(fase_01);
              al_play_sample_instance(fase_02);
              eAzul.x=LARGURA_TELA;
              eAzul.y=ALTURA_TELA/2;

        }

    }

}
void atualizaEstrelaAz (astros &eAzul,naveEspacial &nave){
    if (eAzul.ativo){
        if (eAzul.x>-885){
            eAzul.x-=eAzul.velocidade;
        }else{
            eAzul.ativo=false;
            fase2=false;
            fase3=true;
        }
        }
}
void desenhaEstrelaAz (astros &eAzul){
    if (eAzul.ativo)
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
void escudoA (astros &eAzul,naveEspacial &nave,bool teclas[]){
     if (teclas[E]){

        eAzul.habilidade=false;
        nave.escudo=true;

    }else{
        eAzul.habilidade=true;
        nave.escudo=false;
    }

}
void desenhaEscudo (naveEspacial &nave){
   if (nave.escudo && fase2)
        al_draw_bitmap(escudo,nave.x-178,nave.y-115,0);
}
void initMin (astros &worm){
    worm.velocidade=4;
    worm.ativo=false;
    worm.bordaX=75;
    worm.bordaY=75;

}
void spawnWorm (astros &worm, naveEspacial &nave, astros &buraco){
    if (!worm.ativo){
        if (fase3 ){
            worm.ativo=true;
            worm.x=LARGURA_TELA;
            worm.y=ALTURA_TELA/2;

        }
    }
}
void atualizaWorm (astros &worm){
    if (fase3){
        if (worm.x>LARGURA_TELA/2){
            worm.x=worm.x-worm.velocidade;
        }
    }
}
void colisaoWorm (naveEspacial &nave, astros &worm,Estrelas estrelasPF[][numEstrelas],int PF_tamanho, int e_tamanho){
    if(worm.ativo)
    {
           if((worm.x - worm.bordaX) < (nave.x + nave.borda_x) &&
              (worm.x + worm.bordaX) > (nave.x - nave.borda_x) &&
              (worm.y - worm.bordaY) < (nave.y + nave.borda_y) &&
              (worm.y + worm.bordaY) > (nave.y - nave.borda_y))
           {
               al_play_sample_instance(fase_03);
               nave.desenho = false;
                velEstrelas=20;
                initPlanoFundo(estrelasPF,PF_tamanho,e_tamanho);
                worm.ativo=false;
                fase3=false;
                faseFinal=true;
           }
    }
}

void desenhaWorm (astros &worm){
   if (worm.ativo){
        al_draw_bitmap(wormHole,worm.x-142,worm.y-142,0);
   }
}

void initEarth(astros &earth,astros &sol){
    earth.ativo=false;
    earth.velocidade=2;
    earth.bordaX=232;
    earth.bordaY=232;
    sol.velocidade=1;
    sol.x=LARGURA_TELA;
    sol.y=ALTURA_TELA/2;
}
void spawnEarth (astros &earth,naveEspacial &nave){
    if (!earth.ativo){
        if(faseFinal && controleF==600){
        earth.ativo=true;
        nave.desenho=true;
        earth.x=LARGURA_TELA;
        earth.y=ALTURA_TELA/2;
        al_play_sample_instance(fase_final);
        }
    }
}

void atualizaEarth(astros &earth,astros &sol){
    if (earth.ativo){
        if (earth.x>LARGURA_TELA/2)
            earth.x-=earth.velocidade;
            if (sol.x>LARGURA_TELA/2-300)
            sol.x-=sol.velocidade;

    }
}
void desenhaEarth (astros &earth,astros &sol){
   if (earth.ativo){
         al_draw_bitmap(sun,sol.x,sol.y-600,0);
        al_draw_bitmap(terra,earth.x,earth.y,0);

   }
}

void initbossF (Inimigos &bossF){
    bossF.ativo=false;
    bossF.vidas=4;
    bossF.velocidade=2;
    bossF.bordaX=50;
    bossF.bordaY=81;
}
void initBalasBossF (projeteis balas[],int tamanho){
    for (int i=0;i<tamanho;i++){
        balas[i].velocidade = 10;
        balas [i].ativo=false;
        balas[i].borda_x=18;
        balas[i].borda_y=18;
        balas[i].rotacao=20;
        balas[i].dir_x=5;
        balas[i].dir_y=5;
    }
}
void spawnbossF (Inimigos &bossF, naveEspacial &nave,astros &earth){
    if(!bossF.ativo){
            if (faseFinal && earth.ativo){
                bossF.x=LARGURA_TELA;
                bossF.y=ALTURA_TELA/2;
                bossF.ativo=true;

            }
            if (bossF.vidas==0){
                    bossF.ativo=false;
             }
            }

}
void atualizaBossF (Inimigos &bossF,naveEspacial &nave){
    if(bossF.vidas!=0){
    if(bossF.ativo){
            if (bossF.x>LARGURA_TELA/2){
         bossF.x-=bossF.velocidade;
         if (bossF.x>LARGURA_TELA)
            bossF.velocidade *=-1;
        }
         if (bossF.y<nave.y ){
         bossF.y=bossF.y-bossF.velocidade;
            if (bossF.y<0)
                bossF.velocidade*=-1;
         }else{
            bossF.y=bossF.y+bossF.velocidade;
            if (bossF.y>ALTURA_TELA)
                bossF.velocidade*=-1;
         }

        }
}else
    bossF.ativo=false;
}
void desenhaBossF (Inimigos &bossF){
    if (bossF.ativo){
        al_draw_bitmap(bossFinal,bossF.x,bossF.y,0);
    }
}
void atiraBossF (Inimigos &bossF,int tamanho,projeteis balas[]){
    for (int i=0;i<tamanho;i++){
        if (!balas[i].ativo && bossF.ativo){
            balas[i].x = bossF.x-20;
            balas[i].y = bossF.y+50;
            balas[i].ativo=true;
            break;
        }

    }
}
void BalaColididaBossF (projeteis balas[], int b_tamanho, naveEspacial &nave,projeteis balasBossf []){
        for(int i = 0; i < b_tamanho; i++)
    {
        if(balas[i].ativo)
        {
            for(int j = 0; j < b_tamanho; j++)
            {
                if(balasBossf[j].ativo)
                {
                    if(balas[i].x > (balasBossf[j].x - balasBossf[j].borda_x) &&
                       balas[i].x < (balasBossf[j].x + balasBossf[j].borda_x) &&
                       balas[i].y > (balasBossf[j].y - balasBossf[j].borda_y) &&
                       balas[i].y < (balasBossf[j].y + balasBossf[j].borda_y))
                    {

                        al_stop_sample_instance(inst_explosao); //29/10
						al_play_sample_instance(inst_explosao); //29/10
                        balas[i].ativo = false;
                        balasBossf[j].ativo = false;
                        nave.pontos++;
                    }

            }
        }
    }
    }
}
void atualizaBalasBossF (projeteis balas[], int tamanho,Inimigos &boss){
         for (int i=0;i<tamanho;i++){

        if (balas[i].ativo)
        {
            balas[i].rotacao++;
            balas[i].x-=balas[i].dir_x;
            balas[i].y+=balas[i].dir_y;
            if (balas[i].x<=0 ||balas[i].x>=LARGURA_TELA){
                balas[i].dir_x*=-1;
            }
            if (balas[i].y<=0 || balas[i].y>=ALTURA_TELA){
                balas[i].dir_y*=-1;
                }
        }
       balas[i].rotacao++;
   }

}
void balasColididas(projeteis balasBossF[],int b_tamanho,naveEspacial &nave){
     for(int i = 0; i < b_tamanho; i++)
    {
        if(balasBossF[i].ativo)
        {
           if((balasBossF[i].x - balasBossF[i].borda_x) < (nave.x + nave.borda_x) &&
              (balasBossF[i].x + balasBossF[i].borda_x) > (nave.x - nave.borda_x) &&
              (balasBossF[i].y - balasBossF[i].borda_y) < (nave.y + nave.borda_y) &&
              (balasBossF[i].y + balasBossF[i].borda_y) > (nave.y - nave.borda_y))
           {
               balasBossF[i].ativo = false;
               nave.vidas--;
           }
        }
    }
}
void desenhaBalasBossF(projeteis balas[], int tamanho,Inimigos &bossF){
        for (int i=0;i<tamanho;i++)

        if (balas[i].ativo)
        {
            al_draw_rotated_bitmap(balaBossF,19,19,balas[i].x,balas[i].y,balas[i].rotacao*20.1415/180,0);
        }
}
