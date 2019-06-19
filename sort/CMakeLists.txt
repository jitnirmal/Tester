file(GLOB sort_SRCS *.cpp *.h)

add_executable(sort
    ${sort_SRCS}
)

target_link_libraries(sort
	
)

install(TARGETS sort DESTINATION bin)
