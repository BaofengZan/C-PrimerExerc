project(CircularQueueTemplate)

include_directories("E:\\LearningCodes\\CPPProject\\spdlog-1.x\\include")

set(src
    ${CMAKE_CURRENT_SOURCE_DIR}/CircularQueueTemplate.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MyQueue.h
)

add_executable( CircularQueueTemplate
    ${src}
)