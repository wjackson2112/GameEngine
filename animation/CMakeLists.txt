set(SOURCES
	Animation.cpp
	AnimationComponent.cpp
	ColorAnimation.cpp
	CompoundAnimation.cpp
	TranslationAnimation.cpp
	ScaleAnimation.cpp)

target_include_directories(GameEngine
                           PUBLIC
                           include)
target_sources(GameEngine
		       PRIVATE
		       ${SOURCES})