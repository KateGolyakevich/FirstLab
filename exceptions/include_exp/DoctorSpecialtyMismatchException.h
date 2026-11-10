#ifndef DOCTOR_SPECIALTY_MISMATCH_EXCEPTION_H
#define DOCTOR_SPECIALTY_MISMATCH_EXCEPTION_H

#include "ClinicException.h"
#include <string>

class DoctorSpecialtyMismatchException : public ClinicException {
public:
    DoctorSpecialtyMismatchException(const std::string& doctor_name,
                                     const std::string& doctor_type,
                                     const std::string& service_type);
};

#endif // DOCTOR_SPECIALTY_MISMATCH_EXCEPTION_H
