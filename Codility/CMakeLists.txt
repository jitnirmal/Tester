file(GLOB Codility_SRCS *.cpp *.h)

add_executable(Codility
    ${Codility_SRCS}
)


install(TARGETS Codility DESTINATION bin)
