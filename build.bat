rd /s /q cmake-build-debug
cmake -H. -Bcmake-build-debug -G"Visual Studio 15 2017 Win64"
pause
start cmake-build-debug\full_octree_id.sln