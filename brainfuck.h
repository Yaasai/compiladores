// Header file - Trabalho de Compiladores
// Ciência da Computação - Senac Santo Amaro
// @author Lucas Gomes Santana

#ifndef __brainfuck_h
#define __brainfuck_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    OP_FIM_PROGRAMA,
    OP_PONTEIRO_DIR,
    OP_PONTEIRO_ESQ,
    OP_INC_CELULA,
    OP_DEC_CELULA,
    OP_OUTPUT, 
    OP_INPUT,
    OP_PULA_FRENTE,
    OP_PULA_TRAS
};

enum bool { false, true } bool;

#define SUCESSO 0
#define FALHA 1

#define MAX_PROGRAM 4096
#define MAX_PILHA 512
#define DATA_SIZE 65535


struct instruction_t {
    unsigned short operator;
    unsigned short operand;
};

void pilha_adicionar(unsigned short item);
unsigned short pilha_remover();
int pilha_vazia();
int pilha_cheia();

#endif