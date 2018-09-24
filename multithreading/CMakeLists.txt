file(GLOB multithreading_SRCS *.cpp *.h)

add_executable(mt_test
    ${multithreading_SRCS}
)


install(TARGETS mt_test DESTINATION bin)
