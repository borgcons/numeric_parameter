#include "numeric_parameter.hpp" 
#include <iostream> 
#include <algorithm>

template <typename Target>
class NumericParameter
{
public:
    // This input is another Numeric Parameter
    template<typename Source>NumericParameter(const NumericParameter<Source> &s)
    {
        value = NumericParameter<Target>(s.operator Source());
    }

    // The input in not a NumericParameter
    template <typename Source>NumericParameter(Source s)
    {
        value =  boost::numeric_cast<Target>(s);
    }

    // This input is of type Target
    NumericParameter(Target s)
    {
        value = s;
    }

    operator Target() const 
    {
        return value;
    }

    template<typename Result> operator Result() const 
    {
        return boost::numeric_cast<Result>(value);
    }
private:
    Target value;
};

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


int main()
{
    unsigned long unsignedLongMax = std::numeric_limits<unsigned long>::max();

    try
    {
        std::cout << "Test 2 Numeric Parameter to variable: ";
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
        std::cout << "Test 3 Numeric parameter into function overflow: ";
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
        std::cout << "Test 4 Numeric parameter to function valid: ";

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
        std::cout << "Test 5 Numeric parameter returned from function valid: ";

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
        std::cout << "Test 6 Numeric parameter returned from function overflow: ";

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
        std::cout << "Test 8 Numeric parameter returned from another function valid: ";

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
        std::cout << "Test 9 Numeric parameter returned from another function overflow: ";

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
        std::cout << "Test 10 Numeric parameter returned from another function overflow: ";

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
        std::cout << "Test 7 Numeric_cast non value: ";
        NonValue nv = boost::numeric_cast<NonValue>(l);
    }
    catch(...)
    {
        std::cout << " Should never happen" << std::endl;
    }
*/   

    return 0;
}


