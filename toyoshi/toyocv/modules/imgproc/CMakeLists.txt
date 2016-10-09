# CMakeのバージョン
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# SET(CMAKE_CXX_COMPILER c++)

# リリースビルド用オプション
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2 -fpermissive -fPIC -pg")
# デバッグビルド用オプション
SET(CMAKE_CXX_FLAGS_DEBUG "-g -fpermissive -fPIC")
# ビルドのタイプはリリース
# SET(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

#set(CMAKE_CXX_FLAGS "$(CMAKE_CXX_FLAGS) -fpermissive")

SET(CMAKE_INSTALL_PREFIX=/usr/local)
# プロジェクト名
PROJECT(toyocv_imgproc)

FIND_PACKAGE(OpenCV)
FIND_PACKAGE(Boost)
find_package(OpenMP)
#find_package(OpenGL)
#find_package(GLUT)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# バージョン番号
SET(serial "1.0.0")
# 共有ライブラリのバージョン番号
SET(soserial "1")
# ビルドするためにインクルードするヘッダーファイルの場所
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")

file(GLOB toyocv_imgproc_src
	  "src/*.cpp"
)
file(GLOB toyocv_imgproc_include
	  "include/*.hpp"
)

# 共有ライブラリとしてビルド
ADD_LIBRARY(toyocv_imgproc SHARED ${toyocv_imgproc_src})

TARGET_LINK_LIBRARIES(toyocv_imgproc ${OpenCV_LIBRARIES} ${Boost_LIBRARIES})

# バージョン番号の適用
SET_TARGET_PROPERTIES(toyocv_imgproc PROPERTIES VERSION ${serial} SOVERSION ${soserial})

# 共有ライブラリのインストール指定
# INSTALL(TARGETS toyocv_imgproc LIBRARY DESTINATION lib)
# 共有ライブラリ用ヘッダーファイルのインストール指定
INSTALL(FILES ${toyocv_imgproc_include}
	      DESTINATION include/toyocv)
if(WIN32)
  install(TARGETS toyocv_imgproc
    RUNTIME DESTINATION lib)
else()
  install(TARGETS toyocv_imgproc
    LIBRARY DESTINATION lib)
endif()
