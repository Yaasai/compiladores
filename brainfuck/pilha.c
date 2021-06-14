#include "brainfuck.h"

static unsigned short pilha[MAX_PILHA];
static unsigned int posicao_pilha = 0;

void pilha_adicionar(unsigned short item) {
    pilha[posicao_pilha++] = item;
}

unsigned short pilha_remover() {
    return pilha[--posicao_pilha];
}

int pilha_vazia() {
    return posicao_pilha == 0;
}

int pilha_cheia() {
    return posicao_pilha == MAX_PILHA;
}
