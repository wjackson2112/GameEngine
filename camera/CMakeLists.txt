set(SOURCES
	CameraComponent.cpp
	CameraComponent2D.cpp
	CameraComponentBase.cpp
	CameraEntity.cpp
	CameraEntity2D.cpp)

target_include_directories(GameEngine
                           PUBLIC
                           include)
target_sources(GameEngine
		       PRIVATE
		       ${SOURCES})