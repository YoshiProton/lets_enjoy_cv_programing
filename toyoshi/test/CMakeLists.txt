cmake_minimum_required(VERSION 2.8)

#SET(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3 -pg -fpermissive")
set(CMAKE_C_FLAGS_RELEASE "-fpermissive")

set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "-g -pg")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -pg -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3")
set(CMAKE_CXX_FLAGS_MINSIZEREL "")
set(CMAKE_CXX_FLAGS "-pg")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -pg")

set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE Debug)

project(cv_shokyu)

find_package(OpenCV)

# ビルドするためにインクルードするヘッダーファイルの場所
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("/usr/local/include")
include_directories(${OPENCV_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})

# ライブラリの場所
link_directories("/usr/local/lib")

# 実行ファイルを生成
# add_executable(cv_shokyu differentTypeMatTest.cpp)
add_executable(cv_shokyu matAccessTest.cpp)

# ライブラリとリンクする
target_link_libraries(cv_shokyu
	toyocv_imgproc
	${OpenCV_LIBRARIES}
	${Boost_LIBRARIES}
	${OPENGL_LIBRARIES})

# set_target_properties(cv_shokyu PROPERTIES VERSION ${serial})
