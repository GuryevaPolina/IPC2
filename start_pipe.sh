echo Pipe:

./host_pipe &
echo $!
./client_pipe $!
