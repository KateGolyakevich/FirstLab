#ifndef SERVICE_NOT_FOUND_EXCEPTION_H
#define SERVICE_NOT_FOUND_EXCEPTION_H

#include "ClinicException.h"
#include <string>

class ServiceNotFoundException : public ClinicException {
public:
    ServiceNotFoundException(const std::string& service_name, const std::string& patient_name);
};

#endif // SERVICE_NOT_FOUND_EXCEPTION_H