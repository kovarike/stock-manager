# Definindo o compilador (pode ser sobrescrito por uma variável externa)
CC ?= gcc

# Diretórios de instalação do SQLite e UUID
ifeq ($(OS),Windows_NT)
    SQLITE_INCLUDE = C:ProgramData\chocolatey\lib\SQLite\tools\include
    SQLITE_LIB = C:ProgramData\chocolatey\lib\SQLite\tools\lib
    UUID_INCLUDE = C:ProgramData\chocolatey\lib\uuid\tools\include
    UUID_LIB = C:ProgramData\chocolatey\lib\uuid\tools\lib
else
    SQLITE_INCLUDE = /usr/include
    SQLITE_LIB = /usr/lib
    UUID_INCLUDE = /usr/include
    UUID_LIB = /usr/lib
endif

# Flags de compilação
CFLAGS = -Wall -g -I$(SQLITE_INCLUDE) -I$(UUID_INCLUDE)

# Flags de link
LDFLAGS = -lsqlite3 -luuid

# Arquivos fonte e o arquivo de saída
SOURCES = app.c lib/sh.c lib/command.c client/manage.c lib/db.c lib/login.c lib/print.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = StockManager

# Regra principal: compilar e linkar tudo
all: $(EXECUTABLE)
	@echo "Compilação completa: $(EXECUTABLE)"

# Regra para compilar os arquivos objeto
%.o: %.c util/command.h util/sh.h util/global.h util/db.h util/login.h util/print.h
	@echo "Compilando $< ..."
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilando o executável
$(EXECUTABLE): $(OBJECTS)
	@echo "Linkando $@ ..."
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

# Limpeza dos arquivos .o
clean_objects:
	@echo "Limpando arquivos objeto..."
ifeq ($(OS),Windows_NT)
	del /Q $(OBJECTS)
else
	rm -f $(OBJECTS)
endif

# Limpeza do executável
clean: clean_objects
	@echo "Limpando executável..."
ifeq ($(OS),Windows_NT)
	del /Q $(EXECUTABLE)
else
	rm -f $(EXECUTABLE)
endif

.PHONY: all clean clean_objects
