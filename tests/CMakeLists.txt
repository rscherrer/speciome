# tests/CMakeLists.txt

find_package(Boost COMPONENTS unit_test_framework)

if (Boost_FOUND)
    
	# model 'unit' files
	file(GLOB_RECURSE unit ${CMAKE_SOURCE_DIR}/src/*.cpp)

	set(TESTS CollectorTests GenArchTests IndividualTests MetaPopTests OutputTests SimulTests)

	foreach(TEST IN LISTS TESTS)
		add_executable(${TEST} ${CMAKE_SOURCE_DIR}/tests/${TEST}.cpp ${unit})
		target_include_directories(${TEST} PRIVATE ${CMAKE_SOURE_DIR})
		target_link_libraries(${TEST} PUBLIC Boost::unit_test_framework)
		set_target_properties(${TEST} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/tests/$<0:>)
	endforeach()
    
endif()
