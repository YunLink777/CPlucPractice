/*!
 * \file main.cpp
 *
 * \author YunLink777
 * \date 2021/1/15
 *
 * \brief 指针Demo
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

	//赋值一个新的shared_ptr,共享指针内的use_count加一，use_count是atomic的，线程安全
	std::shared_ptr<Test> lp = p;
	{
		//static mutex, used in all the threads
		static std::mutex io_mutex;

		std::lock_guard<std::mutex> lk(io_mutex);

		cout << "local pointer in a thread:\n" << " lp->get() = " << lp.get() << "  lp.use_count() = " << lp.use_count() << endl;
	}
}

//---------------------------------------------
//两个shared_ptr之间循环引用
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

//在类内使用weak_ptr替代shared_ptr，打破循环引用
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
	//使用 make_shared 一次创建所有内存
	//如果使用 "shared_ptr<Test> p(new Test())", new Test 会先执行, Test对象的内存被创建出来, 然后shared_ptr的其他内存才会被创建出来
	//两部分内存不是连续的
	shared_ptr<Test> p = make_shared<Test>();

	cout << "Create a shared pointer Test:\n" << " p->get() = " << p.get() << "  p.use_count() = " << p.use_count() << endl;


	//create three threads
	//形参拷贝了shared_ptr，引用计数增加
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
	//下面三种方式都是调用Test的print
	p->print();
	(p.get())->print();
	(*p).print();

	shared_ptr<Test> p2;
	//判断shared_ptr内的对象指针是否为空
	if (p2 == nullptr)
	{
		cout << "pointer in shared_ptr is null\n";
	}
	p2 = p;
	cout << "p's use_count: " << p.use_count() << endl;
	p2.reset();	//reset shared_ptr p2, 但是use_count != 0, Test 对象不会被释放.
	cout << "p's use_count: " << p.use_count() << endl;
	p.reset();	//reset shared_ptr p, use_count == 0, Test 对象被释放.
	if (p == nullptr)
	{
		cout << "pointer in shared_ptr is null\n";
	}
	p.reset(new Test());	//reset shared_ptr p 的同时创建 new Test 对象, use_count == 1, 如果p已经拥有了一个指针，则use_count会减一，同时拥有新的对象指针
	p->print();
	cout << "p's use_count: " << p.use_count() << endl;

	//---------------------------------------------
	//weak_ptr
	weak_ptr<Test> wk_p(p);
	p2 = p;
	cout << "shared_ptr use count: " << p.use_count() << endl;
	cout << "weak_ptr use count: " << wk_p.use_count() << endl;	//weak_ptr 不会增加use_count
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

	//---------------------------------------------
	//unique_ptr
	unique_ptr<Test> uptr;
	if (!uptr)
	{
		cout << "unique_ptr is empty." << endl;
	}

	if (uptr == nullptr)
	{
		cout << "unique_ptr is empty." << endl;
	}

	uptr = make_unique<Test>();
	if (uptr != nullptr)
	{
		uptr->print();
	}

	unique_ptr<Test> uptr2(uptr.release());	//uptr give up the resource, uptr2 get the resource

	if (uptr == nullptr)
	{
		cout << "unique_ptr is empty." << endl;
	}
	uptr2->print();
	
	//std::move can move one unique pointer's resource to another unique pointer
	//unique pointer cannot assign to another unique pointer, and cannot copy to another
	uptr = std::move(uptr2);
	if (uptr2 == nullptr)
	{
		cout << "unique_ptr is empty." << endl;
	}
	uptr->print();

	uptr.reset();	//release the Test object, uptr become empty

	getchar();
}