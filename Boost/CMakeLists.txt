file(GLOB Boost_SRCS *.cpp *.h)
add_executable(Boost_test
    ${Boost_SRCS}
)


install(TARGETS Boost_test DESTINATION bin)
