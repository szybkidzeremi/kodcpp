/**
 * @file main.cpp
 * @brief Punkt wejścia aplikacji. Ten plik zawiera funkcję main, która inicjalizuje aplikację i rozpoczyna główną pętlę wykonawczą.
 * @author Bartosz Biesiada
 */
#include <iostream>
#include "arguments.h"
#include "filehandler.h"
#include "finder.h"

/**
 * @brief Funkcja główna. Ta funkcja inicjalizuje aplikację i rozpoczyna główną pętlę wykonawczą.
 * @param argc Liczba argumentów przekazanych do programu.
 * @param argv Tablica argumentów przekazanych do programu.
 * @return int Zwraca EXIT_SUCCESS po pomyślnym wykonaniu, w przeciwnym razie EXIT_FAILURE.
 */
int main(int argc, char* argv[]) {
    // Inicjalizacja modułu odczytu argumentów z linii poleceń
    arguments args(argc, argv);
    if (args.get_input().empty() || args.get_output().empty()) {
        return EXIT_FAILURE; // Program bez wymaganych argumentów (-i -o) nie ruszy dalej
    }

    std::string file_contents{ "" };
    std::string result{ "" };

    // Odczyt pliku z argumentu (-i example.txt)
    filehandler reader(args.get_input());
    reader.read(file_contents);
    reader.close();
    std::cout << "Odczytano plik \"" << args.get_input() << "\" pomyślnie.\n";

    // Inicjalizacja modułu szukania
    finder finder(file_contents);
    result = finder.find_functions();

    // Szukanie według wybranych argumentów 
    if (args.find_local_variables()) {
        result.append(finder.find_local_variables()); // --zmienne-lokalne
    }

    if (args.find_called_functions()) {
        result.append(finder.find_called_functions()); // --funkcje-wywolane
    }

    if (args.find_duplicate_variables()) {
        result.append(finder.find_duplicate_variables()); // --policz-duplikaty
    }

    if (!args.find_function_calls().empty()) {
        result.append(finder.find_function_calls_in_functions(args.find_function_calls())); // --gdzie-wywolywana
    }

    if (!args.find_variables_by_type().empty()) {
        result.append(finder.find_variables_by_type(args.find_variables_by_type())); // --zmienna-wedlug-typu
    }

    // Zapis znalezionych funkcji do pliku
    reader.write(args.get_output(), result);
    std::cout << "Zakończono. Wynik działania znajduje się w pliku \"" << args.get_output() << "\".\n";

    return EXIT_SUCCESS;
}
