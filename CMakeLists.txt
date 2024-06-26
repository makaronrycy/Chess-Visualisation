cmake_minimum_required(VERSION 3.16)

project(POiGK1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Quick3D)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appPOiGK1
    main.cpp
)

qt_add_qml_module(appPOiGK1
    URI POiGK1
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES dataparser.h dataparser.cpp
        SOURCES fileloader.h fileloader.cpp

SOURCES chesscontroler.h chesscontroler.cpp
SOURCES chess_piece.h chess_piece.cpp
SOURCES chess_piece.h chess_piece.cpp

RESOURCES models/maps/darkwood.jpg models/meshes/black_Bishop_mesh.mesh models/meshes/black_King_mesh.mesh models/meshes/black_Knight_mesh.mesh models/meshes/black_Pawn_mesh.mesh models/meshes/black_Queen_mesh.mesh models/meshes/black_Rook_mesh.mesh models/meshes/chess_base_mesh.mesh models/meshes/chess_board_mesh.mesh models/meshes/plane_mesh.mesh models/meshes/white_Bishop_mesh.mesh models/meshes/white_King_mesh.mesh models/meshes/white_Knight_mesh.mesh models/meshes/white_Pawn_mesh.mesh models/meshes/white_Queen_mesh.mesh models/meshes/white_Rook_mesh.mesh
QML_FILES models/Black_Bishop.qml models/Black_King.qml models/Black_Knight.qml models/Black_Pawn.qml models/Black_Queen.qml models/Black_Rook.qml models/Chess_base.qml models/Chess_board.qml models/White_Bishop.qml models/White_King.qml models/White_Knight.qml models/White_Pawn.qml models/White_Queen.qml models/White_Rook.qml
RESOURCES sound_effects/capture.wav sound_effects/move.wav

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appPOiGK1 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appPOiGK1
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appPOiGK1
    PRIVATE Qt6::Quick Qt6::Quick3D
)

include(GNUInstallDirs)
install(TARGETS appPOiGK1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
