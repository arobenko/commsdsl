#include "commsdsl/IntField.h"

#include <cassert>

#include "IntFieldImpl.h"

namespace commsdsl
{

namespace
{

const IntFieldImpl* cast(const FieldImpl* ptr)
{
    assert(ptr != nullptr);
    return static_cast<const IntFieldImpl*>(ptr);
}

} // namespace

IntField::IntField(const IntFieldImpl* impl)
  : Base(impl)
{
}

IntField::IntField(Field field)
  : Base(field)
{
    assert(kind() == Kind::Int);
}

IntField::Type IntField::type() const
{
    return cast(m_pImpl)->type();
}

Endian IntField::endian() const
{
    return cast(m_pImpl)->endian();
}

std::intmax_t IntField::serOffset() const
{
    return cast(m_pImpl)->serOffset();
}

std::intmax_t IntField::minValue() const
{
    return cast(m_pImpl)->minValue();
}

std::intmax_t IntField::maxValue() const
{
    return cast(m_pImpl)->maxValue();
}

std::intmax_t IntField::defaultValue() const
{
    return cast(m_pImpl)->defaultValue();
}

IntField::ScalingRatio IntField::scaling() const
{
    return cast(m_pImpl)->scaling();
}

const IntField::ValidRangesList& IntField::validRanges() const
{
    return cast(m_pImpl)->validRanges();
}

const IntField::SpecialValues& IntField::specialValues() const
{
    return cast(m_pImpl)->specialValues();
}

Units IntField::units() const
{
    return cast(m_pImpl)->units();
}

bool IntField::validCheckVersion() const
{
    return cast(m_pImpl)->validCheckVersion();
}

} // namespace commsdsl
