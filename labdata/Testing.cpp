
#include <iostream>
using namespace std;


int isTmax(int x) {
  // 最高位为0
  // 思路是对的，但是要换一种方法来
  // *   Legal ops: ! ~ & ^ | +
  int notNegative = !((1<<31)&x);
  int isLargest   = (1<<31)&(x+1); 
  int valid = x+1 == ~x;
  printf("notNegative: %d, isLargest: %d, result: %d, valid: %d\n", notNegative, isLargest, notNegative&isLargest, valid);

  int a = 5;
  a = (~a+1)|a;
  a = a>>31;
  printf("a: %d", a);

  return notNegative&isLargest;
  //return isLargest;
}

int main()
{
    isTmax(2147483647);
    return 0;
}
