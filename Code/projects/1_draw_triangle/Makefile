###############################################################################
# Makefile
###############################################################################

# --------------------------------
# OpenGL / GLAD
# --------------------------------
OPENGL_SRC = ../../third_party/glad/src/glad.c
OPENGL_HDR = ../../third_party/glad/include

# --------------------------------
# VBO selection
# --------------------------------
VBO_SRC :=
VBO_HDR :=

ifeq ($(VBO_OPTION), single)

  VBO_SRC = src/gl_examples/vbo/1_single_vbo/*.cpp
  VBO_HDR = src/gl_examples/vbo/1_single_vbo

else ifeq ($(VBO_OPTION), interleave)

  VBO_SRC = src/gl_examples/vbo/2_interleaved_vbo/*.cpp
  VBO_HDR = src/gl_examples/vbo/2_interleaved_vbo

else ifeq ($(VBO_OPTION), multiple)

  VBO_SRC = src/gl_examples/vbo/3_multiple_vbos/*.cpp
  VBO_HDR = src/gl_examples/vbo/3_multiple_vbos

else ifeq ($(VBO_OPTION), ibo)

  VBO_SRC = src/gl_examples/ibo/*.cpp
  VBO_HDR = src/gl_examples/ibo

endif

# --------------------------------
# Sources / Includes
# --------------------------------
SRC = src/app/*.cpp \
      src/gl/*.cpp  \
      $(OPENGL_SRC) \
      $(VBO_SRC)

INCLUDES = -I. \
           -Isrc/gl/ \
           -I$(OPENGL_HDR) \
           -I$(VBO_HDR)

# --------------------------------
# Targets
# --------------------------------
.PHONY: help all clean

help:
	@echo "Usage: make vbo-[single|interleave|multiple|ibo]"
	@echo
	@echo "Targets:"
	@echo " * vbo-single"
	@echo " * vbo-interleave"
	@echo " * vbo-multiple"
	@echo " * vbo-ibo"

vbo-%:
	$(MAKE) VBO_OPTION=$* all

all:
	@if [ -z "$(VBO_SRC)" ]; then \
		echo "Error: VBO_OPTION not set or invalid"; \
		echo "Use: make vbo-[single|interleave|multiple]"; \
		exit 1; \
	fi
	mkdir -p /tmp/gl/shaders
	cp -r ./src/shaders/* /tmp/gl/shaders/
	g++ -g -std=c++20 -Weffc++ $(SRC) $(INCLUDES) -o prog -lSDL2 -ldl

clean:
	rm -f prog
