# CMakeのバージョン
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_COMPILER c++)

# リリースビルド用オプション
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2 -fpermissive -fPIC -pg")
# デバッグビルド用オプション
SET(CMAKE_CXX_FLAGS_DEBUG "-g -fpermissive -fPIC")
# ビルドのタイプはリリース
SET(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)

#set(CMAKE_CXX_FLAGS "$(CMAKE_CXX_FLAGS) -fpermissive")

SET(CMAKE_INSTALL_PREFIX=/usr/local)
# プロジェクト名
PROJECT(toyocv)

FIND_PACKAGE(OpenCV)
FIND_PACKAGE(Boost)

# バージョン番号
SET(serial "1.0.0")
# 共有ライブラリのバージョン番号
SET(soserial "1")

# 共有ライブラリとしてビルド
# ADD_LIBRARY(toyocv SHARED)

add_subdirectory(modules/imgproc)

# TARGET_LINK_LIBRARIES(toyocv ${OpenCV_LIBRARIES} ${Boost_LIBRARIES} toyocv_imgproc)

# バージョン番号の適用
# SET_TARGET_PROPERTIES(toyocv PROPERTIES VERSION ${serial} SOVERSION ${soserial})

# 共有ライブラリのインストール指定
# INSTALL(TARGETS toyocv LIBRARY DESTINATION lib)
# if(WIN32)
#  install(TARGETS toyocv
#    RUNTIME DESTINATION path)
# else()
#  install(TARGETS toyocv
#    LIBRARY DESTINATION path)
# endif()
