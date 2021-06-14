#include "brainfuck.h"

static struct instruction_t PROGRAM[MAX_PROGRAM];

int anlex(FILE* fp) {
    unsigned short pc = 0, jmp_pc;
    int c;

    while ((c = getc(fp)) != EOF && pc < MAX_PROGRAM) {
        switch (c) {
            case '>': 
                PROGRAM[pc].operator = OP_PONTEIRO_DIR; 
                break;
            case '<': 
                PROGRAM[pc].operator = OP_PONTEIRO_ESQ; 
                break;
            case '+':  
                PROGRAM[pc].operator = OP_INC_CELULA; 
                break;
            case '-': 
                PROGRAM[pc].operator = OP_DEC_CELULA; 
                break;
            case '.': 
                PROGRAM[pc].operator = OP_OUTPUT; 
                break;
            case ',': 
                PROGRAM[pc].operator = OP_INPUT; 
                break;
            case '[':
                PROGRAM[pc].operator = OP_PULA_FRENTE;
                if (pilha_cheia())
                    return FALHA;
                pilha_adicionar(pc);
                break;
            case ']':
                if (pilha_vazia())
                    return FALHA;
                jmp_pc = pilha_remover();
                PROGRAM[pc].operator =  OP_PULA_TRAS;
                PROGRAM[pc].operand = jmp_pc;
                PROGRAM[jmp_pc].operand = pc;
                break;
            default: 
                pc--; 
                break;
        }
        pc++;
    }

    if (!pilha_vazia() || pc == MAX_PROGRAM) {
        return FALHA;
    }
    
    PROGRAM[pc].operator = OP_FIM_PROGRAMA;
    return SUCESSO;
}

int intr() {
    unsigned short data[DATA_SIZE], pc = 0;
    unsigned int ptr = DATA_SIZE;
    while (--ptr) { 
        data[ptr] = 0; 
    }
    while (PROGRAM[pc].operator != OP_FIM_PROGRAMA && ptr < DATA_SIZE) {
        switch (PROGRAM[pc].operator) {
            case OP_PONTEIRO_DIR: 
                ptr++; 
                break;
            case OP_PONTEIRO_ESQ: 
                ptr--; 
                break;
            case OP_INC_CELULA: 
                data[ptr]++; 
                break;
            case OP_DEC_CELULA: 
                data[ptr]--; 
                break;
            case OP_OUTPUT: 
                putchar(data[ptr]); 
                break;
            case OP_INPUT: 
                data[ptr] = (unsigned int)getchar(); 
                break;
            case OP_PULA_FRENTE: 
                if(!data[ptr]) { 
                    pc = PROGRAM[pc].operand; 
                } 
                break;
            case OP_PULA_TRAS: 
                if(data[ptr]) { 
                    pc = PROGRAM[pc].operand; 
                } 
                break;
            default: 
                return FALHA;
        }
        pc++;
    }
    return ptr != DATA_SIZE ? SUCESSO : FALHA;
}

int main(int argc, const char * argv[]) {
    FILE *file;
    short status;

    if (argc != 2 || (file = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Uso: ./%s arquivo.bf\n", argv[0]);
        exit(FALHA);
    }

    if(anlex(file) == FALHA) {
        fprintf(stderr, "Error!\n");
        exit(FALHA);
    }

    status = intr();
    exit(status);
}
