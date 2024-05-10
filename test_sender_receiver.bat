cd C:\Projects\TestCpp20
move test_sender_receiver.exe test_sender_receiver_old.exe
c++ -std=c++20 -o test_sender_receiver.exe test_sender_receiver.cpp
echo "ok"
test_sender_receiver.exe
pause