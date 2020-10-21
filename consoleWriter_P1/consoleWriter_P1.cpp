#include <iostream>
#include <windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <thread>

using namespace std;

int main()
{
    cout << "console start" << endl;
    HANDLE mutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, TEXT("MainProcessMutex"));

    HANDLE fileMapping = OpenFileMapping(FILE_MAP_READ, FALSE, TEXT("FileMapping"));
    HANDLE sizeMapping = OpenFileMapping(FILE_MAP_READ, FALSE, TEXT("SizeMapping"));


    //cout << "console 2::size_!=" <<nums.size() << endl;

    int currentWritten = 0;

    while (true)
    {
        cout << "xc"<<endl;
         WaitForSingleObject(mutex, 100);
        int* sizeM = (int*)MapViewOfFile(sizeMapping, FILE_MAP_READ, 0, 0, 0);
        int* ch = (int*)MapViewOfFile(fileMapping, FILE_MAP_READ, 0, 0, 0);

        int size = *sizeM;
        cout << "size=" << size << endl;
       // cout << "sizeof(ch)=" << sizeof(*ch) << endl;
        vector<int> nums=(vector<int>)*(ch);
       // vector<int> nums=vector<int>(ch,ch+size);
        /*
        cout << "nums count=" << nums.size() << endl;
        cout << "ch[0]=" << ch[0] << endl;
        cout << "ch[1]=" << ch[1] << endl;
        cout << "ch[2]=" << ch[2] << endl;
        cout << "ch[3]=" << ch[3] << endl;*/

        if (currentWritten < size)

        {
            // cout <<"CONSOLE:"<< ch[currentWritten++] << endl;
            currentWritten++;
            //cout <<"CONSOLE n:"<< nums[currentWritten] << endl;
            cout << "CONSOLE c[" << (currentWritten - 1) << "]" << ":--> " << ch[currentWritten - 1] << endl;
           // cout << "CONSOLE n[" << (currentWritten - 1) << "]" << ":--> " << nums[currentWritten - 1] << endl;
            // cout <<"CONSOLE:"<< *ch << endl;
        }

        UnmapViewOfFile(ch);
        UnmapViewOfFile(sizeM);
       ReleaseMutex(mutex);

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}