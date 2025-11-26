#ifndef TEXT_REDACTOR_H
#define TEXT_REDACTOR_H

#include "dictionary.h"
#include <string>

struct TextRedactor {
    Dictionary replacements_;

    bool read_replacements(const std::string& file_name);
    std::string redact_dates(const std::string& text) const;
    std::string redact_numbers(const std::string& text) const;
    std::string redact_replacements(const std::string& text) const;
    std::string redact(const std::string& text) const;
};

#endif // TEXT_REDACTOR_H