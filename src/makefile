# Definindo o compilador (pode ser sobrescrito por uma variável externa)
CC ?= gcc

# Variáveis de diretórios de inclusão
ifeq ($(OS),Windows_NT)
    SQLITE_INCLUDE = /usr/x86_64-w64-mingw32/include
    UUID_INCLUDE = /usr/x86_64-w64-mingw32/include
else
    SQLITE_INCLUDE = /usr/include
    UUID_INCLUDE = /usr/include
endif

# Flags de compilação
CFLAGS = -Wall -g -I$(SQLITE_INCLUDE) -I$(UUID_INCLUDE)

# Flags de link
LDFLAGS = -lsqlite3 -luuid

# Arquivos fonte e o arquivo de saída
SOURCES = app.c lib/sh.c lib/command.c client/manage.c lib/db.c lib/login.c lib/print.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = StockManager

# Detecta o sistema operacional
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    TARGET = $(EXECUTABLE)
else ifeq ($(OS),Windows_NT)
    TARGET = $(EXECUTABLE).exe
    CC = x86_64-w64-mingw32-gcc
    # Ajustar os caminhos de inclusão e link para Windows se necessário
endif

# Regra principal: compilar e linkar tudo
all: $(TARGET)
	@echo "Compilação completa: $(TARGET)"

# Regra para compilar os arquivos objeto
%.o: %.c
	@echo "Compilando $< ..."
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilando o executável
$(TARGET): $(OBJECTS)
	@echo "Linkando $@ ..."
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Limpeza dos arquivos .o
clean_objects:
	@echo "Limpando arquivos objeto..."
	rm -f $(OBJECTS)

# Limpeza do executável
clean: clean_objects
	@echo "Limpando executável..."
	rm -f $(TARGET)

.PHONY: all clean clean_objects
