CPP_FILES := src/*.cpp 
OBJ_FILES := $(addprefix ,$(notdir $(CPP_FILES:.cpp=.o)))
CC_FLAGS = -g -stdlib=libc++ -Wall -std=c++11 -Werror -O3
INCLUDE = -Iincludes -Iincludes/flux -I/Library/Frameworks/SDL.framework/Headers -I/Library/Frameworks/SDL_image.framework/Headers
FRAMEWORKS = -framework SDL_image -framework OpenGL -framework SDL -framework Cocoa -framework AppKit
EM_FLAGS = -stdlib=libc++ -std=c++11 -O2 -g -s ASM_JS=1
LIBS = -Llibs -L/opt/local/lib -lSDLmain -lFlux

.PHONY:onelight

onelight:
	clang++ $(CC_FLAGS) $(INCLUDE) -c $(CPP_FILES)
	clang++ -o onelight $(FRAMEWORKS) -stdlib=libc++ $(OBJ_FILES) $(LIBS)

emscripten:
	em++ $(EM_FLAGS) $(LIBS) $(INCLUDE) libs/flux.bc *.cpp -o onelight.html --preload-file .

clean:
	rm -f onelight
	rm -f *.o
	rm -f onelight.html
