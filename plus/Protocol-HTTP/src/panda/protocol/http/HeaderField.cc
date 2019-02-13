#include "HeaderField.h"

namespace panda { namespace protocol { namespace http {

HeaderField::HeaderField(const string &name, const string &value) : name(name), value(value) {}

bool HeaderField::operator==(const HeaderField &rhs) const {
    return iequals(name, rhs.name) && value == rhs.value;
}

bool HeaderField::operator!=(const HeaderField &rhs) const {
    return !(rhs == *this);
}

}}} // namespace panda::protocol::http
