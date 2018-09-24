set(BoostNW_SRCS
	AsyncParallel.h
	SyncIterative.h
	SyncParallel.h
	SyncTCPClient.h
	Common.h
	test.cpp
)

add_executable(BoostNW_test
    ${BoostNW_SRCS}
)


install(TARGETS BoostNW_test DESTINATION bin)
