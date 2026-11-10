#ifndef INDEX_OUT_OF_BOUNDS_EXCEPTION_H
#define INDEX_OUT_OF_BOUNDS_EXCEPTION_H

#include "ClinicException.h"
#include <string>

class IndexOutOfBoundsException : public ClinicException {
public:
    IndexOutOfBoundsException(size_t index, size_t size);
};

#endif // INDEX_OUT_OF_BOUNDS_EXCEPTION_H
