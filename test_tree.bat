cd C:\Code\Projects\TestCpp20
move test_tree.exe test_tree_old.exe
c++ -std=c++20 -o test_tree.exe test_tree.cpp
echo "ok"
test_tree.exe
pause