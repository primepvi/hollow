#include "vm/vm.h"

int main(void) {
  // clang-format off
  uint8_t program[] = {
    OP_MOV_RI, 0, 10,
    OP_MOV_RI, 1, 20,
    OP_DUMP_R, 0,
    OP_DUMP_R, 1,
    OP_ADD_RR, 0, 1,
    OP_DUMP_R, 0,
    OP_HALT
  };
  // clang-format on

  vm_t vm = {0};
  vm_init(&vm, program, sizeof(program));
  vm_run(&vm);

  return 0;
}
