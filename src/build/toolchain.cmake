# toolchain.cmake

# Especificar o nome do sistema
set(CMAKE_SYSTEM_NAME Windows)

# Especificar o compilador cruzado
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

# Especificar o caminho da ferramenta
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

# Ajustar os diretórios de inclusão
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
