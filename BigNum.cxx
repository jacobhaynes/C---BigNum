#include "BigNum.h"
using namespace std; 
 
namespace Jacob_Haynes_BigNum
{
	// CONSTRUCTORS and DESTRUCTORS
	//-------------------------------------------------------------------//
	BigNum::BigNum()
	{
	base = 10;
	positive = true;
	used = 1;
	capacity = DEFAULT_CAPACITY;
	digits = new size_t[capacity];
	digits[0] = 0;
	return;
	}  
	//-------------------------------------------------------------------//
	BigNum::BigNum(int num, size_t optional_base) 
	{
		base = optional_base;
		positive = true;
		capacity = DEFAULT_CAPACITY;
		if(num < 0)
		{
			positive = false;
			num *= -1;
		}
		digits = new size_t[capacity];
		used = 0;

		if(num == 0)
		{
			used = 1;
			digits[0] = 0;
		}
				

		while(num > 0)
		{
			digits[used] = num % base;
			num /= base;
			used++;
		}
		trim();
		return;
	}
	//-------------------------------------------------------------------//
	BigNum::BigNum(const char strin[], size_t optional_base)
	{
		size_t size = strlen(strin);
		base = optional_base;
		positive = true;
		capacity = size;

		digits = new size_t[capacity];
		used = 0;
		while(used < size)
		{
			//if it is a negative sign, make the number negative
			if(strin[size - used - 1] == '-')
				{
				positive = false;
				size--;
				}
			//if it is a positive sign, skip it
			else if (strin[size - used - 1] == '+')
				size-- ;
			else 
			{
				//1-10 and only in base 
				if(strin[size - used - 1] >= '0' && 
					strin[size - used -1] <= '9' &&
					strin[size - used -1] <= 
								'0'+ signed(base) - 1)
					digits[used] = strin[size -used - 1] - '0';
				//Upper Case ABCDE and only if of is part of the base
				else if(strin[size - used - 1] >= 'A' && 
					strin[size - used -1] <= 
							'A' + signed(base) - 10)
					digits[used] = strin[size -used - 1] -'A' + 10;
				//Lower Case abcde and only if it is part of the base
				else if(strin[size - used - 1] >= 'a' && 
					strin[size - used -1] <= 
							'a' + signed(base) - 10)
					digits[used] = strin[size -used - 1] -'a' +10;
				//not a good character
				else
				{
					cout << "Invalid Charicter" << endl;
					throw("Invalid Charicter");
				}
				used++;
			}
		}
		trim();
		return;
	}
	//-------------------------------------------------------------------//
	BigNum::BigNum(const BigNum& anotherBigNum)
	{
		digits = NULL;
		*this = anotherBigNum;
	} 
	//-------------------------------------------------------------------//
	BigNum::~BigNum()
	{
		delete[] digits;
	}
	//-------------------------------------------------------------------//
	size_t BigNum::get_digit(size_t index) const
	{
		return digits[index];
	}
	//-------------------------------------------------------------------//
	size_t BigNum::get_used() const
	{
		return used;
	}
	//-------------------------------------------------------------------//
	size_t BigNum::get_capacity() const
	{
		return capacity;
	}
	//-------------------------------------------------------------------//
	size_t BigNum::get_base() const
	{
		return base;
	}
	//-------------------------------------------------------------------//
	bool BigNum::get_sign() const
	{
		return positive;
	}
	//-------------------------------------------------------------------//	
	BigNum& BigNum::operator=(const BigNum &anotherBigNum)
	{
		//if they are in the same location
		if(this == &anotherBigNum)
			return *this;
		
		base = anotherBigNum.get_base();
		positive = anotherBigNum.get_sign();
		capacity = anotherBigNum.get_capacity();
		if (digits != NULL)
			delete [] digits;
		digits = new size_t[capacity];
		used = anotherBigNum.get_used();
		for(size_t i = 0; i <= used; i++)
			digits[i] = anotherBigNum.get_digit(i);
		trim();
		return *this;
	}
	//-------------------------------------------------------------------//
	BigNum& BigNum::operator+=(const BigNum &addend)
	{
		*this = *this + addend;
		return *this;
	}
	//-------------------------------------------------------------------//
	BigNum& BigNum::operator-=(const BigNum &subtractand)
	{
		*this = *this - subtractand;
		return *this;
	}
	//-------------------------------------------------------------------//
	BigNum& BigNum::operator*=(const BigNum &multiplicand)
	{
		*this = *this * multiplicand;
		return *this;
	}
	//-------------------------------------------------------------------//	
	BigNum& BigNum::operator/=(const BigNum &divisor)
	{
		*this = *this * divisor;
		return *this;
	}
	//-------------------------------------------------------------------//
	BigNum& BigNum::operator%=(const BigNum &divisor)
	{
		*this = *this * divisor;
		return *this;
	}
	//-------------------------------------------------------------------//
	// overload prefix increment
	BigNum& BigNum::operator++()
	{
		*this = *this + BigNum(1, base);
		return *this;
	}  
	//-------------------------------------------------------------------//
	BigNum& BigNum::operator--()  // overload prefix decrement
	{
		*this = *this - BigNum(1, base);
		return *this;
	}  
	//-------------------------------------------------------------------//
	


