#ifndef OBJETO_H
#define OBJETO_H

enum {jogador, projetil,inimigos};
struct naveEspacial
{
    int id;
    int x;
    int y;
    int vidas;
    int velocidade;
    int borda_x;
    int borda_y;
    int pontos;
};

struct projeteis
{
    int id ;
    int x ;
    int y;
    int velocidade;
    bool ativo;
};
struct cometas {
    int id;
    int x;
    int y;
    int velocidade;
    int bordaX;
    int bordaY;
    bool ativo;

};
struct fase{
 int x ;
 int velocidade;
};

#endif // OBJETO_H
