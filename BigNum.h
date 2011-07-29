//Written by Jacob Haynes jacob.haynes@coloardo.edu 7/25/2010
//CSCI 2270 Summer 2010

// FYI: I helped Ariel Agular on this assignment


// FILENAME: BigNum.h
// This is the definition of the BigNum class.

// CONSTRUCTORS and DESTRUCTORS for BigNum class
//   BigNum() : Default constructor for BigNum class. A positive BigNum
//      with default value 0, base 0 is created after this constructor.
//   BigNum(int num, size_t base_num) : A BigNum with the same value and
//      sign as num is created after this function.
//   BigNum(const char string[]) : A BigNum with the corresponding integer
//     value of string[] is created after this function.
//   ~BigNum() : Dynamic memory allocated for the BigNum is released after
//     this function.
//
// PUBLIC MEMBER FUNCTIONS of BigNum class:
//   BigNum& operator=(const BigNum &anotherBigNum) : The BigNum has been
//     assigned the same value as anotherBigNum after this function is executed.
//   BigNum& operator+=(const BigNum &addend) : Addend has been added to
//     this BigNum after this function is executed.
//   BigNum& operator-=(const BigNum &subtractand) : Subtractand has been
//     subtracted from this BigNum after this function is executed.
//   BigNum& operator*=(const BigNum &multiplicand) : This BigNum has been
//     multiplied by multiplicand and the result is stored in this BigNum
//     after this function is executed.
//   BigNum& operator/=(const BigNum &divisor) : This BigNum has been divided
//     by divisor and the result has been stored in this BigNum after this
//     function is executed.
//   BigNum& operator%=(const BigNum &divisor) : This BigNum has been taken
//     modulus by divisor and the result has been stored in this BigNum after
//     this function is executed.
//   BigNum& operator++() : This BigNum has been incremented by 1 after
//     this function is executed.
//   BigNum& operator--() : This BigNum has been decremented by 1 after
//     this function is executed.
//   size_t get_used() const : Number of digits in this BigNum has been
//    returned after this function is executed.
//   void set_used(size_t new_used) : Number of digits in this BigNum has been
//    changed after this function is executed.  Precondition: new_used <
//    capacity.
//   size_t get_capacity() const : Size of the memory allocated for this
//    BigNum has been returned after this function is executed.
//   size_t get_base() const : Base for this BigNum has been returned
//    after this function is executed.
//   void set_base(size_t new_base) : Base for this BigNum has been changed
//    to new_base after this function is executed.
//   size_t get_digit(size_t index) const : digit at index for this BigNum
//    has been returned after this function is executed.
//   void set_digit(size_t value, size_t index) const :
//    Precondition: index < used (else reserve more memory before the call)
//    Postcondition: digit at index for this BigNum has been set to value
//    after this function is executed.
//   size_t get_sign() const : returns true if number is positive (>= 0)
//    and false otherwise
//   void set_sign(bool pos_or_neg) : sets sign to true if number is positive
//    (>= 0) and false otherwise
//
//  FRIEND FUNCTIONS of BigNum class:
//   friend std::ostream& operator<<(std::ostream &os, const BigNum &bignum) :
//    This bignum has been output to the console after this function is
//    executed. 
//   friend std::istream& operator>>(std::istream &is, BigNum &bignum) :
//    This BigNum entered from the console has been stored in bignum after
//    this function is executed.
//   friend BigNum operator+(const BigNum &n1, const BigNum& n2) :
//    The result of the addition of n1 and n2 has been returned after this
//    function is executed and neither n1 nor n2 have been changed.
//    You may have to convert n1 or n2 to the other's base before adding.
//   friend BigNum operator-(const BigNum &n1, const BigNum& n2) :
//    The result of the subtraction of n2 from n1 has been returned after this
//    function is executed and neither n1 nor n2 have been changed.
//    You may have to convert n1 or n2 to the other's base before subtracting.
//   friend BigNum operator*(const BigNum &n1, const BigNum& n2) :
//    The result of the multiplication of n1 and n2 has been returned after
//    this function is executed and neither n1 nor n2 have been changed.
//    You may have to convert n1 or n2 to the other's base before multiplying.
//   friend BigNum operator/(const BigNum &n1, const BigNum& n2) :
//    The result of the division of n1 by n2 has been returned after this
//    function is executed and neither n1 nor n2 have been changed.
//    You may have to convert n1 or n2 to the other's base before dividing.
//   friend BigNum operator%(const BigNum &n1, const BigNum& n2) :
//    The modulus (remainder) of the division of n1 by n2 has been returned
//    after this function is executed and neither n1 nor n2 have been changed.
//    You may have to convert n1 or n2 to the other's base before the division.
//   friend factorial(const BigNum& num) : Factorial of this BigNum has been
//    returned after this function is executed and num is unchanged.
//    

