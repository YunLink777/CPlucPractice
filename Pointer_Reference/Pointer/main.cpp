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
	void print()
	{
		cout << "Test Print" << endl;
	}
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

//---------------------------------------------
//circular reference between two shared_ptr
class A
{
public:
	A()
	{
		cout << "Class A is constructing." << endl;
	}

	~A()
	{
		cout << "Class A is destructing." << endl;
	}

	shared_ptr<class B> spb;
};

class B
{
public:
	B()
	{
		cout << "Class B is constructing." << endl;
	}

	~B()
	{
		cout << "Class B is destructing." << endl;
	}

	shared_ptr<class A> spa;
};

//use weak_ptr instead of shared_ptr within class to destroy the circular reference
class C
{
public:
	C()
	{
		cout << "Class C is constructing." << endl;
	}

	~C()
	{
		cout << "Class C is destructing." << endl;
	}

	weak_ptr<class D> spd;
};

class D
{
public:
	D()
	{
		cout << "Class D is constructing." << endl;
	}

	~D()
	{
		cout << "Class D is destructing." << endl;
	}

	weak_ptr<class C> spc;
};

void main(int argc, char* argv[])
{
	func(NULL);	//NULL means 0 in c++, in C, it means (void*)0
	func(nullptr);	//use nullptr means null pointer

	//---------------------------------------------
	//shared_ptr use_count
	//use make_shared to create all the memory once
	//if use "shared_ptr<Test> p(new Test())", new Test will be run first, a memory will be created, then another memory will be created by shared_ptr
	//the two part of memory are not serial
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

	//---------------------------------------------
	//shared_ptr * and ->
	//All three expressions below are calling print of Test object
	p->print();
	(p.get())->print();
	(*p).print();

	shared_ptr<Test> p2;
	//judge the pointer in the shared_ptr
	if (p2 == nullptr)
	{
		cout << "pointer in shared_ptr is null\n";
	}
	p2 = p;
	cout << "p's use_count: " << p.use_count() << endl;
	p2.reset();	//reset shared_ptr p2, but use_count != 0, Test object isn't destoryed.
	cout << "p's use_count: " << p.use_count() << endl;
	p.reset();	//reset shared_ptr p, but use_count == 0, Test object is destoryed.
	if (p == nullptr)
	{
		cout << "pointer in shared_ptr is null\n";
	}
	p.reset(new Test());	//reset shared_ptr p with new Test object, use_count == 1, if p already owned an object, the use_count will decrease by 1
	p->print();
	cout << "p's use_count: " << p.use_count() << endl;

	//---------------------------------------------
	//weak_ptr
	weak_ptr<Test> wk_p(p);
	p2 = p;
	cout << "shared_ptr use count: " << p.use_count() << endl;
	cout << "weak_ptr use count: " << wk_p.use_count() << endl;	//weak_ptr don't increase the use count
	shared_ptr<Test> p3 = wk_p.lock();	//create a new shared_ptr through lock()
	cout << "weak_ptr use count: " << wk_p.use_count() << endl;
	p3.reset();
	p2.reset();
	p.reset();
	cout << "weak_ptr use count: " << wk_p.use_count() << endl;
	cout << "weak_ptr expired: " << wk_p.expired() << endl;	// if use_count == 0, expired == true
	wk_p.reset();
	cout << "weak_ptr use count: " << wk_p.use_count() << endl;
	p = make_shared<Test>();
	wk_p = p;
	cout << "make_shared weak_ptr use count: " << wk_p.use_count() << endl;
	cout << "weak_ptr expired: " << wk_p.expired() << endl;
	p.reset();
	cout << "make_shared weak_ptr use count: " << wk_p.use_count() << endl;
	cout << "weak_ptr expired: " << wk_p.expired() << endl;

	//---------------------------------------------
	//circular reference between two shared_ptr
	//you cannot see the destruct print when main() return
	shared_ptr<A> spa = make_shared<A>();
	shared_ptr<B> spb = make_shared<B>();
	spa->spb = spb;
	spb->spa = spa;

	//you can see the destruct print when main() return
	shared_ptr<C> spc = make_shared<C>();
	shared_ptr<D> spd = make_shared<D>();
	spc->spd = spd;	// shared_ptr cast to weak_ptr
	spd->spc = spc;

	getchar();
}