cmake_minimum_required(VERSION 3.16)
project(CADStepExample)

# Geant4
find_package(Geant4 REQUIRED)

# ROOT
find_package(ROOT REQUIRED COMPONENTS MathCore Graf)
include(${ROOT_USE_FILE})

# CADMesh
set(CADMESH_DIR /Users/syano/eic/CADMesh)

# Include directories
include_directories(
    ${Geant4_INCLUDE_DIRS}
    ${CADMESH_DIR}/include
    ${CADMESH_DIR}/build/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include   # ← 🔧 ここを追加
    ${ROOT_INCLUDE_DIRS}
)

# CADMesh sources
set(CADMESH_SOURCES
    ${CADMESH_DIR}/src/TessellatedMesh.cc
    ${CADMESH_DIR}/src/STLReader.cc
    ${CADMESH_DIR}/src/OBJReader.cc
    ${CADMESH_DIR}/src/PLYReader.cc
    ${CADMESH_DIR}/src/Reader.cc
    ${CADMESH_DIR}/src/Mesh.cc
    ${CADMESH_DIR}/src/Lexer.cc
    ${CADMESH_DIR}/src/FileTypes.cc
    ${CADMESH_DIR}/src/Exceptions.cc
    ${CADMESH_DIR}/src/CADMeshTemplate.impl.cc
    ${CADMESH_DIR}/src/BuiltInReader.cc
)

# Your application sources
set(APP_SOURCES
    main.cc
    #RunAction.cc
    #ActionInitialization.cc
    PrimaryGeneratorAction.cc
    #SteppingAction.cc
    #EventAction.cc
    #TrackingAction.cc
    MyPhotocathodeSD.cc
    MyPhotocathodeHit.cc
    #MyGlobals.cc
)

add_executable(main ${APP_SOURCES} ${CADMESH_SOURCES})
target_link_libraries(main
                      ${Geant4_LIBRARIES}
		      ${ROOT_LIBRARIES}
		      )


