cmake_minimum_required(VERSION 3.24.4)

# Set project name
project(Darkness)

# Set the C compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "Suppresses developer warnings.")
set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.2.sdk)

# Store SDL framework locations
set(SDL2 /Library/Frameworks/SDL2.framework)
set(SDL2_image /Library/Frameworks/SDL2_image.framework)
set(SDL2_mixer /Library/Frameworks/SDL2_mixer.framework)
set(SDL2_ttf /Library/Frameworks/SDL2_ttf.framework)


# Add Lua subdirectory
#add_subdirectory(external/lua)

# Gather source files
file(GLOB SOURCES src/*.c src/*/*.c src/*/*/*.c include/*.h include/*/*.h include/*/*/*.h)

# Set the output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# Define the executable
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# Set C++ standard
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)

# Link libraries
target_link_libraries(
  ${CMAKE_PROJECT_NAME} PRIVATE
  ${SDL2}/Versions/A/SDL2
  ${SDL2_image}/Versions/A/SDL2_image
  ${SDL2_ttf}/Versions/A/SDL2_ttf
  ${SDL2_mixer}/Versions/A/SDL2_mixer
)

target_include_directories(
  ${CMAKE_PROJECT_NAME} PRIVATE
  ${SDL2}/Versions/A/Headers
  ${SDL2_image}/Versions/A/Headers
  ${SDL2_ttf}/Versions/A/Headers
  ${SDL2_mixer}/Versions/A/Headers
)

# Link Lua
#target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC lua)

# Add linker flag -Wl
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE -Wl)