	// FRIEND FUNCTIONS 
	//-------------------------------------------------------------------//
	 std::ostream& operator<<(std::ostream &os, const BigNum &bignum)
	{
		if(!bignum.get_sign())
			os << "-";
		for(size_t i = 0; i < bignum.get_used(); i++)
		{
			//handls 0-9
			if (bignum.get_digit(bignum.get_used() - i - 1) < 10)
				os << bignum.get_digit(bignum.get_used() - i - 1);
			//handles above base 10			
			else
				os << char(bignum.get_digit(bignum.get_used() - i - 1)
					+ 'A' - 10);
		}
		return os;
	}
	//-------------------------------------------------------------------//	
	 std::istream& operator>>(std::istream &is, BigNum &bignum)
	{	
		//puts everything into the bignum string constructor
		char temp[] = "0";
 		is >> temp;
		bignum = BigNum(temp);
		return is;
	}
	//-------------------------------------------------------------------//
	 BigNum operator+(const BigNum &n1, const BigNum &n2)
	{	
		//changes base
		if(n1.get_base() != n2.get_base())
			return n1 + convert_base(n2, n1.get_base());
		//checks they are in the same base	
		assert(n1.get_base() == n2.get_base());
		
		size_t base = n1.get_base();
		int temp = 0;
		bool borrowed = false;
		BigNum result = BigNum(0, base);
		BigNum neg = BigNum(-1, n1.get_base());
		result.set_used(1); 


		//check if they are empty
		if(n1 == BigNum(0, n1.get_base()))
		{
			if(n2 ==  BigNum(0, n1.get_base())) //if they are both empty 
				return result; 	// return empty BigNum 
			else //if n1 is empty return n2
				return n2; 
		}
		else if(n2 ==  BigNum(0, n1.get_base())) //if n2 is empty return n1
			return n1;

		//if negative check if the answer will be positive
		if(!n1.get_sign())
		{
			//if the original result is going to be negative
			if(!n2.get_sign() || (n1 * neg) > n2)
			{
				//this is a recuvrsive call that makes the
				// + operator return a positive
				//and then flips the sign
				BigNum temp = (n1 * neg + n2 * neg);
				return temp * neg;
			}

		}
		else if(!n2.get_sign()) //if the original answer is negative
		{
		
			if(n1 < (n2 * neg))
			{
				return (n1 * neg + n2 * neg) * neg;
			}
		}
			

		//reserving space for all digits
		if(n1.get_used() >= n2.get_used())
			result.reserve(n1.get_used() + 1);
		else
			result.reserve(n2.get_used() + 1);

		//goes through all digits
		for(size_t i = 0; i <= result.get_capacity(); i++)
		{	
			if(i < n1.get_used() || i < n2.get_used() || temp != 0)
				result.set_used(result.get_used() + 1);
			//checks if it is used
			if(i < n1.get_used())
				//ads the digit and multiplys it by negative
				// if it is negaitve
				temp += n1.get_digit(i) * 
						(n1.get_sign() * 2 - 1);

			if(i < n2.get_used())
				temp += n2.get_digit(i) * 
						(n2.get_sign() * 2 - 1);	
			
			//borrows
			if(temp < 0)
			{
				borrowed = true;
				temp += n1.get_base();			
			}
			
			//makes result(digit) equal to the 1 place of temp
			result.set_digit(temp % n1.get_base(), i); 
			//passes up the tens place
			temp /= n1.get_base();
		
			//retruns borrowed number
			if(borrowed)
			{
				borrowed = false;
				temp--;
			}
			
		}
		result.trim();
		return result;
	}
	//-------------------------------------------------------------------//
	 BigNum operator-(const BigNum &n1, const BigNum &n2)
	{
		BigNum negative = BigNum(-1, n1.get_base());
		return n1 + (n2 * negative);
	}
	//-------------------------------------------------------------------//
	 BigNum operator*(const BigNum &n1, const BigNum &n2)
	{	
		//converts base
		if(n1.get_base() != n2.get_base())
			return n1 * convert_base(n2, n1.get_base());
		assert(n1.get_base() == n2.get_base());
		size_t base = n1.get_base();

		BigNum result = BigNum(0, base);
		
		BigNum neg = BigNum(-1, base);
		
		BigNum remander = BigNum(0, base);
		//if they are both zero, must have for safe recursive calls
		if(n1 == BigNum(0, base) || n2 == BigNum(0, n2.get_base()))
		{
			return result;
		}
		//if one is -1, must have for safe recursion
		if(n1 == neg) 
		{	
			result = n2;
			result.set_sign(n1.get_sign() == n2.get_sign());
			return result;
		}
		if(n2 == neg) 
		{	
			result = n1;
			result.set_sign(n1.get_sign() == n2.get_sign());
			return result;
		}	

		//adds a trailing zero if it is multiplied by its base
		//Must have for safe recursion
		if(n2 == BigNum(n2.get_base(), n2.get_base()))
		{
			result = n1;
			result.push_in(0);	
			return result;	
		}
		if(n1 == BigNum(n1.get_base(), base))
		{	
			result = n2;
			result.push_in(0);	
			return result;	
		}
	
		//if they are only one long, return the multiplication
		if(n1.get_used() == 1 && n2.get_used() == 1)
		{
			result = BigNum(n1.get_digit(0) * n2.get_digit(0), base);
		}
		else
		{
			//if they aren't one long, do a recursive 
			//multiplication untill they are. 
			//It is n2 * a digit of n1 which ensures that it 				
			//always get smaller and won't go into an infinate loop
			for(size_t i = 0; i < n1.get_used(); i++)
			{
				//adds a zero to the result because that is 
				//what you do when multiplying
				result *= BigNum(base, base);//, it will be negat
				//recursive call
				result +=  n2 * BigNum(n1.get_digit(n1.get_used() - i - 1), base);
			}
			
		}

		//if they are both positive or negative,
		// the result will be positive 
		//if not, it will be negative		
		if(n1.get_sign() == n2.get_sign())
		{
			result.set_sign(true);
		}
		else
		{
			result.set_sign(false);
		}

		result.trim();
		return result;
	}
	//-------------------------------------------------------------------//
	 BigNum operator/(const BigNum &n1, const BigNum &n2)
	{
		if(n1.get_base() != n2.get_base())
			return n1 / convert_base(n2, n1.get_base());
		assert(n2 != BigNum(0, n2.get_base()) && n1.get_base() == n2.get_base());
		size_t base = n1.get_base();
		
		BigNum result = BigNum(0, base);
	
		BigNum remander = BigNum(0, base);

		BigNum this_digit = BigNum(0, base);

		//size_t this_digit = 0;

		//in intiger division, if it is smaller than one, return 0; 
		//this makes the recursion safe
		if(n2 * BigNum((n2.get_sign() * 2 - 1), base) > 
				n1 * BigNum((n1.get_sign() * 2 - 1), base))
			return result;
		
		//;=;=;=;=;=;=;long division;=;=;=;=;=;=;//
		for(size_t i = 0; i < n1.get_used(); i++)
		{
			//subtracts what needs to be subtracted
			remander -= n2 * this_digit *
				BigNum((n2.get_sign() * 2 - 1), base);
			//sets the next digit to zero
			this_digit = BigNum(0, base);	
			
			//moves the remander to the next place
			remander *= BigNum(base, base);

			//adds the next digit to the remander
			remander += BigNum(n1.get_digit(n1.get_used() - i - 1), base);


			while(remander >= (n2 * (this_digit + BigNum(1, base)) *
						BigNum(n2.get_sign() * 2 - 1, base)))
			++this_digit; 
			//sets the results
			result += this_digit *
					BigNum(pow(base,n1.get_used() - i -1), base);
			
		}

		//if they are both positive or negative,the result is positive 
		//if not, it will be negative
		if(n1.get_sign() == n2.get_sign())
			result.set_sign(true);		
		else
			result.set_sign(false);

		result.trim();
		return result;
	}
	//-------------------------------------------------------------------//
	 BigNum operator%(const BigNum &n1, const BigNum &n2)
	{
		return n1 - (n1 / n2) * n2;
	}
	//-------------------------------------------------------------------//
	 BigNum factorial(const BigNum &num)
	{
		//must have for safe recursion
		if(num <= BigNum(1, num.get_base()))
			return  BigNum(1, num.get_base());
		return num * factorial(num - 1);
	}
	//-------------------------------------------------------------------//
	BigNum convert_base(const BigNum &b, size_t new_base)
	{
		BigNum result = BigNum(0, new_base);
		BigNum temp;
		//handles negative numbers which would break the function
		if(b.get_sign() == 0)
			return convert_base(b*BigNum(-1, b.get_base()), new_base)
					* BigNum(-1, new_base);
		//if b is greater than 1, recuvrsive call
 		if(b > BigNum(1, b.get_base()))
			result = convert_base(b / BigNum(new_base, b.get_base()), 
					new_base) * BigNum(new_base, new_base); 
		//gets this digit
		temp =  b % BigNum(new_base, b.get_base());
		//changes the base to the other base
		temp.set_base(new_base);
		//these for loops are here for when the original base is bigger 
		//than the older base
		for(size_t j = 0; j < temp.get_used(); j++)
			for(size_t i = 0; temp.get_digit(j) > 1 || i == 0; i++)
			{
				result += BigNum(temp.get_digit(j) *
						 pow(b.get_base(),i) *
						 pow(b.get_base(), j)
						, new_base);
				temp.set_digit(temp.get_digit(j) / new_base, 0);
			}

		return result;

	}
	//-------------------------------------------------------------------//
	 BigNum convert_to_base10(const BigNum &b)
	{
		return convert_base(b, 10);
	}
	//---------------------
----------------------------------------------//
	 BigNum convert_base10_to_another(const BigNum &b,
						size_t new_base)
	{
		assert(b.get_base() == 10);
		return convert_base(b, new_base);
	}
	//-------------------------------------------------------------------//
	void BigNum::reserve(size_t n)
	{
		size_t k = DEFAULT_CAPACITY;
		while (k <=  n)
			k *= 2;
		capacity = k;
		size_t *old_digits = digits;
		digits = new size_t[capacity];
		for(size_t i = 0; i < used; i++)
			digits[i] = old_digits[i];
		if(old_digits != NULL)
			delete [] old_digits;
	} // resize the digits array
	//-------------------------------------------------------------------//

