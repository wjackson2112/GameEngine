project(glad)

if(${BUILD_SHARED_LIBS})
    add_library(glad SHARED)
else()
    add_library(glad STATIC)
endif()

target_include_directories(glad
                           PUBLIC
                           include)
target_sources(glad
               PRIVATE
               src/glad.c)