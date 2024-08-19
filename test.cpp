#include "numeric_parameter.hpp" 
#include <iostream> 
#include <algorithm>

// This is Scott Meyer's example class from his article
// Signed and Unsigned Types in Interfaces
// https://www.aristeia.com/Papers/C++ReportColumns/sep95.pdf
// I added the stream output
//
template<class T>
class Array
{
public:
    Array(unsigned int size) : m_size(size)
    {
        std::cout << "Array's size is " << size << std::endl;
    }
    
    unsigned int length() const
    {
        std::cout << "Array's length is " << m_size << std::endl; 
        return m_size;
    }
private:
    unsigned int m_size;
};


int f()
{
    return 1;
};

int g()
{
    return 2;
};


void scottsExampleUsage()
{
    std::cout << "Scott Meyer's example to create an array with negative size" << std::endl;
    std::cout << "creating Array type variable a with size " << f() - g() << std::endl;
    Array<double> a(f() - g());

    std::cout << std::endl;

    std::cout << "Scott Meyer's example to get array length created with negative size" << std::endl;
    std::cout << "getting length of a to int variable arraySize" << std::endl;
    int arraySize = a.length();
    std::cout << "a length to int : " << arraySize << std::endl;
    std::cout<< std::endl << std::endl;
}

// This is the Array class improvement using NumericParameter that does
// bounds checking
template<typename T>
class Array2
{
public:
    Array2(NumericParameter<unsigned int> size) : m_size(size)
    {
        std::cout << "Array2's size is " << m_size << std::endl;
    }
    
    NumericParameter<unsigned int> length() const
    {
        return m_size;
    }
    
private:
    unsigned int m_size;
};

