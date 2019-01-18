echo Mmap:

./host_mmap &
echo $!
./client_mmap $!
