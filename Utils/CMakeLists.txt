file(GLOB Utils_SRCS *.cpp *.h)

add_executable(Utils_test
    ${Utils_SRCS}
)


install(TARGETS Utils_test DESTINATION bin)
