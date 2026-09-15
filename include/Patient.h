#include <iostream>
#include <string>
#include "Service.h"

class Patient {
private:
    Service services[10];
    int services_count = 0;
    public:
    std::string patient_name;

    void add_service(Service service);
    void print();
};