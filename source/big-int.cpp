
#include <iostream>
#include "big-int/sources/unsigned_big_integer.h"

using namespace std;

int main()
{
	unsigned_big_integer a = "19";
	cout << a.to_string() << endl;
	
	return 0;
}