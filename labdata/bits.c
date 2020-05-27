/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

// 就是更改下面的这些 function
You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

[[[[[INTEGER]]]]] CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 

 // 方法的template
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      
     not allowed to use big constants such as 0xffffffff.

  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly [[[forbidden]]] to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // x 取补码之后再和 y 取 and
  // x 补码就是和自己完全相反的，如果和y取and非零的话，那么就证明那一位两者不相等
  // 4: 100, 补码 011
  // 5: 101， 001，但是反过来不行？ 所以不可能只是单方面进行操作， 010 & 100 -> 000，相加吗？
  // 这样只能把x原来是0的和y原来是1的找出来，反过来应该也可以把y原来是0的和x原来是1的找出来
  int nx = ~x;
  int ny = ~y;
  int x0y1 = nx&y;
  int y0x1 = ny&x;
  // 然后需要把 y&nx 以及 x&ny 这两个相加起来，其实或也可以，所以现在是用 ~ 和 & 实现 |
  // 二者 非的与的非
  int res = ~((~x0y1)&(~y0x1)); 
  return res;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  int min = 1<<31;
  return min;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  // 这种只能保证是当前最大的
  // 但是不能保证是Tmax，位数不一样
  //int isMax = x+1 == ~x;
  int Tmin = x+1;
  
  // 如果是最大值，下面 x 将会变成 1111111111...
  x = x + Tmin;
  // 取补码就会变成 0000000000
  x = ~x;
  
  // 排除-1的情况
  // 如果是 -1的话，Tmin将会是0，那么！Tmin就是1，x此时也是0，但是加了1之后就是1
  Tmin = !Tmin;
  x = x + Tmin;
  return !x;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // 奇数位的都是1,101010那么就是1
  // 如果有一个不是，比如11111101，那么就是0
  // 0XAA是10101010总共八个
  int mask = 0XAAAA + (0XAAAA<<16);
  // 此时获得了x的所有奇数位
  x = mask&x;
  // 如果奇数位和mask不一样就不是 0
  x = x^mask;
  return !x;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x+1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int sign = 1<<31;
  // 考虑 ~x+1 即为负数,那么现在~（-9）作为upper， 000001010之类的，相加之后看看最高位是否为1
  // 其实就是变成0x39的补码，然后补码相加不就是最大的了吗？超过了就变成111111111
  int upper = ~(sign| 0x39);
  int lower = ~0x30;
  int larger = sign&(upper+x) >> 31;
  // lower类似思路，不过是不够大的那么最高位1就不会被置为0
  int smaller  = sign&(lower+1+x)>>31;
  return !(larger|smaller);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  x = !!x;
  // 此时x变成了要么是0要么是1，都代表自己原来的值
  // 0的话，补码加1还是0， 1的话，补码加1都是1
  x = ~x + 1;
  return (x&y)|(~x &z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  //int sign = 1<<31;
  // 判断y是不是比x大，但是要注意负数的怎么办
  // 符号不同，正数为大，符号相同，差值大小
  int negX = ~x + 1;
  int yMinusX = y+negX;
  int smaller = (yMinusX>>31)&1;

  int leftSign = 1<<31;
  int signX = x&leftSign;
  int signY = y&leftSign;
  int diff = ((signX^signY)>>31) & 1;

  return ((!diff)&& !smaller)|(diff && (signX>>31 &1));
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  // 0 就是1，否则都是 0
  // 如果是0，那么~x+1还是0,0|0还是0，0>>31+1就是1
  // 如果非0，那么~x+1 | x 最高位一定是1，算术右移就会导致11111111
  return ((x|(~x+1))>>31)+1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5 ; 01100
 *            howManyBits(298) = 10 
 *            howManyBits(-5) = 4 ; 1011
 *            howManyBits(0)  = 1 ; 0
 *            howManyBits(-1) = 1 ; 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int b16, b8, b4, b2, b1, b0;
  int sign = x>>31;
  x = (~sign&x)|(sign&(~x));


  //4和16是对应的，如果x>>16最高16位存在着1，那么！！之后就是1,1<<4 = 16
  b16 = !!(x>>16)<<4;
  // 这里是至少的意思，就是如果最高16位存在着1，那么至少要16位，然后把后面的16位删掉
  x = x>>b16;

  b8 = !!(x>>8)<<3;
  x = x>>b8;

  b4 = !!(x>>4)<<2;
  x = x>>b4;

  b2 = !!(x>>2)<<1;
  x = x>>b2;

  b1 = !!(x>>1);
  x = x>>b1;

  b0 = x;
  return b16+b8+b4+b2+b1+b0+1;
}



//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  int sign = uf&(1<<31);
  // 获取exp，可能前面还有一个sign
  int exp = (uf&0x7f800000)>>23;
  if(exp==0){
    // 0或者是无穷小，后面分别跟着的是0000，或者是非零的数
    return uf<<1|sign;
  }
  if(exp == 255){
    // exp == 255，那么就是无穷大或者是NaN, not a number
    return uf;
  }
  exp++;
  // 最后的形式是 (-1)^S * 2^(exp-bias[255]) *(1+F) (这个是小数部分) 
  if(exp==255) return 0x7f800000|sign;
  return (exp<<23)|(uf&0x807fffff);
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int sign = (uf>>31)&1;
  // 获取exp，可能前面还有一个sign
  int exp = ((uf&0x7f800000)>>23)-127;
  int F = (uf&0x7fffff)|0x00800000;
  if((uf& 0x7fffffff)==0){
    //如果是0, 除了第一位之外都是0
    return 0;
  }
  if(exp > 31){
    // 也就是后面至少要2^32次方，肯定是超了的
    return 0x80000000;
  }
  if(exp <0){
    return 0;
  }

  if(exp>23){
    // 如果exp==23,那么其实完全就不用动
    // 大于就往左边移，小于就往右边移动
    F = F << (exp-23);
  }else{
    F = F >> (23- exp);
  }
  if(!(F>>31)^sign){
    // 如果是同号，直接返回
    return F;
  }else if(F>>31){
    // 如果现在是负的，原来是正的，可能是左移的过程中导致了overflow，那么返回0
    return 0;
  }
  //原来是负的，现在是正的，直接取反就可以了
  return ~F+1;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  int bias = 127;
  // 实际上就是1.0 * 2^x，所以x实际上就是E
  // E = exp- 127
  // x = exp- 127
  // exp = x+127
  // 所以要看exp = E+127 = x+127,此时fraction部分是0，所以讨论exp的几种情况
  // 如果 x+127<-23,就代表要向右移至少24位，所以无穷小 
  if(x<-150) return 0;
  // 无穷小，或者精度已经达不到了，2^-24次方，但是fraction部分最多也就23 bits
  if(x>127) return 0xff<<23;
  // 无穷大，127 是 1111111（7个）,加上127就是254，如果是大于的就至少是255了，exp==255就是无穷大
  if(x<-127) return 0x1<<(150-x);


  /*
  int INF = 0xff<<23;
  int exp = x + 127;
  if(exp <= 0) return 0;
  if(exp >= 255) return INF;
  return exp << 23;
  */
  return (x+bias)<<23;
}
