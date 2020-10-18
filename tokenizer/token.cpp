#include "token.h"


bool Token::is_digit() {
    std::string::const_iterator it = this->value.begin();
    while (it != this->value.end() && std::isdigit(*it)) ++it;
    return !this->value.empty() && it == this->value.end();
}

bool Token::is_string() {
    return (this->value.starts_with("\"") && this->value.ends_with("\"")) ||  (this->value.starts_with("'") && this->value.ends_with("'"));
}

Token::Token(std::string value) {
    this->value = value;
}

bool Token::is_keyword() {
    return this->value == "let" || this->value == "const" || this->value == "var" || this->value == "function" || this->value == "if" || this->value == "else" || this->value == "for";
}

bool Token::is_identifier() {
    if (this->contains_digit()) return false;
    if (this->is_punctuator()) return false;

    return !this->is_keyword();
}

bool Token::contains_digit() {
    return std::any_of(this->value.begin(), this->value.end(), ::isdigit);
}

bool Token::is_punctuator() {
    return this->value == "." || this->value == "," || this->value == "||" || this->value == "&&" ||
           this->value == "+" || this->value == "-" || this->value == "=" || this->value == "==" ||
           this->value == "=>" || this->value == "{"  || this->value == "}"  || this->value == "(" || this->value == ")" || this->value == ";";
}
