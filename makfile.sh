clear

nasm -f bin -o loader0.bin loader0.asm
nasm -f bin -o loader1.bin loader1.asm
nasm -f bin -o loader2.bin loader2.asm
nasm -f bin -o ISR0.bin ISR0.asm
nasm -f bin -o ISR1.bin ISR1.asm
nasm -f bin -o ISR2.bin ISR2.asm
nasm -f bin -o ISR3.bin ISR3.asm
nasm -f bin -o prog1.bin prog1.asm
nasm -f bin -o loadIRQ.bin loadIRQ.asm

#nasm -f bin -o test_asm_file.bin test_asm_file.asm

gcc -c -g -std=gnu99 -m32 -march=i386 --no-warn -ffreestanding primc.c -o primc.o
ld --no-warn-rwx-segments -melf_i386 -static -Tprimc.ld -nostdlib --nmagic -o primc.elf primc.o
objcopy -O binary primc.elf primc.bin

gcc -c -g -std=gnu99 -m32 -march=i386 --no-warn -ffreestanding game_file.c -o game_file.o
ld --no-warn-rwx-segments -melf_i386 -static -Tgame_file.ld -nostdlib --nmagic -o game_file.elf game_file.o
objcopy -O binary game_file.elf game_file.bin

gcc -c -g -std=gnu99 -m32 -march=i386 --no-warn -ffreestanding primc_priest.c -o primc_priest.o
ld --no-warn-rwx-segments -melf_i386 -static -Tprimc_priest.ld -nostdlib --nmagic -o primc_priest.elf primc_priest.o
objcopy -O binary primc_priest.elf primc_priest.bin

gcc -c -g -std=gnu99 -m32 -march=i386 --no-warn -ffreestanding graphit.c -o graphit.o
ld --no-warn-rwx-segments -melf_i386 -static -Tgraphit.ld -nostdlib --nmagic -o graphit.elf graphit.o
objcopy -O binary graphit.elf graphit.bin

gcc -c -g -std=gnu99 -m32 -march=i386 --no-warn -ffreestanding file_redakt.c -o file_redakt.o
ld --no-warn-rwx-segments -melf_i386 -static -Tfile_redakt.ld -nostdlib --nmagic -o file_redakt.elf file_redakt.o
objcopy -O binary file_redakt.elf file_redakt.bin

gcc -c -g -std=gnu99 -m32 -march=i386 --no-warn -ffreestanding compiler.c -o compiler.o
ld --no-warn-rwx-segments -melf_i386 -static -Tfile_redakt.ld -nostdlib --nmagic -o compiler.elf compiler.o
objcopy -O binary compiler.elf compiler.bin

dd if=loader0.bin of=OS.img conv=notrunc
dd if=loader1.bin of=OS.img obs=512 seek=1
dd if=loader2.bin of=OS.img obs=512 seek=3
dd if=ISR0.bin of=OS.img obs=512 seek=4
dd if=ISR1.bin of=OS.img obs=512 seek=5
dd if=ISR2.bin of=OS.img obs=512 seek=6
dd if=ISR3.bin of=OS.img obs=512 seek=7
#dd if=loadIRQ.bin of=OS.img obs=512 seek=8
dd if=primc_priest.bin of=OS.img obs=512 seek=9
dd if=game_file.bin of=OS.img obs=512 seek=10
#dd if=graphit.bin of=OS.img obs=512 seek=23

dd if=symbtab.bin of=OS.img obs=512 seek=63
dd if=buttonlist.bin of=OS.img obs=256 seek=139
dd if=zastavka.bin of=OS.img obs=256 seek=140
dd if=anim1.bin of=OS.img obs=256 seek=141

dd if=primc.bin of=OS.img obs=512 seek=126 #63+63

dd if=graphit.bin of=OS.img obs=512 seek=189

dd if=file_redakt.bin of=OS.img obs=512 seek=252
dd if=compiler.bin of=OS.img obs=512 seek=285

#dd if=test_asm_file.bin of=OS.img obs=512 seek=315

dd if=/dev/zero of=OS.img obs=1024 seek=200 count=1

qemu-system-x86_64 -hda OS.img
