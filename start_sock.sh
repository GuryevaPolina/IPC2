echo Sock:

./host_sock &
echo $!
./client_sock $!
