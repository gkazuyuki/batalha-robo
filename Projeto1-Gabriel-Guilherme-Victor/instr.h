// Guilherme Costa Vieira               Nº USP: 9790930
// Gabriel Kazuyuki Isomura             Nº USP: 9793673
// Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756


#ifndef __INSTR_H__
#define __INSTR_H__

/* Códigos das instruções */
typedef enum {
    PUSH, // 0
    POP, // 1
    DUP, // 2
    ADD, // 3
    SUB, // 4
    MUL, // 5
    DIV, // 6
    JMP, // 7
    JIT, // 8
    JIF, // 9
    CALL, // 10
    RET, // 11
    EQ, // 12
    GT, // 13
    GE, // 14
    LT, // 15
    LE, // 16
    NE, // 17
    STO, // 18
    RCL, // 19
    END, // 20
    PRN, // 21
    STL, // 22
    RCE, // 23
    ALC, // 24
    FRE, // 25
    ATR, // 26
    MOV, // 27
    FETCH, // 28
    DEPO, // 29
    ATK // 30
} OpCode;

/* Tipos dos operandos */
typedef enum {
    NUM,
    ACAO,
} Tipo;

/* Operando */
typedef struct {
    Tipo t;
    union {
        int n;
        int ac;
    };
} OPERANDO;

/* Instrução */
typedef struct {
    OpCode instr;
    int op;
} INSTR;

#endif
