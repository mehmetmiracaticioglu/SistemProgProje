all: exe
exe:
	gcc -c main.c fields.c jval.c jrb.c
	gcc -o kripto main.o fields.o jval.o jrb.o
run:
	./kripto -d giris_metin decripted.txt
	./kripto -e decripted.txt encripted.txt
clean:
	rm *.o kripto