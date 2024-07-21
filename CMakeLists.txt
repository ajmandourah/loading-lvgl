# cmake_minimum_required(VERSION 3.10)
# project(lvgl)
#
# set(CMAKE_C_STANDARD 11)#C99 # lvgl officially support C99 and above
# set(CMAKE_CXX_STANDARD 11)#C17
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#
# add_subdirectory(lvgl)
# target_include_directories(lvgl PUBLIC ${PROJECT_SOURCE_DIR})
#
# add_executable(main main.c mouse_cursor_icon.c)
#
# include(${CMAKE_CURRENT_LIST_DIR}/lvgl/tests/FindLibDRM.cmake)
# include_directories(${Libdrm_INCLUDE_DIRS})
#
# find_package(SDL2)
# find_package(SDL2_image)
# include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
#
# target_link_libraries(main lvgl lvgl::examples lvgl::demos lvgl::thorvg ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${Libdrm_LIBRARIES} m pthread)
# add_custom_target (run COMMAND ${EXECUTABLE_OUTPUT_PATH}/main DEPENDS main)

cmake_minimum_required(VERSION 3.15)
set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

#cross-compilation toolchain configuration
set(TOOLCHAIN_PATH /home/ladis/minulli_cfw/output/h700/host)
set(CMAKE_CROSSCOMPILING true)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
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

