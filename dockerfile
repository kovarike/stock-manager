# Use uma imagem base mais recente do Debian
FROM debian:bullseye AS build-linux

# Instale o compilador GCC
RUN apt-get update && apt-get install -y gcc

# Copie o código fonte
COPY . /src

# Defina o diretório de trabalho
WORKDIR /src

# Compile para Linux
RUN gcc -o App_StockManager src/service/sh.c src/service/command.c src/client/manage.c src/app.c

# Stage para compilação do Windows
FROM debian:bullseye AS build-windows

# Instale o compilador MinGW
RUN apt-get update && apt-get install -y mingw-w64

# Copie o código fonte do estágio anterior
COPY --from=build-linux /src /src


# Defina o diretório de trabalho
WORKDIR /src

# Compile para Windows
RUN x86_64-w64-mingw32-gcc -o App_StockManager.exe  src/service/sh.c src/service/command.c src/client/manage.c src/app.c
