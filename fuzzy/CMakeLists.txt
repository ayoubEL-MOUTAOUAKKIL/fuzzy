cmake_minimum_required(VERSION 3.5)

project(untitled LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
		datas/pictures
        main.cpp
        tests/tests.cpp
        mainwindow.cpp
        mainwindow.h
        core/expression.h
        core/BinaryExpressionModel.h
        core/BinaryShadowExpression.h
        core/evaluator.h
        core/factory.h
        core/NaryExpressionModel.h
        core/NaryShadowExpression.h
        core/UnaryExpressionModel.h
        core/UnaryShadowExpression.h
        core/valueModel.h
        repository/csv/CSVParser.h
        repository/csv/CSVParser.cpp
        repository/car/CarRepository.h
        repository/car/InMemoryCarRepository.h
        repository/car/InMemoryCarRepository.cpp
        domain/Car.h
        domain/Car.cpp
        domain/CarBuilder.h
        domain/CarBuiler.cpp
        domain/CarFactory.h
        domain/CarFactory.cpp
        domain/categorie/Category.h
        domain/categorie/CategoryFactory.h
        domain/categorie/CategoryFactory.cpp
        domain/categorie/City.h
        domain/categorie/Electric.h
        domain/categorie/Sports.h
        domain/categorie/Suv.h
        domain/categorie/Utilitary.h
        controller/CarController.h
        controller/CarController.cpp
        generator/Expressiongenerator.h
        fuzzy/agg.h
        fuzzy/and.h
        fuzzy/CogDefuzz.h
        fuzzy/fuzzyfactory.h
        fuzzy/is.h
        fuzzy/MandaniDefuzz.h
        fuzzy/not.h
        fuzzy/or.h
        fuzzy/SugenoConclusion.h
        fuzzy/SugenoDefuzz.h
        fuzzy/then.h
        tests/tests.h
        datas/cars.csv
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(untitled
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(untitled SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(untitled
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(untitled PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
