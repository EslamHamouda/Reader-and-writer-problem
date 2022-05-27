#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
using namespace std::chrono;

mutex m;
int buffer[5];
int bufferSize = 0;

void reader_writer(int f)
{
	m.lock();
	if (f == 0)
	{
		if (bufferSize == 5)
		{
			cout << "--------------------------------\n";
			cout << " Can not write buffer is full \n";
			this_thread::sleep_for(seconds(1));
			cout << "--------------------------------\n";
		}
		else
		{
			srand((int)time(0));
			cout << "--------------------------------\n";
			cout << " Writer is being write \n";
			this_thread::sleep_for(seconds(3));
			for (int i = 0; i < 5; i++)
			{
				buffer[i] = (rand() % 100) + 1;
				bufferSize++;
			}
			cout << " Writing data is done \n";
			cout << "--------------------------------\n";
		}
	}
	else if (f == 1)
	{
		if (bufferSize == 0)
		{
			cout << "--------------------------------\n";
			cout << " Can not read buffer is embty \n";
			this_thread::sleep_for(seconds(1));
			cout << "--------------------------------\n";
		}
		else
		{
			cout << "--------------------------------\n";
			cout << " Reader is being read \n";
			this_thread::sleep_for(seconds(3));
			for (int i = 0; i < 5; i++)
			{
				cout << " " << buffer[i];
				bufferSize--;
			}
			cout << "\n";
			cout << " Reading data is done \n";
			cout << "--------------------------------\n";
		}
	}
	m.unlock();
}

int main()
{
	srand((int)time(0));
	thread randomThread[10];
	for (int i = 0; i < 10; i++)
	{
		randomThread[i] = thread(reader_writer, rand() % 2);
	}
	for (auto &i :randomThread)
	{
		i.join();
	}
	
} 