# Definindo o compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -g

# Arquivos fonte e o arquivo de saída
SOURCES = app.c lib/sh.c lib/command.c client/manage.c
OBJECTS = lib/sh.o lib/command.o client/manage.o app.o
EXECUTABLE = app.exe

# Regra principal: compilar e linkar tudo
all: $(EXECUTABLE)

# Regra para compilar o arquivo objeto
app.o: app.c util/global.h util/sh.h
	$(CC) $(CFLAGS) -c -o $@ $<

lib/sh.o: lib/sh.c util/command.h util/sh.h util/global.h
	$(CC) $(CFLAGS) -c -o $@ $<

lib/command.o: lib/command.c util/command.h util/global.h
	$(CC) $(CFLAGS) -c -o $@ $<

client/manage.o: client/manage.c util/command.h util/global.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilando o executável
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

# Limpeza dos arquivos .o e do executável
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

.PHONY: all clean


