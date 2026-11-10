#ifndef DUPLICATE_PATIENT_EXCEPTION_H
#define DUPLICATE_PATIENT_EXCEPTION_H

#include "../include_exp/ClinicException.h"
#include <string>

class DuplicatePatientException : public ClinicException {
public:
    explicit DuplicatePatientException(const std::string& patient_name);
};

#endif // DUPLICATE_PATIENT_EXCEPTION_H
