# Definindo o compilador (pode ser sobrescrito por uma variável externa)
CC ?= gcc

# Flags de compilação
CFLAGS = -Wall -g

# Flags de link
LDFLAGS = -lsqlite3 -luuid

# Arquivos fonte e o arquivo de saída
SOURCES = app.c lib/sh.c lib/command.c client/manage.c lib/db.c lib/login.c lib/print.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = StockManager

# Regra principal: compilar e linkar tudo
all: $(EXECUTABLE) clean_objects

# Regra para compilar os arquivos objeto
%.o: %.c util/command.h util/sh.h util/global.h util/db.h util/login.h util/print.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilando o executável
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

# Limpeza dos arquivos .o
clean_objects:
	rm -f $(OBJECTS)

# Limpeza do executável
clean:
	rm -f $(EXECUTABLE)

.PHONY: all clean clean_objects
