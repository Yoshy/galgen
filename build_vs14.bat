mkdir build
mkdir install
cd build
cmake -G "Visual Studio 14 2015" -DURHO3D_HOME=Y:/devel/Urho3D-1.7/sdk/ -DCMAKE_INSTALL_PREFIX=Y:/devel/GalaxyGenerator/install/ ../src
cmake --build . --target install
pause
