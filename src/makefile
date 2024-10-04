# Definindo o compilador (pode ser sobrescrito por uma variável externa)
CC ?= gcc

# Incluindo caminhos dependendo do sistema
ifeq ($(CC),x86_64-w64-mingw32-gcc)
    SQLITE_INCLUDE = /usr/x86_64-w64-mingw32/include
    # UUID_INCLUDE = /usr/x86_64-w64-mingw32/include/uuid
	LDFLAGS = -lsqlite3 -luuid 
else
    SQLITE_INCLUDE = /usr/include
    # UUID_INCLUDE = /usr/include
	LDFLAGS = -lsqlite3 -luuid
endif

# Flags de compilação
CFLAGS = -Wall -g -I$(SQLITE_INCLUDE) -I$(UUID_INCLUDE)

# Flags de link


# Arquivos fonte e o arquivo de saída
SOURCES = app.c lib/sh.c lib/command.c client/manage.c lib/db.c lib/login.c lib/print.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = StockManager

all: $(EXECUTABLE)
	@echo "Compilação completa: $(EXECUTABLE)"

# Regra para compilar os arquivos objeto
%.o: %.c
	@echo "Compilando $< ..."
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilando o executável
$(EXECUTABLE): $(OBJECTS)
	@echo "Linkando $@ ..."
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

# Limpeza dos arquivos .o
clean_objects:
	@echo "Limpando arquivos objeto..."
	rm -f $(OBJECTS)

# Limpeza do executável
clean: clean_objects
	@echo "Limpando executável..."
	rm -f $(EXECUTABLE)

.PHONY: all clean clean_objects
