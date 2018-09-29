file(GLOB containers_SRCS *.cpp *.h)

add_executable(containers
    ${containers_SRCS}
)


install(TARGETS containers DESTINATION bin)
