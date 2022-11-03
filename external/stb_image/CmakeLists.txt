project(stb_image)

if(${BUILD_SHARED_LIBS})
    add_library(stb_image SHARED)
else()
    add_library(stb_image STATIC)
endif()

target_include_directories(stb_image
                           PUBLIC
                           include)

target_sources(stb_image
               PRIVATE
               stb_image.cpp)