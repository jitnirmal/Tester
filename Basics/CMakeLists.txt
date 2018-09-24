file(GLOB Basics_SRCS *.cpp *.h)

add_executable(Basics
    ${Basics_SRCS}
)


install(TARGETS Basics DESTINATION bin)
