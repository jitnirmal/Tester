file(GLOB IO_SRCS *.cpp *.h)

add_executable(IO_test
    ${IO_SRCS}
)


install(TARGETS IO_test DESTINATION bin)
