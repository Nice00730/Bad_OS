BITS 32
org 0x3200;
;Create pixel

;eax-смещение, ecx-цвет

start:

push ebx;

cmp eax, 0xFFFF;
jg exit;

cmp eax, 0x0;
jl exit;

mov ebx, 0xA0000;
add ebx, eax;

mov byte [ebx], cl;

exit:

mov al, 0x20;
out 0x20, al;
out 0xA0, al;

pop ebx;

iret;
