#include "../include/SurgicalService.h"

SurgicalService::SurgicalService() : Service(), operation_type("") {}

SurgicalService::SurgicalService(std::string serve, int cost, int duration,
                                 std::string operation_type, Doctor* doctor)
    : Service(serve, cost, duration, nullptr), operation_type(operation_type) {
    set_doctor(doctor);
}

SurgicalService::~SurgicalService() {}

std::string SurgicalService::get_operation_type() const { return operation_type; }
void SurgicalService::set_operation_type(const std::string& op_type) { operation_type = op_type; }

std::string SurgicalService::get_serve_type() const { return "Хирургия"; }

bool SurgicalService::can_accept(Doctor* doctor) const {
    return dynamic_cast<Surgeon*>(doctor) != nullptr;
}

void SurgicalService::execute_service() const {
    std::cout << "-> Проводится хирургическая операция: \"" << operation_type
              << "\". Длительность протокола: " << duration << " мин." << std::endl;
}

void SurgicalService::print_info(std::ostream& os) const {
    Service::print_info(os);
    os << " | Тип операции: " << operation_type;
}