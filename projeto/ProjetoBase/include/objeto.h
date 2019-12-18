#ifndef OBJETO_H
#define OBJETO_H

enum {jogador, projetil,inimigos};
struct naveEspacial
{
    int x;
    int y;
    int vidas;
    int velocidade;
    int borda_x;
    int borda_y;
    int pontos;
    bool propulsor;
    bool escudo;
    bool desenho;
};

struct projeteis
{
    int x ;
    int y;
    int velocidade;
    bool ativo;
    int dir_x;
    int dir_y;
    int borda_x;
    int borda_y;
    int rotacao;
};
struct Inimigos {
    int vidas;
    int x;
    int y;
    int velocidade;
    int bordaX;
    int bordaY;
    int rotacao;
    bool habilidade;
    bool ativo;
    bool explosao;


};
struct astros{
 int y;
 int x ;
 int velocidade;
 bool ativo;
 double rotacao;
 int bordaX;
 int bordaY;
 bool habilidade;
};
struct Estrelas {
    int x;
    int y;
    int velocidade;
};



#endif // OBJETO_H
