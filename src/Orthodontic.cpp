#include "../include/Orthodontic.h"

Orthodontic::Orthodontic() : Service(), correction_type(""), correction_material(""){}
Orthodontic::Orthodontic(std::string serve, int cost, int duration,
    std::string &correction_type, std::string &correction_material) {}
Orthodontic::~Orthodontic(){}

std::string Orthodontic::get_correction_type() const {return correction_type;}
std::string Orthodontic::get_correction_material() const {return correction_material;}

void Orthodontic::set_correction_type(const std::string &operation_type) {
    this->correction_type = correction_type;}
void Orthodontic::set_correction_material(const std::string &operation_material) {this->correction_material = correction_material;}

std::string Orthodontic::get_serve_type() const {return "Ортодонтия";}
std::ostream& operator<<(std::ostream& os, const Orthodontic& orthodontic) {
    os << static_cast<const Service&>(orthodontic)
    << " | Устройство (брекеты, капы, пластинка): " << orthodontic.correction_type
    << " | Материал (Металл, керамика, сапфир): " << orthodontic.correction_material;
    return os;
}
