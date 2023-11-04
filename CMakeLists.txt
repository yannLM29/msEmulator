cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 20)

set (CMAKE_EXE_LINKER_FLAGS)


include_directories(include)

file(GLOB allfiles
     "src/*.cpp"
)

#add_compile_definitions(DEBUG)
set(CMAKE_BUILD_TYPE Debug)

# add the executable
add_executable(z80 ${allfiles})
