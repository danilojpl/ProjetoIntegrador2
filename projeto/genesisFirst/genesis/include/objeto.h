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

#endif // OBJETO_H
