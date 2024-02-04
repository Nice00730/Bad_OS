use16
org 0x4200

start:

  jmp entry;

entry:

  mov ax, cs;

  mov [inject], ax;

  mov ds, ax;

;очистить экран

  mov ah, 0x0E;
  mov al, 0x30;
  mov bl, 0x2;
  int 0x10;

.eng:

  mov dh, 0x2;
  mov ch, 0x0;
  mov cl, 0x1;
  mov al, 0x3F;//0x3F
  mov bx, 0x7000;
  call load;

  mov dh, 0x1;
  mov ch, 0x0;
  mov cl, 0x1;
  mov al, 0x11;
  mov bx, 0x1000;
  call load;

  mov dh, 0x0;
  mov ch, 0x0;
  mov cl, 0x5;
  mov al, 0x1;
  mov bx, 0x3800;
  call load;

  mov dh, 0x0;
  mov ch, 0x0;
  mov cl, 0x6;
  mov al, 0x1;
  mov bx, 0x3400;
  call load;

  mov dh, 0x0;
  mov ch, 0x0;
  mov cl, 0x7;
  mov al, 0x1;
  mov bx, 0x3600;
  call load;

  mov dh, 0x0;
  mov ch, 0x0;
  mov cl, 0x8;
  mov al, 0x1;
  mov bx, 0x3200;
  call load;

  mov dh, 0x0;
  mov ch, 0x0;
  mov cl, 0xA;
  mov al, 0x1;
  mov bx, 0x4000;
  call load;

  mov dh, 0x0;
  mov ch, 0x0;
  mov cl, 0x9;
  mov al, 0x1;
  mov bx, 0x4600;
  call load;

  mov ax, 0x13;
  int 0x10;

;Загрузить адрес и размер GDT в GDTR

  mov word [0xF000+0x20*8], 0x3400; Таблица прерываний по адресу 0xF000
  mov word [0xF000+0x20*8+2], 0b0000000000001000;
  mov word [0xF000+0x20*8+4], 0b1000111000000000;
  mov word [0xF000+0x20*8+6], 0x0;

  mov word [0xF000+0x21*8], 0x3800;
  mov word [0xF000+0x21*8+2], 0b0000000000001000;
  mov word [0xF000+0x21*8+4], 0b1000111000000000;
  mov word [0xF000+0x21*8+6], 0x0;

  mov word [0xF000+0x30*8], 0x3600;
  mov word [0xF000+0x30*8+2], 0b0000000000001000;
  mov word [0xF000+0x30*8+4], 0b1000111000000000;
  mov word [0xF000+0x30*8+6], 0x0;

  mov word [0xF000+0x31*8], 0x3200;
  mov word [0xF000+0x31*8+2], 0b0000000000001000;
  mov word [0xF000+0x31*8+4], 0b1000111000000000;
  mov word [0xF000+0x31*8+6], 0x0;

  call PM;

a32  mov edi, 0x7000;from
a32  mov esi, 0x10000;to
a32  mov ebx, 0x3F*0x200;size
a32  call peren;

a32  mov edx, 0x7000;from
a32  mov edi, 0xF000;to
a32  xor ebx, ebx;char
a32  call inj;

  call RM;

  mov dh, 0x3;
  mov ch, 0x0;
  mov cl, 0x1;
  mov al, 0x3F;//0x3F
  mov bx, 0x7000;
  call load;

  call PM;

a32  mov edi, 0x7000;from
a32  mov esi, 0xF00000;to
a32  mov ebx, 0x3F*0x200;size
a32  call peren;

a32  mov edx, 0x7000;from
a32  mov edi, 0xF000;to
a32  xor ebx, ebx;char
a32  call inj;

  call RM;

  mov dh, 0x0;
  mov ch, 0x0;
  mov cl, 0xB;
  mov al, 0x20;//0x3F
  mov bx, 0x7000;
  call load;

  call PM;

a32  mov edi, 0x7000;from
a32  mov esi, 0xF0F000;to
a32  mov ebx, 0x20*0x200;size
a32  call peren;

a32  mov edx, 0x7000;from
a32  mov edi, 0xF000;to
a32  xor ebx, ebx;char
a32  call inj;

  call RM;

  mov dh, 0x4;
  mov ch, 0x0;
  mov cl, 0x1;
  mov al, 0x21;//0x3F
  mov bx, 0x7000;
  call load;

  call PM;