	BigNum BigNum::diff(const BigNum &subtractand) const
	{
		return *this - subtractand;
	} // simple subtraction

	BigNum BigNum::sum(const BigNum &addend) const
	{
		return *this + addend;
	} // simple addition
	//-------------------------------------------------------------------//
	// set a digit	
	void BigNum::set_digit(size_t digit, size_t index)
	{
		assert(capacity >= index);
		digits[index] = digit;
	} 
	//-------------------------------------------------------------------//
	void BigNum::set_used(size_t new_used) // set the number of digits
	{
		assert(capacity >= used);
		used = new_used;
	}
	//-------------------------------------------------------------------//
	void BigNum::set_base(size_t new_base) // set the number's base
	{
		base = new_base;
	}
	//-------------------------------------------------------------------//
	void BigNum::set_sign(bool pos_or_neg)
	{
		positive = pos_or_neg;	
	} // set true for >= 0, false otherwise
	//-------------------------------------------------------------------//
	void BigNum::trim()
	{
		//Remove first digit if it is a zero and it isn't the only digit
		if(used > 1 && get_digit(used - 1) == 0)
		{
			used--;
			trim();
		}
	}
	//-------------------------------------------------------------------//
	void BigNum::push_in(size_t digit)
	{
		reserve(get_used() + 1);
		for(size_t i = 0; i < used; i++)
		{
			digits[used - i] = digits[used - i - 1];
		}
		digits[0] = digit;
		used++;
	}
	//-------------------------------------------------------------------//	

    
	// nonmember functions
	//-------------------------------------------------------------------//
	bool operator>(const BigNum &n1, const BigNum &n2)
	{
		if(n1.get_base() != n2.get_base())
			return n1 > convert_base(n2, n1.get_base());
		assert(n1.get_base() == n2.get_base());

		if(n1 == n2)
			return false;

		if(n1.get_sign() < n2.get_sign())
			return false;
		if(n1.get_sign() > n2.get_sign())
			return true;

		if(n1.get_used() < n2.get_used())
			return !n1.get_sign();
		if(n1.get_used() > n2.get_used())
			return n1.get_sign();

		for(size_t i = 0; i < n1.get_used(); i++)
		{
			if(n1.get_digit(n1.get_used() - i - 1) < 
				n2.get_digit(n2.get_used() - i - 1))
				return !n1.get_sign();
			if(n1.get_digit(n1.get_used() - i - 1) >
				n2.get_digit(n2.get_used() - i - 1))
				return n1.get_sign();
		}		
		return false;
	}
	//-------------------------------------------------------------------//
	bool operator>=(const BigNum &n1, const BigNum &n2)
	{
		return !(n1 < n2);
	}
	//-------------------------------------------------------------------//    
	bool operator<(const BigNum &n1, const BigNum &n2)
	{
		return !(n1 > n2) && !(n1 == n2);
	}
	//-------------------------------------------------------------------//    
	bool operator<=(const BigNum &n1, const BigNum &n2)
	{
		return !(n1 > n2);
	}
	//-------------------------------------------------------------------//    
	bool operator==(const BigNum &n1, const BigNum &n2)
	{
		if(n1.get_base() != n2.get_base())
			return (n1 == convert_base(n2, n1.get_base()));

		if(n1.get_base() != n2.get_base())
			return false;
		if(n1.get_used() != n2.get_used())
			return false;
		if(n1.get_sign() != n2.get_sign())
			return false;

		for(size_t i = 0; i < n1.get_used(); i++)
		{
			if(n1.get_digit(i) != n2.get_digit(i))
				return false;

		} 
		return true;
	}
	//-------------------------------------------------------------------//
	bool operator!=(const BigNum &n1, const BigNum &n2)
	{
		return !(n1 == n2);
	}
	//-------------------------------------------------------------------//
}
