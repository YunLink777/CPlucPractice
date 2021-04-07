/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/4/6
 *
 * \brief  多线程并发基础demo
 *  \content:
 * 1、thread_local；2、thread/jthread；3、mutex和lock
 */

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
mutex out_mutex;

void Func()
{
	//thread_local,存储空间是线程,每个单独的线程有一份num实例,等价于thread_local static
	thread_local int num = 0;

	for (int i = 0; i < 10; i++)
	{
		//lock_guard是RAII模式的锁,创建时对mutex加锁,离开作用域析构时,解锁
		lock_guard<mutex> out_lock(out_mutex);
		cout << "Thread: " << this_thread::get_id() << " num: " << num++ << endl;
	}
}

int main()
{
	//创建两个thread, 调用join等待线程同步
	thread thread_1(Func);
	thread thread_2(Func);
	thread_1.join();
	thread_2.join();
	system("pause");
	return 0;
}

