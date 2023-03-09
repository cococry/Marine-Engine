LIBS=`pkg-config --libs glfw3`
INCLUDES=-Ivendor/glfw/include -Ivendor/glad/include
EXT_FILES=vendor/glad/src/glad.c
DEFINES=-DGLFW_INCLUDE_NONE


clean:
	rm -f bin/marine
debug:
	gcc -Wall -Wextra -ggdb -DMRN_DEBUG `pkg-config --cflags glfw3`  \
	$(DEFINES) $(LIBS) $(INCLUDES) $(EXT_FILES) -o bin/marine src/*.c

release:
	gcc -Wall -Wextra -Werror -O3 -ffast-math `pkg-config --cflags glfw3`  \
	$(DEFINES) $(LIBS) $(INCLUDES) $(EXT_FILES) -o bin/marine src/*.c

