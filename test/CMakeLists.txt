include_directories(../include)
add_definitions(-DBIMALLOC_TESTING)
link_libraries(gtest gmock_main)

add_executable(bitmap_test
        bitmap_test.cc
        ../src/bimalloc_bitmap.c
        )
target_link_libraries(bitmap_test)
add_test(NAME bitmap_test COMMAND bitmap_test)