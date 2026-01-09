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
# Options
# --------------------------------

UV_OPTION ?= uv_mat4
DEFINES :=

ifeq ($(UV_OPTION), uv_only)
	DEFINES += -DUV
	SHADER_SRC := src/shaders/uv/*
else
	SHADER_SRC := src/shaders/uv_mat4/*
endif

# --------------------------------
# Targets
# --------------------------------
.PHONY: all clean


all: shaders
	g++ -g $(DEFINES) -std=c++20 -Weffc++ $(SRC) $(INCLUDES) -o prog -lSDL2 -ldl

shaders:
	mkdir -p /tmp/gl/shaders
	cp -r $(SHADER_SRC) /tmp/gl/shaders

uv:
	$(MAKE) UV_OPTION=uv_only all
clean:
	rm -f prog
