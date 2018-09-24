set(Boost_SRCS
   Serialization.h
   Tuple.h
   LockFree.h
   test.cpp	
   container_bmark.h
)

add_executable(Boost_test
    ${Boost_SRCS}
)


install(TARGETS Boost_test DESTINATION bin)
