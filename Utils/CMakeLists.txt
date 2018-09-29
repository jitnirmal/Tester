file(GLOB Utils_SRCS *.cpp *.h)

add_executable(utils
    ${Utils_SRCS}
)


install(TARGETS utils DESTINATION bin)
