# Derleyici ve derleyici bayrakları
CC = gcc
CFLAGS = -Wall -g -Iinclude

# Hedef: programı derlemek
all: bin/main

# program hedefini oluşturmak için gereken bağımlılıklar
bin/main: bin/main.o bin/Habitat.o bin/Canli.o bin/Bitki.o bin/Bocek.o bin/Sinek.o bin/Pire.o
	$(CC) $(CFLAGS) -o bin/main $^

# .c dosyalarından .o dosyaları oluşturma kuralları
bin/main.o: src/main.c include/Habitat.h include/Canli.h
	$(CC) $(CFLAGS) -c src/main.c -o bin/main.o

bin/Habitat.o: src/Habitat.c include/Habitat.h include/Canli.h
	$(CC) $(CFLAGS) -c src/Habitat.c -o bin/Habitat.o

bin/Canli.o: src/Canli.c include/Canli.h
	$(CC) $(CFLAGS) -c src/Canli.c -o bin/Canli.o

bin/Bitki.o: src/Bitki.c include/Bitki.h include/Canli.h
	$(CC) $(CFLAGS) -c src/Bitki.c -o bin/Bitki.o

bin/Bocek.o: src/Bocek.c include/Bocek.h include/Canli.h
	$(CC) $(CFLAGS) -c src/Bocek.c -o bin/Bocek.o

bin/Sinek.o: src/Sinek.c include/Sinek.h include/Bocek.h
	$(CC) $(CFLAGS) -c src/Sinek.c -o bin/Sinek.o

bin/Pire.o: src/Pire.c include/Pire.h include/Bocek.h
	$(CC) $(CFLAGS) -c src/Pire.c -o bin/Pire.o

# Temizleme kuralı
clean:
	rm -f bin/*.o bin/main