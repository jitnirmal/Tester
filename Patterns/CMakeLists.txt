set(Patterns_SRCS
    test.cpp
	Singleton.h
	Factory.h
	Pimpl.h
	Visitor.h
	Composite.h
	Observer.h
	Command.h
	Strategy.h
)

add_executable(Patterns_test
    ${Patterns_SRCS}
)


install(TARGETS Patterns_test DESTINATION bin)
