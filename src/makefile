# Definição do compilador (Linux ou Windows cross-compile)
CC ?= gcc

# Verifica o compilador para definir paths e flags adequadas
ifeq ($(CC),x86_64-w64-mingw32-gcc)
    # Cross-compiling para Windows
    SQLITE_INCLUDE = /usr/x86_64-w64-mingw32/include
    LDFLAGS = -lsqlite3 -static
    EXECUTABLE = StockManager.exe
else
    # Compilação para Linux
    SQLITE_INCLUDE = /usr/include
    LDFLAGS = -lsqlite3
    EXECUTABLE = StockManager
endif

# Flags de compilação
CFLAGS = -Wall -g -I$(SQLITE_INCLUDE)

# Arquivos fonte e objetos
SOURCES = app.c lib/sh.c lib/command.c client/manage.c lib/db.c lib/login.c lib/print.c
OBJECTS = $(SOURCES:.c=.o)

# Alvo principal
all: $(EXECUTABLE)

# Regras para gerar o executável
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

# Regras para compilar os objetos
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos objeto e executável
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Definir como alvos que não são arquivos
.PHONY: all clean
