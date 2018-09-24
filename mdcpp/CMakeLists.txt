file(GLOB mdcpp_SRCS *.cpp *.h)

add_executable(mdcpp
    ${mdcpp_SRCS}
)


install(TARGETS mdcpp DESTINATION bin)
