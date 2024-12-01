section .data
ZERO dq 0.0

n dq 2
vec_a_addr dq 0
vec_b_addr dq 0
sdot_addr dq 0

section .text
bits 64
default rel
global x64_dotfunc

x64_dotfunc:
  ; Free up registers
  mov [n], rcx
  mov [vec_a_addr], rdx
  mov [vec_b_addr], r8
  mov [sdot_addr], sdot

  ; Initialize computation variables
  mov rax, vec_a_addr ; current vec_a address
  mov rbx, vec_b_addr ; current vec_b address
  mov rcx, [n]        ; loop counter
  vmovsd xmm2, [ZERO] ; result accumulator

compute_loop:
  vmovsd xmm0, [rax]
  vmovsd xmm1, [rbx]

  vmulsd xmm0, xmm1, xmm0
  vaddsd xmm2, xmm0, xmm2

  add rax, 8
  add rbx, 8

  loop compute_loop

  ; Store result at sdot_addr
  vmovsd [sdot_addr], xmm2 

  xor rax, rax
  ret
