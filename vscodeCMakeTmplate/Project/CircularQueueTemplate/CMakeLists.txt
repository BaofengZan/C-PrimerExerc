project(CircularQueueTemplate)

set(src
    ${CMAKE_CURRENT_SOURCE_DIR}/CircularQueue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MyQueue.h
)

add_executable( CircularQueueTemplate
    ${src}
)