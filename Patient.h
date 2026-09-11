#include <iostream>
#include <string>

class Patient {
private:
    Service services[10];
    int services_count = 0;

public:
    std::string patient_name;

    void add_service(Service service) {
        services[services_count] = service;
        services_count++;
    }
    void print() {
        std::cout << "Имя пациента: " << patient_name << std::endl;
        std::cout << "Количество выполненных процедур: " << services_count << std::endl;

        for(int i = 0; i < services_count; i++){
            std::cout << "\nПроцедура: " << i+1 << ":" << std::endl;
            services[i].print();
        }
    }
};