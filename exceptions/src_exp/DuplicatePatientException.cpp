#include "../include_exp/DuplicatePatientException.h"

DuplicatePatientException::DuplicatePatientException(const std::string& service_name, const std::string& patient_name)
    : ClinicException("[Ошибка регистрации] Услуга '" + service_name + "' уже назначена пациенту " + patient_name + "!") {}