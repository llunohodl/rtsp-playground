echo
echo build  ========================================
echo 

mkdir ./build
cd ./build
cmake ../ 
make -j$(nproc) all