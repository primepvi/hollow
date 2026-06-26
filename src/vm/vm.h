#ifndef HOLLOW_RUNTIME_VM_H
#define HOLLOW_RUNTIME_VM_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define HOLLOW_VM_REG_COUNT 8

typedef enum {
  OP_MOV_RI,

  OP_ADD_RR,
  OP_SUB_RR,
  OP_MUL_RR,
  OP_DIV_RR,

  OP_DUMP_R,
  OP_HALT,
} vm_opcode_t;

typedef struct {
  int16_t r[HOLLOW_VM_REG_COUNT];
  bool running;
  uint8_t *rom;
  uint16_t rom_size, pc;
} vm_t;

void vm_init(vm_t *vm, uint8_t *rom, uint16_t rom_size);
void vm_step(vm_t *vm);
void vm_run(vm_t *vm);
void vm_reset(vm_t *vm);
	    
#endif
