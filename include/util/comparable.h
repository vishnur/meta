/**
 * @file comparable.h
 * @author Chase Geigle
 * Defines a CRTP base class that allows for inheritance of comparator
 * operations given that the base class defines operator<().
 *
 * All files in META are released under the MIT license. For more details,
 * consult the file LICENSE in the root of the project.
 */

#ifndef META_COMPARABLE_H_
#define META_COMPARABLE_H_

namespace meta
{
namespace util
{

/**
 * A CRTP base class that allows for inheritance of all comparator
 * operators given that the derived class defines an operator<(). All
 * operations are defined in terms of Derived's operator<().
 */
template <class Derived>
class comparable
{
  public:
    friend bool operator==(const comparable& lhs, const comparable& rhs)
    {
        return !(lhs.as_derived() < rhs.as_derived())
               && !(rhs.as_derived() < lhs.as_derived());
    }

    friend bool operator!=(const comparable& lhs, const comparable& rhs)
    {
        return !(lhs == rhs);
    }

    friend bool operator>(const comparable& lhs, const comparable& rhs)
    {
        return rhs.as_derived() < lhs.as_derived();
    }

    friend bool operator<=(const comparable& lhs, const comparable& rhs)
    {
        return lhs.as_derived() < rhs.as_derived() || lhs == rhs;
    }

    friend bool operator>=(const comparable& lhs, const comparable& rhs)
    {
        return lhs > rhs || lhs == rhs;
    }

  private:
    inline const Derived& as_derived() const
    {
        return static_cast<const Derived&>(*this);
    }
};
}
}
#endif