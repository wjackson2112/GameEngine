set(SOURCES
#	GraphicsComponent.cpp
#	Mesh.cpp
#	Model.cpp
#	ModelComponent.cpp
	PostProcessor.cpp
	Shader.cpp
	SpriteComponent2D.cpp
	Texture2D.cpp
	Texture2DMS.cpp
	SpriteSheetComponent2D.cpp)

target_include_directories(GameEngine
                           PUBLIC
                           include)
target_sources(GameEngine
		       PRIVATE
		       ${SOURCES})