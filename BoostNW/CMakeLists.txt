file(GLOB BoostNW_SRCS *.cpp *.h)

add_executable(BoostNW_test
    ${BoostNW_SRCS}
)


install(TARGETS BoostNW_test DESTINATION bin)
