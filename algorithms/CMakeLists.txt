file(GLOB algorithms_SRCS *.cpp *.h)

add_executable(algorithms
    ${algorithms_SRCS}
)


install(TARGETS algorithms DESTINATION bin)
