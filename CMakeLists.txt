cmake_minimum_required(VERSION 3.10)
project(full_octree_id CXX)

add_executable(full_octree_id full_octree_id.cpp)

set_target_properties(full_octree_id PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

