#include "../include_exp/ServiceNotFoundException.h"

ServiceNotFoundException::ServiceNotFoundException(const std::string& service_name, const std::string& patient_name)
    : ClinicException("[Объект не найден] Услуга '" + service_name +
                      "' отсутствует в карте пациента " + patient_name + "!") {}