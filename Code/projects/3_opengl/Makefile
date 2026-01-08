###############################################################################
# Makefile
###############################################################################

# --------------------------------
# OpenGL / GLAD
# --------------------------------
OPENGL_SRC = ../../third_party/glad/src/glad.c
OPENGL_HDR = ../../third_party/glad/include

# --------------------------------
# OpenGL Math 
# --------------------------------

GLM_HDR = ../../third_party/glm-master/


# --------------------------------
# Sources / Includes
# --------------------------------
SRC = src/app/*.cpp \
      src/gl/*.cpp  \
      src/gl/gl_objects/*.cpp  \
      $(OPENGL_SRC) \
      $(VBO_SRC)


# Disable warnings for GLM only

INCLUDES = -Isrc/app/ \
           -Isrc/gl/ \
           -Isrc/gl/gl_objects/ \
           -I$(OPENGL_HDR) \
           -I$(GLM_HDR) \
		-isystem $(GLM_HDR)

# --------------------------------
# Targets
# --------------------------------
.PHONY: all clean

all:
	mkdir -p /tmp/gl/shaders
	cp -r ./src/shaders/* /tmp/gl/shaders/
	g++ -g -std=c++20 -Weffc++ $(SRC) $(INCLUDES) -o prog -lSDL2 -ldl

clean:
	rm -f prog
