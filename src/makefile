# Definindo o compilador (pode ser sobrescrito por uma variável externa)
CC ?= gcc

# Flags de compilação
# Inclui o diretório do SQLite no Windows e Linux (ajustar caminhos conforme necessário)
CFLAGS = -Wall -g
ifeq ($(OS),Windows_NT)
    CFLAGS += -I"C:/ProgramData/chocolatey/lib/SQLite/tools"
else
    CFLAGS += -I/usr/include
endif

# Flags de link
# Inclui a biblioteca do SQLite no Windows e Linux (ajustar caminhos conforme necessário)
LDFLAGS = -lsqlite3 -luuid
ifeq ($(OS),Windows_NT)
    LDFLAGS += -L"C:/ProgramData/chocolatey/lib/SQLite/tools/"
else
    LDFLAGS += -L/usr/lib
endif

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
