#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char** argv)
{
    std::ifstream file3(argv[1]);
    std::ofstream file4(argv[2]);
    int grace = 1111;
    if (argc > 3)
    {
        std::stringstream arg3(argv[3]);
        arg3 >> grace;
    }
    for (int i = 0; i < grace; i++)
    {
        file3.get();
        if (file3.eof())
        {
            std::cerr << "File too short" << std::endl;
            return 1;
        }
    }
    while (true)
    {
        unsigned char cur_big = file3.get();
        if (file3.eof())
        {
            break;
        }
        unsigned char cur_little = file3.get();
        if (file3.eof())
        {
            file4.put(cur_big << 4);
            file4.close();
            break;
        }
        cur_big &= 0b00001111;
        cur_little &= 0b00001111;
        unsigned char joined = cur_big * 16 + cur_little;
        file4.put(joined);
    }
    file3.close();
    file4.close();
    return 0;
}
