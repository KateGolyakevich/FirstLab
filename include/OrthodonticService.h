#ifndef ORTHODONTIC_SERVICE_H
#define ORTHODONTIC_SERVICE_H

#include "Service.h"
#include "Orthodontist.h"

class OrthodonticService : public Service {
private:
    std::string correction_type;
    std::string correction_material;

public:
    OrthodonticService();
    OrthodonticService(std::string serve, int cost, int duration,
                       std::string correction_type, std::string correction_material,
                       Doctor* doctor = nullptr);
    ~OrthodonticService() override;

    std::string get_correction_type() const;
    std::string get_correction_material() const;
    void set_correction_type(const std::string& type);
    void set_correction_material(const std::string& material);

    std::string get_serve_type() const override;
    bool can_accept(Doctor* doctor) const override;
    void execute_service() const override;
    void print_info(std::ostream& os) const override;
};

#endif // ORTHODONTIC_SERVICE_H