# ACLGAD_testbench_sim

# You need to install geant4, qt5, zlib, CADMesh, and ROOT before make

# Load geant4
source /DIR_GEANT4_INSTALL/bin/geant4.sh

# CMake main.cc file
cd build
cmake .. -DGeant4_DIR=/PATH_TO_GEANT4_INSTALL/lib/cmake/Geant4  -DCMAKE_PREFIX_PATH="/PATH_TO_QT5/qt@5;/PATH_TO_ZLIB/zlib;/PATH_TO_CADMesh/build" -DROOT_DIR="/PATH_TO_ROOT/root"
make -j$(sysctl -n hw.logicalcpu)

# Run main
# Interactive Mode (w/ Event Display)
./main
# Batch Mode (w/o Event Display)
./main init_vis.mac