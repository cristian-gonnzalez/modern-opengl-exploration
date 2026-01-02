
OPENGL_SRC =../../third_party/glad/src/glad.c
OPENGL_INCLUDE =../../third_party/glad/include

SRC = c_style_version/main.cpp \
      $(OPENGL_SRC)
INCLUDE= -I$(OPENGL_INCLUDE)


all:
	g++ -std=c++20 $(SRC) $(INCLUDE) -o prog -lSDL2 -ldl

clean:
	rm -f prog