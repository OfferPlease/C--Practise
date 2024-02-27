#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <functional>
struct S{
	S() { i = 0; d = 0; }
	S(int myint, double d)
	{
		i = myint;
		this->d = d;
	}
	~S() { std::cout << "destructor of S\n"; }
	int i;
	double d;
};

template<typename T>
class UniquePtr
{
public:
	UniquePtr(T* ptr, std::function<void(T*)> deleteF)
		:mHeapPtr(ptr),
		mDeleter(deleteF){}
	UniquePtr(T* ptr)
		:mHeapPtr(ptr) {
	}
	~UniquePtr(){ DoDelete(); }
	
	// disallow copy for Unique pointer
	UniquePtr(const UniquePtr& Other) = delete;
	UniquePtr& operator=(const UniquePtr& other) = delete;
	
	// allow move 
	// move constructor
	UniquePtr(UniquePtr&& other)
		:mHeapPtr(std::move(other.mHeapPtr)),
		mDeleter(std::move(other.mDeleter))
	{
		std::cout << "Unique_ptr copy constructor called\n";
		other.mHeapPtr = nullptr;
	}
	// move assignment operator
	UniquePtr& operator=(UniquePtr&& other)
	{
		std::cout << "Unique_ptr copy assignment consturcotr called\n";
		// check for self-assignment
		if (this != &other)
		{
			// delete existing object
			DoDelete();
			// do the move
			this->mHeapPtr = other.mHeapPtr;
			this->mDeleter = other.mDeleter;
		}
		return *this;
	}
	T* Get() { return this->myHeapPtr; }
private:
	T* mHeapPtr;
	std::function<void(T*)> mDeleter;
	void DoDelete()
	{
		if (mDeleter)
		{
			mDeleter(mHeapPtr);
		}
		else {
			delete mHeapPtr;
		}
		
	}
};


struct ControlBlock
{
	unsigned mStrongReferences = 0;
	unsigned mWeakReferences = 0;
};

template <typename T>
class SharedPtr
{
public:
	SharedPtr(T* ptr) :mHeapPtr(ptr), mBlock(new ControlBlock{ 1, 0}) 
	{
		std::cout << "Constructor of my shared_ptr called\n";
	}
	
	~SharedPtr() 
	{
		std::cout << "call destrucor of my shared_ptr\n";
		this->doDelete(); 
	}
	// allow copy
	// copy constructor
	SharedPtr(const SharedPtr& other) :mHeapPtr(other.mHeapPtr), mBlock(other.mBlock)
	{
		std::cout << "Copy constructor of my shared_pointer\n";
		mBlock->mStrongReferences++;
	}
	// copy assignment operator
	SharedPtr& operator=(const SharedPtr& other)
	{
		std::cout << "Copy assignment operator of my shared_poiner\n";
		if (this != &other)
		{
			// no longer reference to the old object
			doDelete();
			// reference to the new object, increment reference count of the new object
			mHeapPtr = other.mHeapPtr;
			mBlock = other.mBlock;
			mBlock->mStrongReferences++;
		}
		return *this;
	}

	// allow move
	// move constructor
	SharedPtr(SharedPtr&& other) 
		: mHeapPtr(other.mHeapPtr),
		mBlock(other.mBlock)
	{
		std::cout << "Move constructor of my shared_pointer\n";
		other.mHeapPtr = nullptr;
		other.mBlock = nullptr;

	}
	// move assignment constructor
	SharedPtr& operator=(SharedPtr&& other)
	{
		std::cout << "Move assignment constructor of my shared_pointer\n";
		if (&other != this)
		{
			// delete the previous resourse
			doDelete();
			mHeapPtr = other.mHeapPtr;
			mBlock = other.mBlock;
			other.mBlock = nullptr;
			other.mBlock = nullptr;
		}
		return *this;
	}

