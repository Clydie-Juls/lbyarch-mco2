section .data
ZERO dq 0.0

n dq 0
vec_a_addr dq 0
vec_b_addr dq 0
sdot_addr dq 0

section .text
bits 64
default rel
global x64_dotfunc

x64_dotfunc:
  mov [n], rcx
  mov [vec_a_addr], rdx
  mov [vec_b_addr], r8
  mov [sdot_addr], sdot

  mov rax, vec_a_addr
  mov rbx, vec_b_addr
  mov rcx, [n]
  xor rdx, rdx
  vmovsd xmm2, ZERO

compute_loop:
  vmovsd xmm0, [rax]
  vmovsd xmm1, [rbx]

  vmulsd xmm0, xmm1, xmm0
  vaddsd xmm2, xmm0, xmm2

  inc rax
  inc rbx

  loop compute_loop

  vmovsd [sdot_addr], xmm2 

  xor rax, rax
  ret
