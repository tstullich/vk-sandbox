#!/usr/bin/bash

if ! command -v glslangValidator &> /dev/null
then
  echo "glslangValidator is not available on your system! Make sure to install it."
  echo "Alternatively you can use Google glslc."
else
  echo "Compiling shaders"
  glslangValidator -V shader.vert
  glslangValidator -V shader.frag
fi