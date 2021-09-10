bits 64
section .text

global out_port
out_port:
  mov dx, di
  mov eax, esi
  out dx, eax
  ret

global in_port
in_port:
  mov dx, di
  in eax, dx
  ret