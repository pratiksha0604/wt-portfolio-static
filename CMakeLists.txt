cmake_minimum_required(VERSION 3.16)
project(wt_portfolio_static LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Step 1: Wt as a dependency
find_package(Wt CONFIG REQUIRED)

add_executable(portfolio_server src/main.cpp)
target_link_libraries(portfolio_server PRIVATE Wt::Wt Wt::HTTP)

# Copy the static folder next to the executable so it can be served from the build dir too
add_custom_command(TARGET portfolio_server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/static $<TARGET_FILE_DIR:portfolio_server>/static)
