all:main.exe test.exe

run:main.exe
	./main.exe

test:test.exe
	./test.exe

main.exe:main.c ../common/virtual_microprocessor.c interrupt.c
	gcc -o $@ -Wall -Werror $^ -lm

test.exe:test.c ../common/virtual_microprocessor.c interrupt.c
	gcc -o $@ -Wall -Werror $^ -lm
