COMPILE_FILES="main.c"
LINKER_FLAGS="-lraylib -lGL -lm -lpthread -ldl -lrt -lX11"
gcc -DDEBUG -g -Wall -Wextra -Werror -std=gnu99 -Wvla -pedantic $COMPILE_FILES -o main $LINKER_FLAGS
