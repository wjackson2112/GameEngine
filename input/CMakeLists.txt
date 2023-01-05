set(SOURCES
	InputComponent.cpp
	InputManager.cpp)

target_include_directories(GameEngine
                           PUBLIC
                           include)
target_sources(GameEngine
		       PRIVATE
		       ${SOURCES})