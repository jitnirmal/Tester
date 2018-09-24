set(performance_SRCS
    test.cpp
)

add_executable(performance_test
    ${performance_SRCS}
)


install(TARGETS performance_test DESTINATION bin)
