#ifndef THERAPIST_H
#define THERAPIST_H

#include "Doctor.h"

class Therapist : public Doctor {
private:
    int filled_teeth;  // вылечено зубов

public:
    Therapist();
    Therapist(std::string name, int experience, int filled_teeth);
    ~Therapist() override;

    int get_filled_teeth() const;
    void set_filled_teeth(int filled_teeth);

    std::string get_doctor_type() const override;
    double get_coefficient() const override;
    void perform_procedure() const override;
    void print_info(std::ostream& os) const override;

};
#endif //THERAPIST_H
