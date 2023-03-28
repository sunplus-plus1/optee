echo "#####  clean optee_os  #####"
cd optee_os
make clean
cd ..

echo "#####  clean optee_client #####"
cd optee_client
make  WITH_TEEACL=0 clean
cd ..

echo "##### clean optee_example #####"
cd optee_examples/hello_world
make  clean
cd ../..
