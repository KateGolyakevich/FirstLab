#ifndef DUPLICATE_PATIENT_EXCEPTION_H
#define DUPLICATE_PATIENT_EXCEPTION_H

#include "ClinicException.h"
#include <string>

class DuplicatePatientException : public ClinicException {
public:
    DuplicatePatientException(const std::string& service_name, const std::string& patient_name);
};

#endif // DUPLICATE_PATIENT_EXCEPTION_H
