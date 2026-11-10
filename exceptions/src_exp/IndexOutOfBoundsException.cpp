#include "../include_exp/IndexOutOfBoundsException.h"

IndexOutOfBoundsException::IndexOutOfBoundsException(size_t index, size_t size)
    : ClinicException("[Выход за границы диапазона] Попытка доступа по индексу [" + std::to_string(index) +
                      "], допустимый диапазон: [0 .. " + (size == 0 ? "0" : std::to_string(size - 1)) + "] (размер: " +
                      std::to_string(size) + ")") {}