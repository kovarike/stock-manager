# Definindo o compilador (pode ser sobrescrito por uma variável externa)
CC ?= gcc

# Diretório do vcpkg
VCPKG_PATH = "D:/a/stock-manager/stock-manager/vcpkg"

# Flags de compilação
CFLAGS = -Wall -g
ifeq ($(OS),Windows_NT)
    CFLAGS += -I$(VCPKG_PATH)/installed/x64-windows/include
else
    CFLAGS += -I/usr/include
endif

# Flags de link
LDFLAGS = -lsqlite3 -luuid
ifeq ($(OS),Windows_NT)
    LDFLAGS += -L$(VCPKG_PATH)/installed/x64-windows/lib
else
    LDFLAGS += -L/usr/lib
endif

# Arquivos fonte e o arquivo de saída
SOURCES = app.c lib/sh.c lib/command.c client/manage.c lib/db.c lib/login.c lib/print.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = StockManager

# Regra principal: compilar e linkar tudo
all: $(EXECUTABLE)

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
clean: clean_objects
	rm -f $(EXECUTABLE)

.PHONY: all clean clean_objects
