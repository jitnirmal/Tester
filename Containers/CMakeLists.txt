file(GLOB containers_SRCS *.cpp *.h)

add_executable(container_test
    ${containers_SRCS}
)


install(TARGETS container_test DESTINATION bin)
