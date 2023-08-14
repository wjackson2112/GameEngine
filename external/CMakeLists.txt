if(EMSCRIPTEN)
    target_link_libraries(GameEngine
            glm
            stb_image)
    # GLM
    add_subdirectory(glm)
    add_subdirectory(stb_image)
    #    set(FT_DISABLE_HARFBUZZ ON CACHE BOOL "" FORCE)
    #    add_subdirectory(freetype-2.12.1)
else()
find_package(OpenGL REQUIRED)
target_link_libraries(GameEngine
        OpenGL::GL
#        assimp
        glad
        glfw
        glm
        stb_image
        OpenAL
        freetype)

# Assimp
#set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
#add_subdirectory(assimp-5.2.4)

# GLAD
add_subdirectory(glad)

# GLFW
## Disable Docs,Tests,Examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw-3.3.2)

# GLM
add_subdirectory(glm)

# STB_IMAGE
add_subdirectory(stb_image)

# OpenAL
add_subdirectory(openal-soft-1.22.2)

# FreeType
set(FT_DISABLE_HARFBUZZ ON CACHE BOOL "" FORCE)
add_subdirectory(freetype-2.12.1)
endif()