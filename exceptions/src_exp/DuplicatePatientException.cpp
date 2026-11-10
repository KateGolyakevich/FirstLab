#include "../include_exp/DuplicatePatientException.h"

DuplicatePatientException::DuplicatePatientException(const std::string& patient_name)
    : ClinicException("[Ошибка регистрации] Пациент '" + patient_name + "' уже существует в картотеке клиники!") {}