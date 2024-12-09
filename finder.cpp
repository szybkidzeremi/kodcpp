#include "finder.h"

finder::finder(const std::string& code) : code(code) {}

std::string finder::find_functions() const {
    std::istringstream stream(code);
    std::string chunk;
    std::regex function_regex(R"(\b(\w+)\s+(\w+)\s*\(([^)]*)\))");
    std::smatch match;
    std::ostringstream result;
    std::size_t start_pos = 0, end_pos;
    int line_number = 1;

    while ((end_pos = code.find(';', start_pos)) != std::string::npos) {
        chunk = code.substr(start_pos, end_pos - start_pos + 1);
        start_pos = end_pos + 1;

        line_number += std::count(chunk.begin(), chunk.end(), '\n');

        if (std::regex_search(chunk, match, function_regex)) {
            std::string return_type = match[1];
            std::string function_name = match[2];
            std::string parameters = match[3];

            std::string trimmed_parameters = parameters;
            trimmed_parameters.erase(std::remove_if(trimmed_parameters.begin(), trimmed_parameters.end(), ::isspace), trimmed_parameters.end());

            result << "Znaleziona funkcja: " << function_name << "\n";
            if (!trimmed_parameters.empty()) {
                result << "Przyjmuje: " << parameters << "\n";
            }
        }
    }

    return result.str();
}

std::string finder::find_local_variables() const {
    std::istringstream stream(code);
    std::string line;
    std::regex function_regex(R"(\b(\w+)\s+(\w+)\s*\(([^)]*)\)\s*\{)");
    std::regex variable_regex(R"(\b(\w+)\s+(\w+)\s*=\s*([^;]+);)");
    std::smatch match;
    std::ostringstream result;
    int line_number = 1;
    bool in_function = false;
    std::string current_function;
    std::ostringstream current_function_result;

    while (std::getline(stream, line)) {
        if (!in_function && std::regex_search(line, match, function_regex)) {
            in_function = true;
            current_function = match[2];
            current_function_result.str("");
            current_function_result.clear();
            current_function_result << "Zmienne lokalne w funkcji " << current_function << ":\n";
        }

        if (in_function) {
            auto vars_begin = std::sregex_iterator(line.begin(), line.end(), variable_regex);
            auto vars_end = std::sregex_iterator();
            for (std::sregex_iterator i = vars_begin; i != vars_end; ++i) {
                std::smatch var_match = *i;
                current_function_result << var_match[1] << " " << var_match[2] << " = " << var_match[3] << ";\n";
            }
        }

        if (in_function && line.find('}') != std::string::npos) {
            in_function = false;
            if (current_function_result.str().find('=') != std::string::npos) {
                result << current_function_result.str();
            }
        }
        line_number++;
    }

    return result.str();
}

std::string finder::find_called_functions() const {
    std::istringstream stream(code);
    std::string line;
    std::regex called_function_regex(R"(\b(\w+)\s*\(([^)]*)\))");
    std::smatch match;
    std::ostringstream result;
    int line_number = 1;

    while (std::getline(stream, line)) {
        auto funcs_begin = std::sregex_iterator(line.begin(), line.end(), called_function_regex);
        auto funcs_end = std::sregex_iterator();

        for (std::sregex_iterator i = funcs_begin; i != funcs_end; ++i) {
            std::smatch func_match = *i;
            std::string function_name = func_match[1];
            std::string parameters = func_match[2];

            result << "Wywołana funkcja: " << function_name;
            if (!parameters.empty()) {
                result << " z argumentami: " << parameters;
            }
            result << "\n";
        }
        line_number++;
    }

    return result.str();
}

std::string finder::find_function_calls_in_functions(const std::string& function_name) const {
    std::istringstream stream(code);
    std::string line;
    std::regex function_regex(R"(\b(\w+)\s+(\w+)\s*\(([^)]*)\)\s*\{)");
    std::regex called_function_regex(R"(\b)" + std::regex_replace(function_name, std::regex(R"([()])"), R"(\()") + R"(\s*\([^)]*\))");
    std::smatch match;
    std::ostringstream result;
    int line_number = 1;
    bool in_function = false;
    std::string current_function;
    bool is_current_function = false;

    while (std::getline(stream, line)) {
        if (!in_function && std::regex_search(line, match, function_regex)) {
            in_function = true;
            current_function = match[2];
            is_current_function = (current_function == function_name);
        }

        if (in_function && !is_current_function && std::regex_search(line, match, called_function_regex)) {
            result << "Funkcja " << function_name << " jest wywoływana w funkcji " << current_function << "\n";
        }

        if (in_function && line.find('}') != std::string::npos) {
            in_function = false;
        }
        line_number++;
    }

    return result.str();
}

std::string finder::find_duplicate_variables() const {
    std::istringstream stream(code);
    std::string line;
    std::regex function_regex(R"(\b(\w+)\s+(\w+)\s*\(([^)]*)\)\s*\{)");
    std::regex variable_regex(R"(\b(\w+)\s+(\w+)\s*=\s*([^;]+);)");
    std::smatch match;
    std::ostringstream result;
    int line_number = 1;
    bool in_function = false;
    std::string current_function;
    std::unordered_map<std::string, std::unordered_set<std::string>> function_variables;
    std::unordered_map<std::string, int> variable_count;

    while (std::getline(stream, line)) {
        if (!in_function && std::regex_search(line, match, function_regex)) {
            in_function = true;
            current_function = match[2];
            function_variables[current_function] = std::unordered_set<std::string>();
        }

        if (in_function) {
            auto vars_begin = std::sregex_iterator(line.begin(), line.end(), variable_regex);
            auto vars_end = std::sregex_iterator();
            for (std::sregex_iterator i = vars_begin; i != vars_end; ++i) {
                std::smatch var_match = *i;
                std::string variable_name = var_match[2];
                for (const auto& func : function_variables) {
                    if (func.second.find(variable_name) != func.second.end()) {
                        variable_count[variable_name]++;
                    }
                }
                function_variables[current_function].insert(variable_name);
            }
        }

        if (in_function && line.find('}') != std::string::npos) {
            in_function = false;
        }
        line_number++;
    }

    if (!variable_count.empty()) {
        result << "Zmienne o tej samej nazwie znalezione w kilku funkcjach:\n";
        for (const auto& var : variable_count) {
            result << var.first << " znaleziono w " << var.second + 1 << "\n";
        }
    }
    else {
        result << "Nie znaleziono zmiennych o tych samych nazwach.";
    }

    return result.str();
}

std::string finder::find_variables_by_type(const std::string& type) const {
    std::istringstream stream(code);
    std::string line;
    std::regex variable_regex(R"(\b)" + type + R"(\s+(\w+)\s*(=\s*[^;]*)?;)");
    std::smatch match;
    std::ostringstream result;
    int line_number = 1;

    while (std::getline(stream, line)) {
        auto vars_begin = std::sregex_iterator(line.begin(), line.end(), variable_regex);
        auto vars_end = std::sregex_iterator();
        for (std::sregex_iterator i = vars_begin; i != vars_end; ++i) {
            std::smatch var_match = *i;
            std::string variable_name = var_match[1];
            std::string initialization = var_match[2];

            result << "Zmienna " << variable_name << " o typie " << type << " znaleziona";
            if (!initialization.empty()) {
                result << " z zainicjowaną wartością: " << initialization << "\n";
            }
        }
        line_number++;
    }

    if (result.str().empty()) {
        result << "Nie znaleziono zmiennych o typie " << type << ".\n";
    }

    return result.str();
}
