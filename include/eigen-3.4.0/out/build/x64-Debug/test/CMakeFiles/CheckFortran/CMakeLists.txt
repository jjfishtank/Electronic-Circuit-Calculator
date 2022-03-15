cmake_minimum_required(VERSION 3.20.21032501-MSVC_2)
project(CheckFortran Fortran)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/result.cmake"
  "set(CMAKE_Fortran_COMPILER \"${CMAKE_Fortran_COMPILER}\")\n"
  "\n"
  )