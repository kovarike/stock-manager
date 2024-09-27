SOURCE_FILE="../app.c"
SERVICE_FILE="../service/sh.c"
MANAGE_FILE="../client/manage.c"
COMMAND_FILE="../service/command.c"
EXECUTABLE="app.exe"

# Verifica se os arquivos existem
if [ ! -f "$SOURCE_FILE" ] || [ ! -f "$COMMAND_FILE" ] || [ ! -f "$SERVICE_FILE" ] || [ ! -f "$MANAGE_FILE" ]; then
    echo "Um ou mais arquivos de código fonte não foram encontrados."
    exit 1
fi

echo "Verificando arquivos..."
ls -l "$SOURCE_FILE" "$COMMAND_FILE" "$SERVICE_FILE" "$MANAGE_FILE"

# Compila o código C
gcc -o "$EXECUTABLE" "$SOURCE_FILE" "$COMMAND_FILE" "$SERVICE_FILE" "$MANAGE_FILE"

# Verifica se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    echo "Compilação bem-sucedida! Executando o programa..."
    
    # # Funções para automatizar os comandos
    # (
    #     echo "manage"
    #     echo "-i"      
    #     echo "-get"        
    #     echo "-r"      
    #     echo "-z"      
    #     echo "exit"        
    #     echo "inserir"
    #     echo "inserir"
    #     echo "listar"
    #     echo "remover"
    #     echo "zerados"
    #     echo "sair"
    # ) | 

    ./"$EXECUTABLE"

else
    echo "Erro na compilação!"
fi
