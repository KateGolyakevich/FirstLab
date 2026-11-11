#include <iostream>
#include "../include/Collection.hpp"
#include "../include/Therapist.h"
#include "../include/Surgeon.h"
#include "../include/Orthodontist.h"
#include "../include/TherapeuticService.h"
#include "../include/SurgicalService.h"
#include "../include/OrthodonticService.h"
#include "../include/Patient.h"

#include "../exceptions/include_exp/ClinicException.h"
#include "../exceptions/include_exp/InvalidDataException.h"
#include "../exceptions/include_exp/DoctorSpecialtyMismatchException.h"
#include "../exceptions/include_exp/DuplicatePatientException.h"
#include "../exceptions/include_exp/ServiceNotFoundException.h"
#include "../exceptions/include_exp/IndexOutOfBoundsException.h"

int main() {
    std::cout << "========================================================================\n\n";

    Doctor* therapist = new Therapist("Иванов И.И.", 10, 400);
    Doctor* surgeon   = new Surgeon("Петров П.П.", 15, 250);

    std::cout << ">>> ТЕСТ 1: InvalidDataException (отрицательный стаж врача)\n";
    try {
        std::cout << "Попытка задать стаж -5 лет...\n";
        therapist->set_experience(-5);
    } catch (const InvalidDataException& exception) {
        std::cout << "[ПЕРЕХВАЧЕНО]: " << exception.what() << "\n";
    }
    std::cout << "\n\n";

    std::cout << ">>> ТЕСТ 2: DoctorSpecialtyMismatchException (хирург на терапию)\n";
    Service* therapy_service = new TherapeuticService("Пломбирование зуба", 3000, 45, "21", false);
    try {
        std::cout << "Попытка назначить хирурга на терапевтическую услугу...\n";
        therapy_service->set_doctor(surgeon);
    } catch (const DoctorSpecialtyMismatchException& e) {
        std::cout << "[ПЕРЕХВАЧЕНО]: " << e.what() << "\n";
    }
    therapy_service->set_doctor(therapist);
    std::cout << "\n\n";

    std::cout << ">>> ТЕСТ 3: DuplicatePatientException (повторная регистрация пациента)\n";
    Patient p1("Сидоров Алексей Михайлович", true);
    p1 += therapy_service;
    try {
        std::cout << "Повторно добавляем ту же процедуру...\n";
        p1+=therapy_service;
    }catch (const DuplicatePatientException& e) {std::cout << "[ПЕРЕХВАЧЕНО]: " << e.what() << "\n";}

    Patient p2("Сидоров Алексей Михайлович", false);
    std::cout << "\n\n";

    std::cout << ">>> ТЕСТ 4: ServiceNotFoundException (удаление неназванной услуги)\n";
    Patient p3("Кузнецова О.В.", false);
    p3 += therapy_service;

    Service* phantom_surgery = new SurgicalService("Удаление зуба мудрости", 5000, 60, "Экстракция", surgeon);

    try {
        std::cout << "Попытка удалить из карты пациента услугу, которой там нет...\n";
        p3 -= phantom_surgery;
    } catch (const ServiceNotFoundException& e) {
        std::cout << "[ПЕРЕХВАЧЕНО]: " << e.what() << "\n";
    }
    std::cout << "\n\n";

    std::cout << ">>> ТЕСТ 5: IndexOutOfBoundsException (выход за пределы Collection<T>)\n";
    Collection<Doctor*> doctors_list;
    doctors_list.add(therapist);
    doctors_list.add(surgeon);

    try {
        std::cout << "Попытка обратиться к элементу [10] при размере коллекции 2...\n";
        doctors_list.at(10);
    } catch (const IndexOutOfBoundsException& exception) {
        std::cout << "[ПЕРЕХВАЧЕНО]: " << exception.what() << "\n";
    }

    delete therapist;
    delete surgeon;
    delete therapy_service;
    delete phantom_surgery;

    return 0;
}