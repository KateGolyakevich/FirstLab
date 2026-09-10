#include "DentalClinic.h"

int main() {
    Service service_first;
    service_first.serve_name = "Лечение кариеса";
    service_first.doctor_name = "Иванов Иван Иванович";
    service_first.serve_cost = 5000;
    service_first.duration = 60;

    Service service_second;
    service_second.serve_name = "Протезирование";
    service_second.doctor_name = "Повлеченко Игорь Васильевич";
    service_second.serve_cost = 15000;
    service_second.duration = 120;

    Patient patient_first;
    patient_first.patient_name = "Петров Петр Петрович";
    patient_first.add_service(service_first);

    Patient patient_second;
    patient_second.patient_name = "Александрова Елизавета Ивановна";
    patient_second.add_service(service_first);
    patient_second.add_service(service_second);

    patient_first.print();
    patient_second.print();

    return 0;
}