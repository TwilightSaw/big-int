#include <iostream>
#include "big-int/unsigned_big_integer.h"

using namespace std;

int main()
{
	unsigned_big_integer a = "10";
	unsigned_big_integer b = "10000000000";
	cout << a.sum(b).to_string() << endl;
	
	return 0;
}