	int getRefCount() { return mBlock->mStrongReferences; }
private:
	void doDelete()
	{
		if (mBlock) 
		{
			mBlock->mStrongReferences--;
			if (mBlock->mStrongReferences == 0)
			{
				if (mBlock->mWeakReferences == 0) {
					delete mBlock;
				}
				if (mHeapPtr) delete mHeapPtr;

			}
		} 
	}
	T* mHeapPtr;
	ControlBlock* mBlock;
	
	SharedPtr() { mHeapPtr = nullptr, mBlock = nullptr; }
	SharedPtr(T* ptr, ControlBlock* blockPtr) :mHeapPtr(ptr), mBlock(blockPtr)
	{
		mBlock->mStrongReferences++;
		std::cout << "Constructor of my shared_ptr called\n";
	}
	
	template <typename U>
	friend class WeakPtr;
};

template <typename T>
class WeakPtr
{
public:
	WeakPtr(const SharedPtr<T>& ptr) :mHeapPtr(ptr.mHeapPtr), mBlock(ptr.mBlock) 
	{
		// std::cout << "Call weak pointer constructor\n";
		mBlock->mWeakReferences++;
	}
	~WeakPtr()
	{
		std::cout << "Call destructor of my WeakPtr()\n";
		if (mBlock)
		{
			mBlock->mWeakReferences--;
			if (mBlock->mStrongReferences == 0 && mBlock->mWeakReferences == 0) delete mBlock;
		}
	}
	// check if the object still exists
	bool isObjectActive() const
	{
		return mBlock && mBlock->mStrongReferences>0;
	}
	// If the object exists, return a strong reference of it
	SharedPtr<T> lock()
	{
		if (isObjectActive()) { return SharedPtr<T>(mHeapPtr, mBlock); }
		else return SharedPtr<T>();
	}
private: 
	void doDelete()
	{

	}
	T* mHeapPtr;
	ControlBlock* mBlock;
};

SharedPtr<S> func_Test1(SharedPtr<S> ptr)
{
	SharedPtr<S> tmp = ptr;
	std::cout << tmp.getRefCount() << std::endl;
	return tmp;
}

int main()
{
	/* std library unique pointer */
	//auto p = std::make_unique<int>(50);
	//auto p1 = std::make_unique<S>(20, 5.0);
	//auto p3 = std::move(p1); // std::move() will set p1 to nullptr
	//std::unique_ptr<int> p4(new int(20));

	// test myUnique_ptr
	//UniquePtr<S> my_uniquePtr(new S(1, 1.0));
	//// passing a customized deleter
	//S* arrS = new S[10];
	//UniquePtr<S> arr_uniquePtr(arrS, [](S* sptr) {delete[] sptr; });

	/* Test Shared_pointer */
	SharedPtr<S> myShared_ptr1(new S(1, 1.0));
	{
		SharedPtr<S> myShared_ptr2 = myShared_ptr1;
		std::cout << myShared_ptr1.getRefCount() << std::endl;
		std::cout << myShared_ptr2.getRefCount() << std::endl;
	}
	std::cout << myShared_ptr1.getRefCount() << std::endl;
	// copy assginment constructor
	SharedPtr<S> myShared_ptr2(new S(2, 2.0));
	myShared_ptr2 = myShared_ptr1;
	std::cout << myShared_ptr2.getRefCount() << std::endl;
	// test move constructor
	SharedPtr<S> myShared_ptr3 = func_Test1(myShared_ptr1);
	std::cout << myShared_ptr2.getRefCount() << std::endl;
	// test move assignment operator
	myShared_ptr2 = func_Test1(myShared_ptr1);
	
	std::cout << myShared_ptr1.getRefCount() << std::endl;
	/* Test weak pointer */
	WeakPtr<S> myWeak_ptr(myShared_ptr1);
	if (myWeak_ptr.isObjectActive()) {
		SharedPtr<S> myShared_ptr4 = myWeak_ptr.lock();
	}
	std::cout << myShared_ptr1.getRefCount() << std::endl;
	return 0;
}