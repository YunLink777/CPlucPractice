/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/1/15
 *
 * \description: Pointer and Reference Demo
 */
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

void func(void* i)
{
	cout << "func1" << endl;
}

void func(int i)
{
	cout << "func2" << endl;
}

//---------------------------------------------
//shared_ptr
struct Test
{
	Test() { cout << "  Test::Test()" << endl; }
	~Test() { cout << "  Test::~Test()" << endl; }
};

//test thread function
void thr(std::shared_ptr<Test> p)
{
	//sleep for 1 second
	std::this_thread::sleep_for(std::chrono::seconds(1));

	//assign a new shared_ptr, increase the use_count by 1, in shred_ptr, the increase count is atomic
	std::shared_ptr<Test> lp = p;
	{ 
		//static mutex, used in all the threads
		static std::mutex io_mutex;

		std::lock_guard<std::mutex> lk(io_mutex);

		cout << "local pointer in a thread:\n" << " lp->get() = " << lp.get() << "  lp.use_count() = " << lp.use_count() << endl;
	}
}

void main(int argc, char* argv[])
{
	func(NULL);	//NULL means 0 in c++, in C, it means (void*)0
	func(nullptr);	//use nullptr means null pointer

	//---------------------------------------------
	//shared_ptr
	//use make_shared to create all the memory once
	shared_ptr<Test> p = make_shared<Test>();

	cout << "Create a shared pointer Test:\n" << " p->get() = " << p.get() << "  p.use_count() = " << p.use_count() << endl;

	//create three threads
	//formal parameters copy the pointer, increase the use count
	std::thread t1(thr, p), t2(thr, p), t3(thr, p);
	std::cout << "Shared ownership between 3 threads and released\n"
					<< "ownership from main:\n" << " p->get() = " << p.get() << "  p.use_count() = " << p.use_count() << endl;

	//wait for the threads finished
	t1.join();
	t2.join();
	t3.join();

	std::cout << "All threads completed, the last one deleted\n";

	getchar();
}