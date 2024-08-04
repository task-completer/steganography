#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char** argv)
{
    std::ifstream file1(argv[1]);
    std::ifstream file2(argv[2]);
    std::ofstream file3(argv[3]);
    int grace = 1111;
    if (argc > 4)
    {
        std::stringstream arg4(argv[4]);
        arg4 >> grace;
    }
    while (true)
    {
        unsigned char cur = file1.get();
        if (file1.eof())
        {
            break;
        }
        file3.put(cur);
        grace--;
        if (grace == 0)
        {
            break;
        }
    }
    if (file1.eof())
    {
        std::cerr << "File 1 too short" << std::endl;
        return 1;
    }
    while (true)
    {
        unsigned char cur2 = file2.get();
        if (file2.eof())
        {
            break;
        }
        unsigned char cur1 = file1.get();
        if (file1.eof())
        {
            std::cerr << "File 1 too short, partially done" << std::endl;
            file3.close();
            return 2;
        }
        cur1 &= 0b11110000;  // Обнуление младших битов
        cur1 |= cur2 >> 4;  // Записываем старшие биты из файла 2
        file3.put(cur1);
        cur1 = file1.get();
        if (file1.eof())
        {
            std::cerr << "File 1 too short, partially done" << std::endl;
            file3.close();
            return 2;
        }
        cur1 &= 0b11110000;
        cur1 |= cur2 % 16;  // Записываем младшие биты из файла 2
        file3.put(cur1);
    }
    if (file1.eof() != true)
    {
        while (true)
        {
            unsigned char cur = file1.get();
            if (file1.eof())
            {
                break;
            }
            file3.put(cur);
        }
    }
    file1.close();
    file2.close();
    file3.close();
    return 0;
}
