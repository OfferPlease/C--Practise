#include <cstring>

union {
	struct 
	{
		char* mData;
		size_t mSize;
		size_t mCpacity;
	} Large;

	struct 
	{
		char mData[22];
		char mSize;
		bool mIsSmallString;
	} Small;
} mstr;

void String(const char* str)
{
	size_t len = strlen(str);
	if (len <= 21)
	{
		strcpy(mstr.Small.mData, str);
		mstr.Small.mSize = len;
		mstr.Small.mIsSmallString = true;
	}
	else {
		mstr.Large.mCpacity = len + 1;
		mstr.Large.mSize = len;
		mstr.Large.mData = new char[len + 1];
	}
	
}


int capacity() {
	if (mstr.Small.mIsSmallString) return 21;
	else return mstr.Large.mSize;
}