# CMakeのバージョン
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#SET(CMAKE_CXX_COMPILER "clang++")

# リリースビルド用オプション
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3 -pg -fpermissive")
SET(CMAKE_C_FLAGS_RELEASE "-fpermissive")

# デバッグビルド用オプション
SET(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "-g -pg")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -pg -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3")
set(CMAKE_CXX_FLAGS_MINSIZEREL "")
SET (CMAKE_CXX_FLAGS "-pg")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -pg")

# ビルドのタイプはリリース
#SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_BUILD_TYPE Debug)

# プロジェクト名
PROJECT(cv_shokyu)

# 実行に必要なライブラリのパッケージを見つける
FIND_PACKAGE(OpenCV)
FIND_PACKAGE(Boost)
find_package(OpenMP)
find_package(OpenGL)
find_package(GLUT)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# バージョン番号
# SET(serial "1.0.0")

# ビルドするためにインクルードするヘッダーファイルの場所
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}")
INCLUDE_DIRECTORIES("/usr/local/include")
INCLUDE_DIRECTORIES(${OPENCV_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})

# ライブラリの場所
LINK_DIRECTORIES("/usr/local/lib")

# 実行ファイルを生成
ADD_EXECUTABLE(cv_shokyu lesson4.cpp)

# ライブラリとリンクする
TARGET_LINK_LIBRARIES(cv_shokyu toyocv_imgproc ${OpenCV_LIBRARIES} ${Boost_LIBRARIES} ${OPENGL_LIBRARIES})

# バージョン番号の適用
# SET_TARGET_PROPERTIES(cv_shokyu PROPERTIES VERSION ${serial})
