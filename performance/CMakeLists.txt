file(GLOB performance_SRCS *.cpp *.h)

add_executable(performance_test
    ${performance_SRCS}
)


install(TARGETS performance_test DESTINATION bin)
