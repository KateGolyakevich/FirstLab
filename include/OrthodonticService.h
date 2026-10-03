#ifndef ORTHODONTIC_H
#define ORTHODONTIC_H

#include "Service.h"
class OrthodonticService : public Service {
    private:
    std::string correction_type;
    std::string correction_material;

public:
    OrthodonticService();
    OrthodonticService(std::string serve, int cost, int duration,
        std::string& correction_type, std::string& correction_material);
    ~OrthodonticService() override;

    std::string get_correction_type() const;
    std::string get_correction_material() const;

    void set_correction_type(const std::string& operation_type);
    void set_correction_material(const std::string& operation_material);

    std::string get_serve_type() const override;
    friend std::ostream& operator<<(std::ostream& os, const OrthodonticService& service);
};

#endif //ORTHODONTIC_H
