if [ ! -f "../external/x264/configure" ]; then
git submodule update --init --recursive
fi

echo 
echo x264: configure ===============================
echo 
cd ./external/x264
./configure  --enable-static --enable-pic \
--prefix=../../lib

echo 
echo x264: build ===================================
echo 
make -j$(nproc) 

echo 
echo x264: install =================================
echo 
make install