a32  mov edi, 0x7000;from
a32  mov esi, 0xF1F000;to
a32  mov ebx, 0x3F*0x200;size
a32  call peren;

a32  mov edx, 0x7000;from
a32  mov edi, 0xF000;to
a32  xor ebx, ebx;char
a32  call inj;

  call RM;

  mov dh, 0x4;
  mov ch, 0x0;
  mov cl, 0x22;
  mov al, 0x1D;//0x3F
  mov bx, 0x7000;
  call load;

  call PM;

a32  mov edi, 0x7000;from
a32  mov esi, 0xF2A000;to
a32  mov ebx, 0x3F*0x200;size
a32  call peren;

a32  mov edx, 0x7000;from
a32  mov edi, 0xF000;to
a32  xor ebx, ebx;char
a32  call inj;

;  mov ax, ldtr1;
;  mov word [0xD08], ax;
;  mov ax, gdt;
;  mov word [0xD0C], ax;
;  mov ax, gdtr;
;  mov word [0xD10], ax;
;  mov ax, ldtr;
;  mov word [0xD14], ax;
;  mov ax, [inject];
;  mov word [0xD18], ax;
;  mov al, [masc1];
;  mov byte [0xD1D], al;
;  mov al, [masc2];
;  mov byte [0xD1E], al;


;Загрузить в CS:EIP точку входа в защищенный режим
  jmp 0x8:0x4000; это не адрес, а номер в таблице дескрипторов; последние три бита(после еденички) это: самый левый глобальная/локальная таблица, остальные д

peren:

a32 push edx;
a32 xor edx, edx;

.cikl1:
a32  cmp edx, ebx;
a32  je .eng1;

a32  mov al, byte [edi];
a32  mov byte [esi], al;

a32  inc edi;
a32  inc esi;
a32  inc edx;

a32  jmp .cikl1;

.eng1:

a32 pop edx;

a32 ret;


inj:

.cikl1:
a32  cmp edx, edi;
a32  je .eng1;

a32  mov byte [edx], bl;

a32  inc edx;

a32  jmp .cikl1;

.eng1:

a32 ret;



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

  mov ax, [inject];
  mov sp, ax;

  call PIC1;

  lidt [ldtr1];

  sti;

  ret;

PM:
  cli;

  lgdt  [gdtr];

  lidt  [ldtr];

  call PIC0;

  in  al, 0x92;
  or  al, 2;
  out 0x92, al;

  mov ax, sp;
  mov [inject], ax;

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

  ret;




PIC0:
  push ax;

  in al, 0x21; PIC-master(1) mask
  mov byte [masc1], al;
  in al, 0xA1; PIC-slave(2) mask
  mov byte [masc2], al;

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

  mov al, byte [masc1];
  out 0x21, al; PIC-master(1) mask
  mov al, byte [masc2];
  out 0xA1, al; PIC-slave(2) mask

  pop ax;

  ret;




  inject dw 0x0;

  masc1 db 0x0;
  masc2 db 0x0;

;Глобальная таблица дескрипторов.
;Нулевой дескриптор использовать нельзя!

ldtr1:
  dw  0x3FF;
  dd 0x0;

gdt:
  dq 0;
  db  0xFF, 0xFF, 0x00, 0x00, 0x00, 10011010b, 11000000b, 0x00; Идёт с лева на право в общем, байт доступа читается с лева на право, в паре флаг/ограничение первый - флаг
  db  0xFF, 0xFF, 0x00, 0x00, 0x00, 10010010b, 00000000b, 0x00;
  ;db  0xFF, 0xFF, 0x00, 0x00, 0x00, 10010010b, 00000000b, 0x00;
  ;db  0x11, 0x00, 0x00, 0x00, 0xFF, 11111010b, 11000000b, 0xFF;

gdt_size  equ $ - gdt

;данные, загружаемые в регистр GDTR
gdtr:
  dw  gdt_size - 1
  ;dw  gdt_size
  dd  gdt

ldtr:
  dw  0x18F;
  dd 0xF000;
  ;dd  ldt;
  ;dd  0x123123;