//  NONMEMBER FUNCTIONS of BigNum class:
//  bool operator>(const BigNum &n1, const BigNum& n2): True will be
//   returned if this BigNum is bigger than anotherBigNum, otherwise false
//   will be returned.  You may have to convert n1 or n2 to the other's base.
//  bool operator>=(const BigNum &n1, const BigNum& n2) : True will be
//   returned if this BigNum is bigger than or equal to anotherBigNum,
//   otherwise false will be returned. You may have to convert n1 or n2 to
//   the other's base.
//  bool operator<(const BigNum &n1, const BigNum& n2) :  True will be
//   returned if this BigNum is smaller than anotherBigNum, otherwise false
//   will be returned. You may have to convert n1 or n2 to
//   the other's base.
//  bool operator<=(const BigNum &n1, const BigNum& n2) :  True will be
//   returned if this BigNum is smaller than or equal to anotherBigNum,
//   otherwise false will be returned. You may have to convert n1 or n2 to
//   the other's base.
//  bool operator==(const BigNum &n1, const BigNum& n2) :  True will be
//   returned if this BigNum is equal to anotherBigNum, otherwise false
//   will be returned. You may have to convert n1 or n2 to
//   the other's base.
//  bool operator!=(const BigNum &n1, const BigNum& n2) : True will be
//   returned if this BigNum is not equal to anotherBigNum, otherwise false
//   will be returned. You may have to convert n1 or n2 to the same base.
//  BigNum convert_to_base10(const BigNum &b): Returns the base 10 equivalent
//   of the number b.  BigNum b is unchanged.
//  BigNum convert_base10_to_another(const BigNum &b, size_t new_base):
//   returns the base 'new_base' equivalent of the number b.  BigNum b is
//   unchanged.

// PRIVATE MEMBER FUNCTIONS of BigNum class:
//  void reserve(size_t n) : Size of the memory allocated for this BigNum
//   has been changed to n after this function is executed. If n is smaller
//   than the length of this BigNum, this BigNum will not be resized.           
//  BigNum  diff(const BigNum &subtractand) : Precondition is that both this
//   BigNum and subtractand are positive, have the same base, and also that
//   this BigNum >= subtractand. The result of subtraction has been returned
//   after this function is executed.
//  BigNum sum(const BigNum &addend) : Precondition is that both this BigNum
//   and addend are positive, have the same base, and this BigNum >= addend.
//   The result of addition has been returned after this function is executed.


#ifndef HW1B_BIGNUM_H
#define HW1B_BIGNUM_H
#include <cstdlib>  // Provides size_t
#include <iostream> // Provides istream and ostream
#include <assert.h>
#include <string.h>
#include <math.h>

namespace Jacob_Haynes_BigNum
{
    class BigNum 
    {
    public:
	
	// CONSTRUCTORS and DESTRUCTORS
	BigNum();                            
	BigNum(int num, size_t optional_base = 10);           
	BigNum(const char strin[], size_t optional_base = 10);
	BigNum(const BigNum& anotherBigNum);  
	~BigNum();
	
	
	// MEMBER FUNCTIONS
	size_t get_digit(size_t index) const;
	size_t get_used() const;
	size_t get_capacity() const;
	size_t get_base() const;
	bool get_sign() const;
	
	BigNum& operator=(const BigNum &anotherBigNum);
	BigNum& operator+=(const BigNum &addend);
	BigNum& operator-=(const BigNum &subtractand);
	BigNum& operator*=(const BigNum &multiplicand);
	BigNum& operator/=(const BigNum &divisor);
	BigNum& operator%=(const BigNum &divisor);
	BigNum& operator++();  // overload prefix increment
	BigNum& operator--();  // overload prefix decrement
	
	// FRIEND FUNCTIONS
	friend std::ostream& operator<<(std::ostream &os, const BigNum &bignum);
	friend std::istream& operator>>(std::istream &is, BigNum &bignum);
	friend BigNum operator+(const BigNum &n1, const BigNum &n2);
	friend BigNum operator-(const BigNum &n1, const BigNum &n2);
	friend BigNum operator*(const BigNum &n1, const BigNum &n2);
	friend BigNum operator/(const BigNum &n1, const BigNum &n2);
	friend BigNum operator%(const BigNum &n1, const BigNum &n2);
	friend BigNum factorial(const BigNum &num);
	friend BigNum convert_base(const BigNum &b, size_t new_base);
	friend BigNum convert_to_base10(const BigNum &b);
	friend BigNum convert_base10_to_another(const BigNum &b,
						size_t new_base);


    private:
	size_t base;            // Base of number (2-16)
	size_t *digits;         // Pointer to the array of BigNum digits 
	bool positive;          // Indicates the sign of BigNum (true for positive, false for negative)
	size_t used;            // Length of the array for BigNum Digits  
	size_t capacity;        // Size of the memory allocated for tis BigNum 
	void reserve(size_t n); // resize the digits array
	BigNum diff(const BigNum &subtractand) const; // simple subtraction
	BigNum sum(const BigNum &addend) const; // simple addition
	
	void set_digit(size_t digit, size_t index); // set a digit
	void set_used(size_t new_used); // set the overall number of digits
	void set_base(size_t new_base); // set the number's base
	void set_sign(bool pos_or_neg); // set true for >= 0, false otherwise
	void trim();
	void push_in(size_t digit); //adds a digit to the ones place and pushes everything else up
	
	
	static const size_t DEFAULT_CAPACITY = 20; 
    };

    // nonmember functions
    bool operator>(const BigNum &n1, const BigNum &n2);
    bool operator>=(const BigNum &n1, const BigNum &n2);
    bool operator<(const BigNum &n1, const BigNum &n2);
    bool operator<=(const BigNum &n1, const BigNum &n2);
    bool operator==(const BigNum &n1, const BigNum &n2);
    bool operator!=(const BigNum &n1, const BigNum &n2);

}

#endif

