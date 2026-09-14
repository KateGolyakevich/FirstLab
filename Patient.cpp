#include "Patient.h"

void Patient::add_service(Service service) {
    services[services_count] = service;
    services_count++;
}

void Patient::print() {
    std::cout <<"\nПациент: " << patient_name << std::endl;
    std::cout << "Количество выполненных процедур: " << services_count << std::endl;

    for (int i = 0; i < services_count; i++) {
        std::cout << "\nПроцедура: " << i + 1<< ":" << std::endl;
        services[i].print();
    }
}
