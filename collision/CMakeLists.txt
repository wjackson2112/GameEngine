set(SOURCES
	CollisionComponent2DAABB.cpp
	CollisionComponent2DRound.cpp)

target_include_directories(GameEngine
                           PUBLIC
                           include)
target_sources(GameEngine
		       PRIVATE
		       ${SOURCES})