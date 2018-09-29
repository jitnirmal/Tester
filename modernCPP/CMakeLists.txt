file(GLOB mdcpp_SRCS *.cpp *.h)

add_executable(modernCPP
    ${mdcpp_SRCS}
)


install(TARGETS modernCPP DESTINATION bin)
