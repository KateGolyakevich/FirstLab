#ifndef SURGEON_H
#define SURGEON_H
#include "Doctor.h"

class Surgeon : public Doctor {
private:
    int operations_count;  // проведено операций

public:
    Surgeon();
    Surgeon(std::string name, int experience, int operations_count);
    ~Surgeon() override;

    int get_operations_count() const;
    void set_operations_count(int o);

    std::string get_doctor_type() const override;
    double get_coefficient() const override;
    void perform_procedure() const override;
    void print_info(std::ostream& os) const override;
};
#endif //SURGEON_H
