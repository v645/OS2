#include <iostream>
#include <windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <thread>
#include <chrono>

using namespace std;

int main1()
{
    HANDLE mutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, TEXT("MainProcessMutex"));

    HANDLE fileMapping = OpenFileMapping(FILE_MAP_WRITE, FALSE, TEXT("FileMapping"));

    char* ch = (char*)MapViewOfFile(fileMapping, FILE_MAP_WRITE, 0, 0, 0);
    while (true)
    {
        WaitForSingleObject(mutex, INFINITE);
        cout << "FP" << endl;

        ofstream out("D:\\hello.txt", std::ios::app);
        if (out.is_open())
        {
            out << *ch << std::endl;
            out << ch << std::endl;
            out << &ch << std::endl;
        }
        out.close();
        ReleaseMutex(mutex);
    }
}


int main()
{
    cout << "cfile start" << endl;
    HANDLE mutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, TEXT("MainProcessMutex"));

    HANDLE fileMapping = OpenFileMapping(FILE_MAP_READ, FALSE, TEXT("FileMapping"));
    HANDLE sizeMapping = OpenFileMapping(FILE_MAP_READ, FALSE, TEXT("SizeMapping"));    

    int currentWritten = 0;

    while (true)
    {
        cout << "fxc"<<endl;
       WaitForSingleObject(mutex, 110);

        int* sizeM = (int*)MapViewOfFile(sizeMapping, FILE_MAP_READ, 0, 0, 0);
        int* ch = (int*)MapViewOfFile(fileMapping, FILE_MAP_READ, 0, 0, 0);
        int size = *sizeM;
                cout << "write in file"<< ch[currentWritten - 1] ;
        if (currentWritten < size)
        {
            ofstream out("D:\\hello.txt", std::ios::app);
            if (out.is_open())
            {
                out << ch[currentWritten - 1] << std::endl;
            }
            out.close();
        }
        UnmapViewOfFile(sizeM);
        UnmapViewOfFile(ch);
       ReleaseMutex(mutex);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}