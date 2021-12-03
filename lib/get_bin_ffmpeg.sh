if [ ! -f "../external/FFmpeg/configure" ]; then
git submodule update --init --recursive
fi

echo 
echo FFmeg: configure ==============================
echo 
cd ./external/FFmpeg
PKG_CONFIG_PATH="../../lib/lib/pkgconfig" ./configure\
  --prefix=../../lib \
  --pkg-config-flags="--static" \
  --extra-cflags="-I../../lib/include" \
  --extra-ldflags="-L../../lib/lib" \
  --extra-libs="-lpthread -lm" \
  --bindir="../../lib/bin" \
  --disable-large-tests \
  --disable-debug \
  --disable-ffplay \
  --disable-ffprobe \
  --disable-doc \
  --disable-sdl2 \
  --enable-gpl \
  --enable-openssl \
  --enable-libx264 \
  --enable-nonfree

echo 
echo FFmeg: build ==================================
echo 
make -j$(nproc) 

echo 
echo FFmeg: install ================================
echo 
make install
