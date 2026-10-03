#include "../include/OrthodonticService.h"

OrthodonticService::OrthodonticService() : Service(), correction_type(""), correction_material(""){}
OrthodonticService::OrthodonticService(std::string serve, int cost, int duration,
    std::string &correction_type, std::string &correction_material) {}
OrthodonticService::~OrthodonticService(){}

std::string OrthodonticService::get_correction_type() const {return correction_type;}
std::string OrthodonticService::get_correction_material() const {return correction_material;}

void OrthodonticService::set_correction_type(const std::string &operation_type) {
    this->correction_type = correction_type;}
void OrthodonticService::set_correction_material(const std::string &operation_material) {this->correction_material = correction_material;}

std::string OrthodonticService::get_serve_type() const {return "Ортодонтия";}
std::ostream& operator<<(std::ostream& os, const OrthodonticService& orthodontic) {
    os << static_cast<const Service&>(orthodontic)
    << " | Устройство (брекеты, капы, пластинка): " << orthodontic.correction_type
    << " | Материал (Металл, керамика, сапфир): " << orthodontic.correction_material;
    return os;
}
