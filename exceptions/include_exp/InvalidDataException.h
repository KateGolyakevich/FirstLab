#ifndef INVALIDDATAEXCEPTION_H
#define INVALIDDATAEXCEPTION_H

#include "ClinicException.h"
#include <string>

class InvalidDataException : public ClinicException {
public:
    InvalidDataException(const std::string& field_name, const std::string& reason);
};

#endif //INVALIDDATAEXCEPTION_H
