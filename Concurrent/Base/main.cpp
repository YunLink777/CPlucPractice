/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/4/6
 *
 * \brief  ���̲߳�������demo
 *  \content:
 * 1��thread_local��2��thread/jthread��3��mutex��lock
 */

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
mutex out_mutex;

void Func()
{
	//thread_local,�洢�ռ����߳�,ÿ���������߳���һ��numʵ��,�ȼ���thread_local static
	thread_local int num = 0;

	for (int i = 0; i < 10; i++)
	{
		//lock_guard��RAIIģʽ����,����ʱ��mutex����,�뿪����������ʱ,����
		lock_guard<mutex> out_lock(out_mutex);
		cout << "Thread: " << this_thread::get_id() << " num: " << num++ << endl;
	}
}

int main()
{
	//��������thread, ����join�ȴ��߳�ͬ��
	thread thread_1(Func);
	thread thread_2(Func);
	thread_1.join();
	thread_2.join();
	system("pause");
	return 0;
}

