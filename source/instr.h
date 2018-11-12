// Guilherme Costa Vieira               Nº USP: 9790930
// Gabriel Kazuyuki Isomura             Nº USP: 9793673
// Victor Chiaradia Gramuglia Araujo    Nº USP: 9793756


#ifndef __INSTR_H__
#define __INSTR_H__

/* Códigos das instruções */
typedef enum {
    PUSH,
    POP,
    DUP,
    ADD,
    SUB,
    MUL,
    DIV,
    JMP,
    JIT,
    JIF,
    CALL,
    RET,
    EQ,
    GT,
    GE,
    LT,
    LE,
    NE,
    STO,
    RCL,
    END,
    PRN,
    ALC,
    FRE,
    ATR,
    MOV,
    FETCH,
    DEPO,
    ATK
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
