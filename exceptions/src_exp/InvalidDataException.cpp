#include "../include_exp/InvalidDataException.h"

InvalidDataException::InvalidDataException(const std::string& field_name, const std::string& reason)
    : ClinicException("[Ошибка данных] Поле '" + field_name + "' содержит некорректное значение: " + reason) {}
