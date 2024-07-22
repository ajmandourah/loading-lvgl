cmake_minimum_required(VERSION 3.15)

set(CMAKE_SYSTEM_NAME aarch64)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(LV_CONF_BUILD_DISABLE_EXAMPLES 1)
set(LV_CONF_BUILD_DISABLE_DEMOS 1)

#cross-compilation toolchain configuration

#set the path to your toolchain here. 
set(TOOLCHAIN_PATH /home/ladis/minulli_cfw/output/h700/host)

set(CMAKE_CROSSCOMPILING true)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
#set the naming scheme of your toolchain/compiler
set(CMAKE_LIBRARY_ARCHITECTURE aarch64-buildroot-linux-gnu)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/bin/${CMAKE_LIBRARY_ARCHITECTURE}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/bin/${CMAKE_LIBRARY_ARCHITECTURE}-g++)
set(CMAKE_LINKER ${TOOLCHAIN_PATH}/bin/${CMAKE_LIBRARY_ARCHITECTURE}-ld)

project(progressbar)


add_subdirectory(lvgl)
target_include_directories(lvgl PUBLIC ${PROJECT_SOURCE_DIR})
# set(SDL_FOLDER sdl2-dev-rpi64)
# set(CMAKE_FIND_ROOT_PATH ${SDL_FOLDER})
set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PATH}/bin/ ${SDL_FOLDER})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


# set(CMAKE_BUILD_RPATH "${SDL_FOLDER}/include")
# set(CMAKE_INSTALL_RPATH ${CMAKE_BUILD_RPATH})

include_directories(
    ${PROJECT_SOURCE_DIR}
    # ${PROJECT_SOURCE_DIR}/${SDL_FOLDER}/include
    ${PROJECT_SOURCE_DIR}/lvgl
#    ${PROJECT_SOURCE_DIR}/lv_drivers
    ${PROJECT_SOURCE_DIR}/ui
)


# FILE(GLOB_RECURSE LVGL_Sources CONFIGURE_DEPENDS ${SDL_FOLDER})
FILE(GLOB_RECURSE LVGL_Sources CONFIGURE_DEPENDS lvgl/*.c)
#FILE(GLOB_RECURSE LV_DRIVERS_Sources CONFIGURE_DEPENDS lv_drivers/*.c)
FILE(GLOB_RECURSE UI_Sources CONFIGURE_DEPENDS ui/*.c ui/*.cpp)

add_executable(${PROJECT_NAME} main.c ${LVGL_Sources} ${LV_DRIVERS_Sources} ${UI_Sources})

# target_link_libraries(${PROJECT_NAME} -L"${PROJECT_SOURCE_DIR}/${SDL_FOLDER}/lib" SDL2 )
target_link_libraries(${PROJECT_NAME} lvgl lvgl::thorvg)

# Define the second executable with RG28XX
add_executable(${PROJECT_NAME}_rg28xx main.c ${LVGL_Sources} ${UI_Sources})
target_compile_definitions(${PROJECT_NAME}_rg28xx PRIVATE RG28XX)
target_link_libraries(${PROJECT_NAME}_rg28xx lvgl lvgl::thorvg)