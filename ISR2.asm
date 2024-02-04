BITS 32;
org 0x3600;
;loader IRQ(2)

start:;В edx откуда, в ecx куда, в esi сколько
push eax;
push ebx;
push edi;
push esi;
;push ecx;

xor eax, eax;
xor ebx, ebx;

mov edi, edx;//откуда
;mov ebx, ecx;//куда
;xor eax, eax;
;xor ecx, ecx;
mov edx, esi;
mov esi, ecx;

loop:
cmp eax, edx;
jge stop;

mov cl, byte [edi];
mov byte [esi], cl;
;mov byte [eax], 0x0;

inc edi;
inc esi;

inc eax;

jmp loop;

stop:
mov dword [0xD00], esi;
mov dword [0xD04], edi;

mov al, 0x20;
out 0x20, al;
out 0xA0, al;

;pop ecx;
pop esi;
pop edi;
pop ebx;
pop eax;

iret;
