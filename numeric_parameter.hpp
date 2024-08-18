#include <boost/numeric/conversion/cast.hpp>

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
