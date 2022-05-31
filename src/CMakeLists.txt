SET(ORCA_HEADERS    
                    const.h
                    agents.h
                    geometry/circle.h
                    geometry/geom.h
                    geometry/line.h
                    geometry/vec.h
                    geometry/VO.h
                    visualization/frame.h
                    algo.h)

SET(ORCA_SOURCES    agents.cpp
                    geometry/circle.cpp
                    geometry/line.cpp
                    geometry/vec.cpp
                    geometry/VO.cpp
                    visualization/frame.cpp
                    algo.cpp)

add_library(ORCA ${ORCA_HEADERS} ${ORCA_SOURCES})