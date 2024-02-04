BITS 32;
org 0x3400;
;timer IRQ(1)

start:

push eax;

mov eax, dword [0xFE7];

add eax, 0x1;

cmp eax, 0xFFFFFFFF;
je .obnull;

mov dword [0xFE7], eax;

jmp stop;

.obnull:

mov dword [0xFE7], 0x0;

stop:

mov al, 0x20;
out 0x20, al;
;out 0xA0, al;

pop eax;

iret;
