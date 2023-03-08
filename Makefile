LIBS=`pkg-config --libs glfw3`
INCLUDES=-Ivendor/glfw/include -Ivendor/glad/include
EXT_FILES=vendor/glad/src/glad.c
DEFINES=-DGLFW_INCLUDE_NONE

build:
	gcc -Wall -Wextra -ggdb `pkg-config --cflags glfw3`  \
	$(DEFINES) $(LIBS) $(INCLUDES) $(EXT_FILES) -o bin/marine src/*.c
