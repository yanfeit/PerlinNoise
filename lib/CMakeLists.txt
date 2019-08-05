aux_source_directory(. DIR_LIB_SRCS)

set (CMAKE_SHARED_LINKER_FLAGS "-fPIC")

add_library (perlinNoise SHARED ${DIR_LIB_SRCS})


