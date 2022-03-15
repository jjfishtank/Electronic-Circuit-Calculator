# Install script for directory: C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE FILE FILES
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/AdolcForward"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/AlignedVector3"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/ArpackSupport"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/AutoDiff"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/BVH"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/EulerAngles"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/FFT"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/IterativeSolvers"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/KroneckerProduct"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/LevenbergMarquardt"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/MatrixFunctions"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/MoreVectorization"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/MPRealSupport"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/NonLinearOptimization"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/NumericalDiff"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/OpenGLSupport"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/Polynomials"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/Skyline"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/SparseExtra"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/SpecialFunctions"
    "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/Splines"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE DIRECTORY FILES "C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/unsupported/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Jeremy/source/repos/PHYS4B/include/eigen-3.4.0/out/build/x64-Debug/unsupported/Eigen/CXX11/cmake_install.cmake")

endif()

