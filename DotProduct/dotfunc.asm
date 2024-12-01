section .data
ZERO dq 0.0

section .text
bits 64
default rel
global x64dotfunc

x64dotfunc:
  ; n    -> rcx
  ; a    -> rdx
  ; b    -> r8
  ; sdot -> r9

  movsd xmm2, [ZERO]  ; result accumulator

compute_loop:
  movsd xmm0, [rdx]
  movsd xmm1, [r8]

  mulsd xmm0, xmm1
  addsd xmm2, xmm0

  add rdx, 8
  add r8, 8

  loop compute_loop

  ; Store result at sdot address 
  movsd [r9], xmm2

  xor rax, rax
  ret
