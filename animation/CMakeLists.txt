set(SOURCES
	Animation.cpp
	AnimationComponent.cpp
	TransformAnimation.cpp)

target_include_directories(GameEngine
                           PUBLIC
                           include)
target_sources(GameEngine
		       PRIVATE
		       ${SOURCES})