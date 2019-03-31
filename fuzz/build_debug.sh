#!/bin/sh
cd ..
if [ -d build_fuzz ]
then
echo "build_fuzz directory found..."
else
echo "creating build_fuzz directory..."
mkdir build_fuzz
fi
cd build_fuzz
cmake .. -DDOWNLOAD_BOOST=1 -DWITH_BOOST=./ -DFUZZINGDEBUG=1

make fuzz_network_1_onefile -j${nproc}
make fuzz_network_1_client -j${nproc}

make server_fuzz
