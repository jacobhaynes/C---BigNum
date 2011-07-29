#include <iostream>
#include <cstdlib>
#include "BigNum.h"

using namespace std;
using namespace Jacob_Haynes_BigNum;

int main()
{
/*
 // cout << "CONSTRUCTOR TESTS" << endl;
  BigNum test1;
//cout << test1 << endl;
  BigNum test2 = 243;
//	cout << test2 << endl;
  BigNum test3 = -243;
//	cout << test3 << endl;
  BigNum test4 = 0;
	//cout << test4 << endl;
  BigNum test5 = 3458919;
//cout << test5 << endl;
  BigNum test6 = "0";
//cout << test6 << endl;
  BigNum test7 = "9997632187383270741827";
//cout << test7 << endl;
  BigNum test8 = "-9997632187383270741827";
//cout << test8 << endl;
  BigNum test9 = "-0008";
//cout << test9 << endl;
  BigNum test10 = "-3458919728786732132";
//cout << test10 << endl;
//cout << endl;

  BigNum test11 = test2;
//cout << test11 << endl;
  BigNum test12 = test10;
//cout << test12 << endl;
  BigNum test13 = test3;
//cout << test13 << endl;
  BigNum test14 = test5;
//cout << test14 << endl;

 // cout << "ASSIGNMENT OPERATOR" << endl;
  BigNum test15;
  test15 = test5;
//cout << test15 << endl; 
 BigNum test16;cout << endl << endl << endl;
  test16 = test10 = test11;
//cout << test16 << endl;
  BigNum test17;
  test17 = test1;
//cout << test17 << endl;
  BigNum test18;
  test18 = test8;
//cout << test18 << endl;
  BigNum test18b = 76878;
  test18b = test18b;
///cout << test18b << endl;

*/
//My tests
//hex a = hex 1816F3053;
//int b = hex 184131;
cout << endl << endl << endl;
BigNum less = 3;
BigNum more = 5;
cout << "less " << (less < more) << endl;
BigNum jtest1 = BigNum("l64545", 36);
BigNum jtest2 = BigNum("a8448", 36);


//cout << (jtest2 + BigNum(1, 16)) * BigNum(16, 16) << endl;

//cout << "Enter a number for the factorial: ";
//cin >> jtest2;
cout << "add" << endl;
BigNum jtest3 = jtest1 + jtest2;
cout << jtest3 << endl;
cout << "----multiply----" << endl;
BigNum jtest4 = jtest1 * jtest2;

cout << jtest4 << endl;
//cout << "real " << a*b << endl;
cout << "----divide----" << endl;
cout << jtest1 / jtest2 << endl; 
//cout << "real " << a/b << endl;
cout << "----modulus----" << endl;
cout << jtest1 % jtest2 << endl;
//cout << "real " << a%b << endl;
//cout << "----factorial----" << endl;
//cout << factorial(jtest1) << endl;
cout << "----base 10-----" << endl;
BigNum jtest5 = convert_to_base10(jtest2);
cout << jtest5 << endl;
cout << "----base2-----" << endl;
cout << convert_base(jtest2, 2) << endl;
cout << "----10 to 16-----" << endl;
cout << convert_base10_to_another(jtest5, 16) << endl;
cout << "-----------------" << endl;
cout << "Enter a number into BigNum" << endl;
BigNum jtest6;
//cin >> jtest6;
//cout << factorial(820) << endl;
cout << endl << jtest6 << endl;
}
