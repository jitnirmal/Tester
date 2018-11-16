file(GLOB sort_SRCS *.cpp *.h)

add_executable(sort
    ${sort_SRCS}
)


install(TARGETS sort DESTINATION bin)
