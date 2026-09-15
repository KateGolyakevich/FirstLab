#include "../include/Patient.h"

int main() {
    Service service_first;
    service_first.serve_name = "Лечение кариеса";
    service_first.doctor_name = "Иванов Павел Иванович";
    service_first.serve_cost = 5000;
    service_first.duration = 60;

    Service service_second;
    service_second.serve_name = "Протезирование";
    service_second.doctor_name = "Александрова Елена Петровна";
    service_second.serve_cost = 50000;
    service_second.duration = 200;

    Service service_third;
    service_third.serve_name = "Удаление зуба мудрости";
    service_third.doctor_name = "Авдей Игорь Михайлович";
    service_third.serve_cost = 7000;
    service_third.duration = 100;

    Patient patient_first;
    patient_first.patient_name = "Бируль Никита Васильевич";
    patient_first.add_service(service_second);
    patient_first.add_service(service_third);

    Patient patient_second;
    patient_second.patient_name = "Ковальчук Ольга Владимировна";
    patient_second.add_service(service_first);

    patient_first.print();
    patient_second.print();

    return 0;
}