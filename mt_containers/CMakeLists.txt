file(GLOB mt_containers_SRCS *.cpp *.h)

add_executable(mt_container
    ${mt_containers_SRCS}
)


install(TARGETS mt_container DESTINATION bin)
