cd C:\Code\Projects\TestCpp20
move test_pfunc.exe test_pfunc_old.exe
c++ -std=c++20 -o test_pfunc.exe test_pfunc.cpp
echo "ok"
test_pfunc.exe
pause