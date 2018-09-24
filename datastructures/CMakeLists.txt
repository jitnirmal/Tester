file(GLOB datastructures_SRCS *.cpp *.h)

add_executable(ds_test
    ${datastructures_SRCS}
)


install(TARGETS ds_test DESTINATION bin)
