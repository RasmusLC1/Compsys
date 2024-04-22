riscv32-unknown-elf-gcc -march=rv32im -mabi=ilp32 -O1 test.s -static -nostartfiles -nostdlib -o test.riscv

riscv32-unknown-elf-objdump -s -w test.riscv > test.dis


riscv32-unknown-elf-objdump -S test.riscv >> test.dis


VALGRIND

valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./executable exampleParam1