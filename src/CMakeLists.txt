cmake_minimum_required(VERSION 3.10)
project(StockManager)


if (WIN32)
    set(SQLite3_INCLUDE_DIR "/usr/x86_64-w64-mingw32/include")
    set(SQLite3_SYSROOT_INCLUDE_DIR "/usr/x86_64-w64-mingw32/sys-root/mingw/include")
    set(SQLite3_LIBRARY "/usr/x86_64-w64-mingw32/lib/libsqlite3.a")
    # set(SQLite3_INCLUDE_DIR "/usr/include")
    # set(SQLite3_LIBRARY "/usr/lib/x86_64-linux-gnu/libsqlite3.so")
    # set(SQLite3_INCLUDE_DIR "/usr/x86_64-w64-mingw32/include")
    # set(SQLite3_LIBRARY "/usr/x86_64-w64-mingw32/lib/libsqlite3.a")
    # Adicione o caminho do MinGW
    include_directories("/usr/x86_64-w64-mingw32/include")
    
else()
    
    set(SQLite3_INCLUDE_DIR "/usr/include")
    # set(SQLite3_LIBRARY "/usr/lib/x86_64-linux-gnu/libsqlite3.so")

    set(SQLite3_LIBRARY "/usr/lib64/libsqlite3.so")
    
    
endif()



find_package(SQLite3 REQUIRED)
include_directories(${SQLite3_INCLUDE_DIRS})

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




# Criar o executável no diretório build/app
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/app)

# Criar diretórios para db e log
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/db)
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/log)

# Criar o executável
add_executable(StockManager ${SOURCES})

# Linkar a biblioteca SQLite
target_link_libraries(StockManager PRIVATE SQLite::SQLite3)

# Definir propriedades específicas para Windows
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(StockManager PRIVATE WIN32)
    set_target_properties(StockManager PROPERTIES SUFFIX ".exe")
    target_link_libraries(StockManager PRIVATE SQLite::SQLite3)

else()
    target_compile_definitions(StockManager PRIVATE LINUX)
endif()

# Incluir diretórios de inclusão
target_include_directories(StockManager PRIVATE ${SQLite3_INCLUDE_DIRS})  # Use esta variável


