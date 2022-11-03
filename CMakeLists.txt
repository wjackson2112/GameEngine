project(GameEngine)

set(ENGINE_SOURCES
		Entity.cpp
		GraphicsComponent.cpp
		PhysicsComponent.cpp
		CameraComponent.cpp
		InputComponent.cpp
		Scene.cpp
		InputManager.cpp
		Shader.cpp
		Window.cpp
		Mesh.cpp
		Model.cpp
        ModelComponent.cpp
		Game.cpp
		AssetManager.cpp
		Texture2D.cpp
		CameraComponent2D.cpp
		CameraComponentBase.cpp
		CameraEntity2D.cpp
		SpriteComponent2D.cpp
		CollisionComponent2DAABB.cpp
		CollisionComponent2DRound.cpp
		EventManager.cpp
		EntityManager.cpp
		PostProcessor.cpp
		Texture2DMS.cpp
		wav.cpp
		AudioClip.cpp
		AudioSourceComponent.cpp
		AudioSourceEntity.cpp
		AudioContextComponent.cpp
		AudioContextEntity.cpp
		AudioStream.cpp
		al_error.cpp
		TextComponent.cpp TextFont.cpp IEventReceiver.cpp)
add_library(GameEngine ${ENGINE_SOURCES})

target_include_directories(GameEngine
                           PUBLIC
                           include)

target_sources(GameEngine
		       PRIVATE
		       ${ENGINE_SOURCES})

find_package(OpenGL REQUIRED)
target_link_libraries(GameEngine
		OpenGL::GL
		assimp
		glad
		glfw
		glm
		stb_image
		OpenAL
		freetype)

# Assimp
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
add_subdirectory(external/assimp-5.2.4)

# GLAD
add_subdirectory(external/glad)

# GLFW
## Disable Docs,Tests,Examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw-3.3.2)

# GLM
add_subdirectory(external/glm)

# STB_IMAGE
add_subdirectory(external/stb_image)

# OpenAL
add_subdirectory(external/openal-soft-1.22.2)

# FreeType
add_subdirectory(external/freetype-2.12.1)