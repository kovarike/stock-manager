# Definindo o compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -g

# Arquivos fonte e o arquivo de saída
SOURCES = app.c service/sh.c service/command.c client/manage.c
OBJECTS = service/sh.o service/command.o client/manage.o app.o
EXECUTABLE = app

# Regra principal: compilar e linkar tudo
all: $(EXECUTABLE)

# Regra para compilar o arquivo objeto
app.o: app.c util/command.h util/sh.h
	$(CC) $(CFLAGS) -c -o $@ $<

service/sh.o: service/sh.c util/command.h util/sh.h
	$(CC) $(CFLAGS) -c -o $@ $<

service/command.o: service/command.c util/command.h util/sh.h
	$(CC) $(CFLAGS) -c -o $@ $<

client/manage.o: client/manage.c util/command.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilando o executável
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

# Limpeza dos arquivos .o e do executável
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

.PHONY: all clean


# # Definindo o compilador
# CC = gcc

# # Flags de compilação
# CFLAGS = -Wall -g

# # Arquivos fonte e o arquivo de saída
# SOURCES = app.c service/sh.c service/command.c client/manage.c
# OBJECTS = service/sh.o service/command.o client/manage.o app.o
# EXECUTABLE = app

# # Regra principal: compilar e linkar tudo
# all: $(EXECUTABLE)

# # Regra para compilar o arquivo objeto
# %.o: %.c util/command.h util/sh.h
# 	$(CC) $(CFLAGS) -c -o $@ $<

# # Compilando o executável
# $(EXECUTABLE): $(OBJECTS)
# 	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

# # Limpeza dos arquivos .o e do executável
# clean:
# 	rm -f $(EXECUTABLE) $(OBJECTS)

# .PHONY: all clean
