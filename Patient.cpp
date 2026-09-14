#include "Service.h"
#include "Patient.h"



int main() {
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