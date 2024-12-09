#include <iostream>
#include "arguments.h"

const std::string help_text = "Użycie: kodcpp [opcje] -i <plik_wejsciowy> -o <plik_wyjsciowy>\n--zmienne-lokalne\t\tPokazuje zmienne lokalne znalezionych funkcji.\n--funkcje-wywolane\t\tPokazuje jakie funkcje wywołuje dana funkcja.\n--gdzie-wywolywana <funkcja>\tPokazuje w ktorych funkcjach dana funkcja jest wywoływana.\n--policz-duplikaty\t\tWypisuje w ilu funkcjach są zmienne o takiej samej nazwie.\n--zmienne-wedlug-typu <typ>\tWypisuje wszystkie zmienne danego typu.";

arguments::arguments(int argc, char* argv[]) : local_variables(false), called_functions(false), duplicate_variables(false) {
    parse(argc, argv);
}

void arguments::parse(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << help_text << std::endl;
        return;
    }

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-i" && i + 1 < argc) {
            input_file = argv[++i];
        }
        else if (arg == "-o" && i + 1 < argc) {
            output_file = argv[++i];
        }
        else if (arg == "--zmienne-lokalne") {
            local_variables = true;
        }
        else if (arg == "--funkcje-wywolane") {
            called_functions = true;
        }
        else if (arg == "--policz-duplikaty") {
            duplicate_variables = true;
        }
        else if (arg == "--gdzie-wywolywana" && i + 1 < argc) {
            function_calls = argv[++i];
        }
        else if (arg == "--zmienne-wedlug-typu" && i + 1 < argc) {
            variables_by_type = argv[++i];
        }
    }

    if (input_file.empty() || output_file.empty()) {
        std::cout << help_text << std::endl;
    }
}

std::string arguments::get_input() const {
    return input_file;
}

std::string arguments::get_output() const {
    return output_file;
}

bool arguments::find_local_variables() const {
    return local_variables;
}

bool arguments::find_called_functions() const {
    return called_functions;
}

bool arguments::find_duplicate_variables() const {
    return duplicate_variables;
}

std::string arguments::find_function_calls() const {
    return function_calls;
}

std::string arguments::find_variables_by_type() const {
    return variables_by_type;
}
