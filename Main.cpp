#include "MyArray.hpp"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    MyArray one(10);
    MyArray two{ 2,4,8,16,32,64,128,256,512,1024,2048,4096 };

    MyArray three = std::move(one);

    std::cout << two.toString();

    std::cout << "\n\n\n\n\n";
    system("pause");
    return 0;
}

