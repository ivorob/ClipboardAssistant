CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
PROJECT (ClipboardAssistant)

SET (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
SET (SOURCES
        ${SRC_DIR}/main.cpp
    )

ADD_EXECUTABLE (ClipboardAssistant ${SOURCES})
