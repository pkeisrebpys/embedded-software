all:main.exe

run:main.exe
	./main.exe

main.exe:main.c ../common/virtual_microprocessor.c interrupt.c
	gcc -o $@ -Wall -Werror $^
