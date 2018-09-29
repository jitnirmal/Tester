file(GLOB datastructures_SRCS *.cpp *.h)

add_executable(dataStructures
    ${datastructures_SRCS}
)


install(TARGETS dataStructures DESTINATION bin)
