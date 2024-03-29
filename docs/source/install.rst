Installation
============
Using cmake
------------
Installation using cmake is simple, you just have to grab CPPRAW's source and headers and fetch both nlohmann/json and libcpr using FetchContent.
Add this to your CMakeLists.txt:

.. code-block:: cmake

    cmake_minimum_required(VERSION 3.20)
    project(your_project)

    set(CMAKE_CXX_STANDARD 17)

    set(CPPRAW_SOURCE_FILES CPPRAW/CPPRAW.cpp CPPRAW/subreddit.cpp CPPRAW/post.cpp CPPRAW/request.cpp CPPRAW/user.cpp)

    add_executable(your_project main.cpp ${CPPRAW_SOURCE_FILES})

    include(FetchContent)

    FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                             GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
    FetchContent_MakeAvailable(cpr)
    FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.1/json.tar.xz)
    FetchContent_MakeAvailable(json)

    target_link_libraries(your_project PRIVATE nlohmann_json::nlohmann_json)
    target_link_libraries(your_project PRIVATE cpr::cpr)

Manual installation
-------------------
You can probably manually install both `libcpr`_ and `nlohmann/json`_, but preferrably use FetchContent.

.. _libcpr: https://github.com/libcpr/cpr
.. _nlohmann/json: https://github.com/nlohmann/json