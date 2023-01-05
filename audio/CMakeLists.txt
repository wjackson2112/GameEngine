set(SOURCES
	al_error.cpp
	AudioClip.cpp
	AudioContextComponent.cpp
	AudioContextEntity.cpp
	AudioSourceComponent.cpp
	AudioSourceEntity.cpp
	AudioStream.cpp
	wav.cpp)

target_include_directories(GameEngine
                           PUBLIC
                           include)
target_sources(GameEngine
		       PRIVATE
		       ${SOURCES})