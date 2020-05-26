project(CircularQueue)

set(src
    ${CMAKE_CURRENT_SOURCE_DIR}/CircularQueue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MyQueue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MyQueue.h
)

add_executable( CircularQueue
    ${src}
)