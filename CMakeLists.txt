cmake_minimum_required (VERSION 2.6)

project (flecs C)

file(GLOB flecs_SRC "src/*.c")

include_directories("include")

add_compile_definitions(FLECS_IMPL)

add_library(flecs_static STATIC ${flecs_SRC})
add_library(flecs_shared SHARED ${flecs_SRC})

target_compile_definitions(flecs_static PRIVATE FLECS_STATIC)

if(MSVC)
    target_compile_options(flecs_static PRIVATE /W3 /WX)
    target_compile_options(flecs_shared PRIVATE /W3 /WX)
else()
    target_compile_options(flecs_static PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(flecs_shared PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include FILES_MATCHING PATTERN "*.h"
)
install(
	TARGETS flecs_static DESTINATION lib
)
install(
	TARGETS flecs_shared DESTINATION lib
)
