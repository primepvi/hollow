#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

inline static uint8_t vm_fetch(vm_t *vm) {
  return vm->rom[vm->pc++];
}

inline static void vm_mov_ri(vm_t *vm) {
    uint8_t r = vm_fetch(vm);
    uint8_t i = vm_fetch(vm);
    vm->r[r] = i;
}

inline static void vm_rr_binary_op(vm_t *vm, uint8_t op) {
  uint8_t dst = vm_fetch(vm);
  uint8_t src = vm_fetch(vm);

  switch (op) {
    case OP_ADD_RR: 
      vm->r[dst] = vm->r[dst] + vm->r[src];
      break;
  case OP_SUB_RR:
      vm->r[dst] = vm->r[dst] - vm->r[src];
      break;
  case OP_MUL_RR:
      vm->r[dst] = vm->r[dst] * vm->r[src];
      break;
  case OP_DIV_RR:
      vm->r[dst] = vm->r[dst] / vm->r[src];
      break;
  default:
    fprintf(stderr, "(hollow_err) Invalid rr binary opcode has received: %d\n", op);
  }
}

inline static void vm_dump_r(vm_t *vm) {
  uint8_t src = vm_fetch(vm);
  printf("(hollow_dump) R%d -> %d\n", src, vm->r[src]);
}

inline static void vm_halt(vm_t *vm) {
  vm->running = false;
}

void vm_init(vm_t *vm, uint8_t *rom, uint16_t rom_size) {
  vm->running = true;
  vm->rom = rom;
  vm->rom_size = rom_size;
  vm->pc = 0;

  for (size_t i = 0; i < HOLLOW_VM_REG_COUNT; i++)
    vm->r[i] = 0;
}

void vm_step(vm_t *vm) {
  uint8_t op = vm_fetch(vm);

  switch (op) {
  case OP_MOV_RI: 
    vm_mov_ri(vm);
    break;
  case OP_ADD_RR:
  case OP_SUB_RR:
  case OP_MUL_RR:
  case OP_DIV_RR:
    vm_rr_binary_op(vm, op);
    break;
  case OP_DUMP_R:
    vm_dump_r(vm);
    break;
  case OP_HALT:
    vm_halt(vm);
    break;
  default:
    fprintf(stderr, "(hollow_err) Invalid opcode has received: %d\n", op);
  }
}

void vm_run(vm_t *vm) {
  while (vm->running)
    vm_step(vm);
}

void vm_reset(vm_t *vm) {
  vm->pc = 0;
  vm->running = true;

  for (size_t i = 0; i < HOLLOW_VM_REG_COUNT; i++)
    vm->r[i] = 0;

}
