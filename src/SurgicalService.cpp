#include "../include/SurgicalService.h"

SurgicalService::SurgicalService() : Service(), operation_type("") {}
SurgicalService::SurgicalService(std::string serve, int cost, int duration, std::string operation_type) :
    Service(serve, cost, duration), operation_type(operation_type){}
SurgicalService::~SurgicalService(){}

std::string SurgicalService::get_operation_type() const {return operation_type;}
void SurgicalService::set_operation_type(const std::string& operation_type) {this->operation_type = operation_type;}

std::string SurgicalService::get_serve_type() const {return "Хирургия";}

std::ostream& operator<<(std::ostream& os, const SurgicalService& surgical) {
    os << static_cast<const Service&>(surgical)
    << " | Операция: " << surgical.operation_type;
    return os;
}