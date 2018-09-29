file(GLOB Patterns_SRCS *.cpp *.h)

add_executable(patterns
    ${Patterns_SRCS}
)


install(TARGETS patterns DESTINATION bin)
