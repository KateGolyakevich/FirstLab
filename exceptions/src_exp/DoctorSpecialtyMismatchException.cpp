#include "../include_exp/DoctorSpecialtyMismatchException.h"

DoctorSpecialtyMismatchException::DoctorSpecialtyMismatchException(const std::string& doctor_name,
                                                                 const std::string& doctor_type,
                                                                 const std::string& service_type)
    : ClinicException("[Ошибка назначения врача] Врач " + doctor_name + " (" + doctor_type +
                      ") не имеет допуска к услуге профиля: " + service_type) {}