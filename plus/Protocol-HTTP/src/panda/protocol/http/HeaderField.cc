#include "HeaderField.h"
#include <ostream>

namespace panda { namespace protocol { namespace http {

HeaderField::HeaderField (const string &name, const string &value) : name(name), value(value) {}

bool HeaderField::operator== (const HeaderField &rhs) const {
    return iequals(name, rhs.name) && value == rhs.value;
}

std::ostream& operator<< (std::ostream& os, const HeaderField& hf) {
    os << hf.name << ": " << hf.value;
    return os;
}

}}}