void scottsExampleWithNumericParameterUsage()
{
    std::cout << "Scott Meyer's example using NumericParamter class to create an array with negative size" << std::endl;
    try
    {
        std::cout << "creating Array2 type variable a2 with size " << f() - g() << std::endl;
        Array2<double> a2(f() - g());
    }
    catch(const std::bad_cast &e)
    {
        std::cout << "a2 constructor caught " << e.what() << " exception" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Scott Meyer's example to using NumericParamete to get array length" << std::endl;
    std::cout << "creating Array2 type variable a3 with size " << std::numeric_limits<unsigned int>::max() << std::endl;
    Array2<double> a3(std::numeric_limits<unsigned int>::max());

    try
    {
        std::cout << "getting length of a3 to unsigned int variable array3Size" << std::endl;
        unsigned int array3Size = a3.length();
        std::cout << "a3 length to unsigned int variable array3Size : " << array3Size << std::endl;
    }
    catch(const std::bad_cast &e)
    {
        std::cout << "a3 length to unsigned int variable array3Size caught " << e.what() << " exception" << std::endl;
    }

    std::cout << std::endl;
    
    try
    {
        std::cout << "getting length of a3 to int variable array3Size" << std::endl;
        int array3Size = a3.length();
        std::cout << "a3 length to int variable array3Size : " << array3Size << std::endl;
    }
    catch(const std::bad_cast &e)
    {
        std::cout << "a3 length to int variable array3Size caught " << e.what() << " exception" << std::endl;
    }
    std::cout <<std::endl << std::endl;
}

//Support functions to full test NumericParameter
int returnInt(NumericParameter<int> i)
{
    return i;
}

NumericParameter<int> returnValidInt(NumericParameter<unsigned long> l)
{
    return NumericParameter<int>(l);
}

NumericParameter<int> returnAnotherValidInt(NumericParameter<unsigned long> l)
{
    return l;
}

NumericParameter<unsigned int> returnAnotherValidUnsignedInt(NumericParameter<long> l)
{
    return l;
}

class NonValue
{
};

// 
void fullTestCasesWithNumericParameter()
{
    std::cout << "Fully testing the NumericParameter class for all test cases" << std::endl;
    unsigned long unsignedLongMax = std::numeric_limits<unsigned long>::max();

    try
    {
        std::cout << "Test 1 Numeric Parameter to variable: ";
        int i = NumericParameter<int>(unsignedLongMax);

        std::cout << " Should never happen" << std::endl;
        std::cout << "long value was " << unsignedLongMax << " int value is " << i << std::endl;
    }
    catch(boost::numeric::negative_overflow& e)
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }
    catch(boost::numeric::positive_overflow& e)
    {
            
        std::cout << "Positive Overflow into an int variable, long value was " << unsignedLongMax << std::endl;
    }
    catch(boost::numeric::bad_numeric_cast& e)
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }

    try
    {
        std::cout << "Test 2 Numeric parameter into function overflow: ";
        int i = returnInt(unsignedLongMax);

        std::cout << " Should never happen" << std::endl;
        std::cout << "Was long value " << unsignedLongMax << " returned int value is " << i << std::endl;
    }
    catch(boost::numeric::negative_overflow& e)
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }
    catch(boost::numeric::positive_overflow& e)
    {
        std::cout << "Positive Overflow into a function expecting an int, long value was " << unsignedLongMax << std::endl;
    }
    catch(boost::numeric::bad_numeric_cast& e)
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }

    try
    {
        std::cout << "Test 3 Numeric parameter to function valid: ";

        long l2 = 12; 
        int i = returnInt(l2);

        std::cout << "Was long value " << l2 << " returned int value is " << i << std::endl;
    }
    catch(boost::numeric::negative_overflow& e)
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }
    catch(boost::numeric::positive_overflow& e)
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }
    catch(boost::numeric::bad_numeric_cast& e)
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }

    try
    {
        std::cout << "Test 4 Numeric parameter returned from function valid: ";

        long l2 = 34; 
        int i = returnValidInt(l2);

        std::cout << "Was long value " << l2 << " returned int value is " << i << std::endl;
    }
    catch(boost::numeric::negative_overflow& e)
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }
    catch(boost::numeric::positive_overflow& e)
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }
    catch(boost::numeric::bad_numeric_cast& e)
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }

    try
    {
        std::cout << "Test 5 Numeric parameter returned from function overflow: ";

        unsigned long l2 = unsignedLongMax; 
        int i = returnValidInt(l2);

        std::cout << " Should never happen" << std::endl;
        std::cout << "Was long value " << l2 << " returned int value is " << i << std::endl;
    }
    catch(boost::numeric::negative_overflow& e)
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }
    catch(boost::numeric::positive_overflow& e)
    {
        std::cout << "Positive Overflow function return value must be int, long value was " << unsignedLongMax << std::endl;
    }
    catch(boost::numeric::bad_numeric_cast& e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        std::cout << "Test 6 Numeric parameter returned from another function valid: ";

        unsigned long l2 = 56;
        int i = returnAnotherValidInt(l2);

        std::cout << "Was long value " << l2 << " returned int value is " << i << std::endl;
    }
    catch(boost::numeric::negative_overflow& e) 
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }
    catch(boost::numeric::positive_overflow& e) 
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }
    catch(boost::numeric::bad_numeric_cast& e) 
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }

    try
    {
        std::cout << "Test 7 Numeric parameter returned from another function overflow: ";

        unsigned long l2 = unsignedLongMax;
        int i = returnAnotherValidInt(l2);

        std::cout << " Should never happen" << std::endl;
        std::cout << "Was long value " << l2 << " returned int value is " << i << std::endl;
    }
    catch(boost::numeric::negative_overflow& e) 
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }
    catch(boost::numeric::positive_overflow& e) 
    {
        std::cout << "Positive Overflow function return value must be int. long value was " << unsignedLongMax << std::endl;
    }
    catch(boost::numeric::bad_numeric_cast& e) 
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }

    try
    {
        std::cout << "Test 8 Numeric parameter returned from another function overflow: ";

        long l2 = -1;
        int i = returnAnotherValidUnsignedInt(l2);

        std::cout << " Should never happen" << std::endl;
        std::cout << "Was long value " << l2 << " returned int value is " << i << std::endl;
    }
    catch(boost::numeric::negative_overflow& e) 
    {
        std::cout << "Negative Overflow function return value must be unsigned int, long value was -1" << std::endl;
    }
    catch(boost::numeric::positive_overflow& e) 
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }
    catch(boost::numeric::bad_numeric_cast& e) 
    {
        std::cout << " Should never happen" << std::endl;
        std::cout << e.what() << std::endl;
    }

  /* This should not compile 
    try
    { 
        std::cout << "Test 9 Numeric_cast non value: ";
        NonValue nv = boost::numeric_cast<NonValue>(l);
    }
    catch(...)
    {
        std::cout << " Should never happen" << std::endl;
    }
*/   
}

int main()
{
    scottsExampleUsage();
    
    scottsExampleWithNumericParameterUsage();

    fullTestCasesWithNumericParameter();

    return 0;
}


