
#include "main.h"

template<typename T , uint8_t s> class Average
{
private:
	T elem[s];
	uint8_t currentIndex; //next array index to be fill with value
	uint8_t numberOfElem; //current number of elements - to protect average during filling array first time
	T avrg;

	void indexIterate();
	void calculate();

public:
	Average();
	~Average();

	void insert(T val);
	void clear();
	int size()const { return s; };
	//T& getAvrage()const{ return avrg;};
	T& operator()();


};




