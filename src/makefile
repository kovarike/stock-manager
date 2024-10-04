CC ?= gcc

ifeq ($(CC),x86_64-w64-mingw32-gcc)
    SQLITE_INCLUDE = /usr/x86_64-w64-mingw32/include/
    LDFLAGS = -lsqlite3
    EXECUTABLE = StockManager.exe
else
    SQLITE_INCLUDE = /usr/include
    LDFLAGS = -lsqlite3 
    EXECUTABLE = StockManager
endif



# Compilation flags
CFLAGS = -Wall -g -I$(SQLITE_INCLUDE) 
# Source files and output file
SOURCES = app.c lib/sh.c lib/command.c client/manage.c lib/db.c lib/login.c lib/print.c
OBJECTS = $(SOURCES:.c=.o)

all: $(EXECUTABLE)

# Compiling the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

# Clean rules
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
