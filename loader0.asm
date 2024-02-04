use16
org 0x7c00
start:
  jmp entry              ;теперь CS=0, IP=0x7c00

entry:
  mov ax, cs
  mov ds, ax

.0:
  call load1;
  jmp 0x4200;

load1:
  push ax;
  push bx;
  push cx;
  push dx;

  mov dl, 0x80;
  mov dh, 0x0;
  mov ch, 0x0;
  mov cl, 0x2; смещение
  mov al, 0x2; размер
  mov bx, 0x4200; адрес
  mov ah, 0x2;

  int 0x13;

  pop dx;
  pop cx;
  pop bx;
  pop ax;

  ret;

finish:
times 0x1FE-finish+start db 0
dw 0xAA55
