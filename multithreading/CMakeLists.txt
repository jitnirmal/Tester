file(GLOB multithreading_SRCS *.cpp *.h)

add_executable(multiThreading
    ${multithreading_SRCS}
)


install(TARGETS multiThreading DESTINATION bin)
