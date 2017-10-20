#ifndef __INSTR_H__
#define __INSTR_H__

#include "arena.h"

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
  STL,
  RCE,
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
  VAR,
  CEL,
} Tipo;

/* Operando */
typedef struct {
  Tipo t;
  union {
 	  int n;
 	  int ac;
 	  int v;
    node cel;
  };
} OPERANDO;

/* Instrução */
typedef struct {
  OpCode instr;
  OPERANDO op;
} INSTR;

#endif
