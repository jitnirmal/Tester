file(GLOB mt_containers_SRCS *.cpp *.h)

add_executable(syncDataStructures
    ${mt_containers_SRCS}
)


install(TARGETS syncDataStructures DESTINATION bin)
