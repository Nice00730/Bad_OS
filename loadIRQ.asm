use32
org 0x4600

start:

use32

mov edx, 0x7000;from
mov edi, 0x8000;to
xor ebx, ebx;char
call inj;

use16

  call RM;

  mov ax, 0x13;
  int 0x10;

  ;mov ah, 0x0E;
  ;mov al, 0x30;
  ;mov bl, 0x2;
  ;int 0x10;

  ;mov dh, 0x0;
  ;mov ch, 0x0;
  ;mov cl, 0x2;
  ;mov al, 0x1;//0x3F
  ;mov bx, 0x7000;
  ;call load;

  call PM;

use32

  jmp 0x8:0xF00000;


inj:

.cikl1:
  cmp edx, edi;
  je .eng1;

  mov byte [edx], bl;

  inc edx;

  jmp .cikl1;

.eng1:

  ret;


use16


RM:
  cli;

  mov eax, 0b10000;
  mov ds, eax;
  mov es, eax;
  mov fs, eax;
  mov gs, eax;
  mov ss, eax;

  mov  eax, cr0;
  and  al, 0;
  mov  cr0, eax;

  in  al, 0x92;
  and  al, 0x0;
  out 0x92, al;

  xor ax, ax;
  mov ds, ax;
  mov es, ax;
  mov fs, ax;
  mov gs, ax;
  mov ss, ax;

  mov ax, word [0xD18];
  mov sp, ax;

  call PIC1;

  lidt [0xD08];

  sti;

  ret;



PM:
  cli;

  lgdt  [0xD10];

  lidt  [0xD14];

  call PIC0;

  in  al, 0x92;
  or  al, 2;
  out 0x92, al;

  mov ax, sp;
  mov word [0xD18], ax;

  mov  eax, cr0
  or   al, 1
  mov  cr0, eax

  sti;

  ret;



load:
  push dx;

  mov dl, 0x80;
  mov ah, 0x2;

  int 0x13;

  pop dx;

  ret



PIC0:
  push ax;

  in al, 0x21; PIC-master(1) mask
  mov byte [0xD1D], al;
  in al, 0xA1; PIC-slave(2) mask
  mov byte [0xD1E], al;

  mov al, 0x11;
  out 0x20, al;

  mov al, 0x11;
  out 0xA0, al; PIC inicialization

  mov al, 0x20;
  out 0x21, al; PIC-master(1) offset

  mov al, 0x28;
  out 0xA1, al; PIC-slave(2) offset

  mov al, 0x4;
  out 0x21, al;

  mov al, 0x2;
  out 0xA1, al; PIC say they 'we here'

  mov al, 0x1;
  out 0x21, al;

  mov al, 0x1;
  out 0xA1, al; PIC to 8086 mode

  mov al, 0xFC;
  out 0x21, al;

  mov al, 0xFF; send save masks
  out 0xA1, al;

  pop ax;

  ret;



PIC1:
  push ax;

  mov al, 0x11;
  out 0x20, al;

  mov al, 0x11;
  out 0xA0, al; PIC inicialization

  mov al, 0x0;
  out 0x21, al; PIC-master(1) offset

  mov al, 0x8;
  out 0xA1, al; PIC-slave(2) offset

  mov al, 0x4;
  out 0x21, al;

  mov al, 0x2;
  out 0xA1, al; PIC say they 'we here'

  mov al, 0x1;
  out 0x21, al;

  mov al, 0x1;
  out 0xA1, al; PIC to 8086 mode

  mov al, byte [0xD1D];
  out 0x21, al; PIC-master(1) mask
  mov al, byte [0xD1E];
  out 0xA1, al; PIC-slave(2) mask

  pop ax;

  ret;
