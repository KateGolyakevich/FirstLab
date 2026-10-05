#include <iostream>
#include "../include/TherapeuticService.h"
#include "../include/SurgicalService.h"
#include "../include/OrthodonticService.h"
#include "../include/Therapist.h"
#include "../include/Surgeon.h"
#include "../include/Orthodontist.h"
#include "../include/Patient.h"

int main() {

    std::cout << "--- Врачи клиники ---\n";
    Therapist    therapist("Иванов И.И.", 12, 340);
    Surgeon      surgeon("Петров П.П.", 18, 95);
    Orthodontist orthodontist("Сидорова А.А.", 8, 47);

    std::cout << therapist    << "\n";
    std::cout << surgeon      << "\n";
    std::cout << orthodontist << "\n";

    std::cout << "\n--- Полиморфизм через Doctor* ---\n";
    Doctor* doctor = &surgeon;
    std::cout << *doctor << "\n";

    std::cout << "\n--- Услуги клиники ---\n";
    TherapeuticService therapy("Лечение кариеса", 2500, 60, "36", false);
    SurgicalService    surgical("Удаление зуба мудрости", 4000, 40,
                               "удаление");
    OrthodonticService braces("Установка брекетов", 30000, 90,
                              "брекеты", "керамика");

    std::cout << therapy;
    std::cout << surgical;
    std::cout << braces << "\n";

    std::cout << "\n--- Полиморфизм через Service* ---\n";
    Service* service = &braces;
    std::cout << *service << "\n";

    std::cout << "\n\n>>> Пациент БЕЗ карты\n";
    Patient patient_first("Иванов И.И.", false);
    patient_first += new TherapeuticService("Лечение кариеса (первичное)", 2500, 60, "36", false);
    patient_first += new TherapeuticService("Лечение кариеса (повторное)",  2500, 60, "36", true);
    patient_first += new SurgicalService("Удаление зуба", 4000, 40,
                              "удаление");

    std::cout << patient_first << "\n";

    std::cout << "\n>>> Пациент С картой\n";
    Patient patient_second("Петров П.П.", true);
    patient_second += new TherapeuticService("Лечение кариеса (первичное)", 2500, 60, "36", false);
    patient_second += new TherapeuticService("Лечение кариеса (повторное)",  2500, 60, "36", true);
    patient_second += new SurgicalService("Удаление зуба", 4000, 40,
                              "удаление");

    std::cout << patient_second << "\n";

    std::cout << "\n>>> Тот же пациент, но теперь у него появилась карта\n";
    patient_first.set_has_card(true);
    std::cout << patient_first << "\n";

    return 0;
}