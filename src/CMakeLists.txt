cmake_minimum_required(VERSION 3.10)
project(StockManager)

# Definir as fontes
set(SOURCES
    app.c
    client/manage.c
    lib/sh.c
    lib/command.c
    lib/db.c
    lib/login.c
    lib/print.c
)

# Incluir diretórios e bibliotecas do SQLite
find_package(SQLite3 REQUIRED)
set(SQLite3_INCLUDE_DIR "C:/ProgramData/chocolatey/lib/SQLite/tools")
set(SQLite3_LIBRARY "C:/ProgramData/chocolatey/lib/SQLite/tools/libsqlite3.dll")



# Criar o executável no diretório build/app
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/app)

# Criar diretórios para db e log
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/db)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/log)

# Criar o executável
add_executable(StockManager ${SOURCES})

# Linkar a biblioteca SQLite
target_link_libraries(StockManager SQLite::SQLite3)

# Definir propriedades específicas para Windows
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(StockManager PRIVATE WIN32)
    set_target_properties(StockManager PROPERTIES SUFFIX ".exe")
else()
    # Definir propriedades específicas para Linux, se necessário
    target_compile_definitions(StockManager PRIVATE LINUX)
endif()

# Adicionar diretórios de inclusão, se necessário
target_include_directories(StockManager PRIVATE ${SQLite3_INCLUDE_DIRS})
