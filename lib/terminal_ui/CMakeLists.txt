add_library(terminal_ui
        ${CMAKE_CURRENT_SOURCE_DIR}/terminal_ui.c
)

target_include_directories(terminal_ui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)