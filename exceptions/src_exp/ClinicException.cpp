#include "../include_exp/ClinicException.h"

ClinicException::ClinicException(const std::string& msg) : message(msg) {}

const char* ClinicException::what() const noexcept {
    return message.c_str();
}