#include "../include/SurgicalService.h"
#include "../include/Surgeon.h"

SurgicalService::SurgicalService() : Service(), operation_type("") {}
SurgicalService::SurgicalService(std::string serve, int cost, int duration,
    std::string operation_type, Doctor* doctor) :
    Service(serve, cost, duration, nullptr), operation_type(operation_type){set_doctor(doctor);}
SurgicalService::~SurgicalService(){}

std::string SurgicalService::get_operation_type() const {return operation_type;}

void SurgicalService::set_operation_type(const std::string& operation_type) {this->operation_type = operation_type;}

bool SurgicalService::can_accept(Doctor* doctor) const {
    return dynamic_cast<Surgeon*>(doctor) != nullptr;
}
std::string SurgicalService::get_serve_type() const {return "Хирургия";}

std::ostream& operator<<(std::ostream& os, const SurgicalService& surgical) {
    os << static_cast<const Service&>(surgical)
    << " | Операция: " << surgical.operation_type;
    return os;
}