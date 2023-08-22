#include "s21_model.h"

namespace s21 {

double Model::create_number(const std::string &number_string) {
  double result = 0;
  bool point = false;
  int stepen = -1;
  for (auto it = number_string.begin();
       it != number_string.end() && error == true; ++it) {
    if (!((*it >= '0' && *it <= '9') || (*it == '.'))) {
      error = false;
    }
    if (*it == '.') {
      if (point == false) {
        point = true;
        if ((it + 1 == number_string.end()) || (it == number_string.begin())) {
          error = false;
          break;
        }
      } else {
        error = false;
        break;
      }
    } else {
      if (point == false) {
        result *= 10;
        result += (*it - '0');
      } else {
        result += (*it - '0') * pow(10, stepen--);
      }
    }
  }
  return result;
}

double Model::from_exp_form_to_double(const std::string &number_string) {
  bool sign;
  std::string mantisa_string;
  std::string stepen_string;
  bool borders = true;
  for (auto it = number_string.begin(); it != number_string.end(); ++it) {
    if (*it == 'e') {
      borders = false;
    } else if (*it == '+') {
      sign = true;
    } else if (*it == '-') {
      sign = false;
    } else if (borders == true) {
      mantisa_string.push_back(*it);
    } else {
      stepen_string.push_back(*it);
    }
  }
  return sign ? create_number(mantisa_string) *
                    pow(10, create_number(stepen_string))
              : create_number(mantisa_string) *
                    pow(10, (-1) * create_number(stepen_string));
}

bool Model::definition_of_tokens(int &i, const std::string &str,
                                 const int &amount, ...) {
  va_list point_f;
  va_start(point_f, amount);
  bool result = true;
  int i_tmp = i;
  if (i_tmp + amount < (int)str.size()) {
    for (int j = 0; j < amount; j++, i_tmp++) {
      char ellement = (char)va_arg(point_f, int);
      if (str[i_tmp] != ellement) {
        result = false;
        break;
      }
    }
  } else {
    result = false;
  }
  if (result == true) {
    i = i + amount - 1;
  }
  va_end(point_f);
  return result;
}

void Model::number_processing(int &i, const std::string &str) {
  std::string number_string;
  bool stop = true;
  int e_col = 0;
  while (((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == 'e') &&
         i < (int)str.size() && error == true) {
    if (str[i] == '.' && stop == true) {
      stop = false;
    } else if (str[i] == '.' && stop == false) {
      error = false;
    } else if (str[i] == 'e' && e_col < 2) {
      e_col++;
      if (i + 2 < (int)str.size()) {
        if ((str[i + 1] == '+' || str[i + 1] == '-') ||
            (str[i + 2] >= 0 && str[i + 2] <= 9)) {
          number_string.push_back(str[i]);
          i++;
        } else {
          error = false;
        }
      }
    } else if (str[i] == 'e') {
      error = false;
    }
    number_string.push_back(str[i]);
    i++;
  }
  i--;
  if (e_col == 0) {
    array_of_tokens.push_back(
        lexeme_struct(create_number(number_string), NUMBER));
  } else {
    array_of_tokens.push_back(
        lexeme_struct(from_exp_form_to_double(number_string), NUMBER));
  }
}

void Model::parser(const std::string &str) {
  for (int i = 0; i < (int)str.size() && error == true; ++i) {
    if (str[i] >= '0' && str[i] <= '9') {
      number_processing(i, str);
    } else if (str[i] == '+') {
      array_of_tokens.push_back(lexeme_struct(0, UNARY_PLUS));
    } else if (str[i] == '-') {
      array_of_tokens.push_back(lexeme_struct(0, UNARY_MINUS));
    } else if (str[i] == '/') {
      array_of_tokens.push_back(lexeme_struct(0, DIV));
    } else if (str[i] == '*') {
      array_of_tokens.push_back(lexeme_struct(0, MULT));
    } else if (str[i] == '(') {
      array_of_tokens.push_back(lexeme_struct(0, OPEN_BRACKET));
    } else if (str[i] == ')') {
      array_of_tokens.push_back(lexeme_struct(0, CLOSE_BRACKET));
    } else if (str[i] == '^') {
      array_of_tokens.push_back(lexeme_struct(0, DEGREE));
    } else if (str[i] == 'x') {
      array_of_tokens.push_back(lexeme_struct(0, IKS));
    } else if (str[i] == '=' || str[i] == ' ') {
      array_of_tokens.push_back(lexeme_struct(0, NT));
    } else if (definition_of_tokens(i, str, 2, (int)'l', (int)'n') == true) {
      array_of_tokens.push_back(lexeme_struct(0, LN));
    } else if (definition_of_tokens(i, str, 3, (int)'m', (int)'o', (int)'d') ==
               true) {
      array_of_tokens.push_back(lexeme_struct(0, MOD));
    } else if (definition_of_tokens(i, str, 3, (int)'c', (int)'o', (int)'s') ==
               true) {
      array_of_tokens.push_back(lexeme_struct(0, COS));
    } else if (definition_of_tokens(i, str, 3, (int)'s', (int)'i', (int)'n') ==
               true) {
      array_of_tokens.push_back(lexeme_struct(0, SIN));
    } else if (definition_of_tokens(i, str, 3, (int)'t', (int)'a', (int)'n') ==
               true) {
      array_of_tokens.push_back(lexeme_struct(0, TAN));
    } else if (definition_of_tokens(i, str, 3, (int)'l', (int)'o', (int)'g') ==
               true) {
      array_of_tokens.push_back(lexeme_struct(0, LOG));
    } else if (definition_of_tokens(i, str, 4, (int)'s', (int)'q', (int)'r',
                                    (int)'t') == true) {
      array_of_tokens.push_back(lexeme_struct(0, SQRT));
    } else if (definition_of_tokens(i, str, 4, (int)'a', (int)'c', (int)'o',
                                    (int)'s') == true) {
      array_of_tokens.push_back(lexeme_struct(0, ACOS));
    } else if (definition_of_tokens(i, str, 4, (int)'a', (int)'s', (int)'i',
                                    (int)'n') == true) {
      array_of_tokens.push_back(lexeme_struct(0, ASIN));
    } else if (definition_of_tokens(i, str, 4, (int)'a', (int)'t', (int)'a',
                                    (int)'n') == true) {
      array_of_tokens.push_back(lexeme_struct(0, ATAN));
    } else {
      error = false;
      break;
    }
  }
}

void Model::input_validation() {
  std::stack<bool> brackes;
  for (int i = 0; i < (int)array_of_tokens.size() && error == true; i++) {
    if (array_of_tokens[i].type_ == OPEN_BRACKET) {
      brackes.push(true);
      if (i + 1 < (int)array_of_tokens.size()) {
        if (array_of_tokens[i + 1].type_ == CLOSE_BRACKET) {
          error = false;
        }
      }
    } else if (array_of_tokens[i].type_ == CLOSE_BRACKET) {
      if (brackes.empty()) {
        error = false;
      } else {
        brackes.pop();
      }
    } else if (array_of_tokens[i].type_ >= COS &&
               array_of_tokens[i].type_ <= LOG) {
      if (i + 1 < (int)array_of_tokens.size()) {
        if (array_of_tokens[i + 1].type_ != OPEN_BRACKET) {
          error = false;
        }
      }
    } else if (array_of_tokens[i].type_ == UNARY_MINUS && i > 0) {
      if (array_of_tokens[i - 1].type_ != OPEN_BRACKET) {
        array_of_tokens[i].type_ = BINARY_MINUS;
      }
    } else if (array_of_tokens[i].type_ == UNARY_PLUS && i > 0) {
      if (array_of_tokens[i - 1].type_ != OPEN_BRACKET) {
        array_of_tokens[i].type_ = BINARY_PLUS;
      }
    }
  }
  if (!brackes.empty()) {
    error = false;
  }
}

void Model::dublicat_validation() {
  for (int i = 0; i < (int)array_of_tokens.size() && error == true; i++) {
    if (array_of_tokens[i].type_ >= UNARY_PLUS &&
        array_of_tokens[i].type_ <= BINARY_MINUS &&
        i + 1 < (int)array_of_tokens.size()) {
      if (array_of_tokens[i + 1].type_ >= CLOSE_BRACKET &&
          array_of_tokens[i + 1].type_ <= BINARY_MINUS) {
        error = false;
      }
    }
  }
}

void Model::create_operators_stack(const int &i) {
  while (!operation_stack.empty()) {
    int first = operation_priority(operation_stack.top().type_);
    int second = operation_priority(array_of_tokens[i].type_);
    if (first >= second && operation_stack.top().type_ >= UNARY_PLUS &&
        operation_stack.top().type_ <= BINARY_MINUS) {
      if (first == second &&
          !operator_associativity(array_of_tokens[i].type_)) {
        break;
      } else {
        output_array.push_back(operation_stack.top());
        operation_stack.pop();
      }
    } else {
      break;
    }
  }
  operation_stack.push(array_of_tokens[i]);
}

void Model::from_stack_to_output_array() {
  if (!operation_stack.empty()) {
    while (operation_stack.top().type_ != OPEN_BRACKET &&
           operation_stack.top().type_ >= UNARY_PLUS &&
           operation_stack.top().type_ <= BINARY_MINUS) {
      output_array.push_back(operation_stack.top());
      operation_stack.pop();
    }
    if (operation_stack.top().type_ == OPEN_BRACKET) {
      operation_stack.pop();
    } else {
      error = false;
    }
  }
  if (!operation_stack.empty()) {
    if (operation_stack.top().type_ >= COS &&
        operation_stack.top().type_ <= LOG) {
      output_array.push_back(operation_stack.top());
      operation_stack.pop();
    }
  }
}

void Model::deicstra_algorithm() {
  for (int i = 0; i < (int)array_of_tokens.size() && error == true; i++) {
    if (array_of_tokens[i].type_ == NUMBER) {
      output_array.push_back(array_of_tokens[i]);
    } else if (array_of_tokens[i].type_ == IKS) {
      array_of_tokens[i].data_ = x_;
      array_of_tokens[i].type_ = NUMBER;
      output_array.push_back(array_of_tokens[i]);
    } else if ((array_of_tokens[i].type_ >= COS &&
                array_of_tokens[i].type_ <= LOG) ||
               (array_of_tokens[i].type_ == OPEN_BRACKET)) {
      operation_stack.push(array_of_tokens[i]);
    } else if (array_of_tokens[i].type_ >= UNARY_PLUS &&
               array_of_tokens[i].type_ <= BINARY_MINUS) {
      create_operators_stack(i);
    } else if (array_of_tokens[i].type_ == CLOSE_BRACKET) {
      from_stack_to_output_array();
    }
  }
  while (!operation_stack.empty()) {
    if (operation_stack.top().type_ == OPEN_BRACKET ||
        operation_stack.top().type_ == CLOSE_BRACKET) {
      error = false;
    }
    output_array.push_back(operation_stack.top());
    operation_stack.pop();
  }
}

int Model::operation_priority(const int &type) {
  int res;
  if (type == 9 || type == 10) {
    res = 0;
  } else if (type == 5 || type == 6) {
    res = 1;
  } else if (type == 3 || type == 4) {
    res = 4;
  } else {
    res = 3;
  }
  return res;
}

bool Model::operator_associativity(const int &type) {
  bool res;
  if (type == 9 || type == 10 || type == 5 || type == 6) {
    res = true;
  } else {
    res = false;
  }
  return res;
}

void Model::CheckODZ(const int &type, double data) {
  if (type == TAN) {
    while (fabs(data) > M_PI) {
      if (data <= 0) {
        data += M_PI;
      } else {
        data -= M_PI;
      }
    }
    if (fabs(data) <= (M_PI / 2.0 + 0.1) && fabs(data) >= (M_PI / 2.0 - 0.1)) {
      error = false;
    }
  } else if ((type == SQRT && data < 0.000001) ||
             ((type == LN || type == LOG) && data <= 0) ||
             ((type == DIV || type == MOD) && data > -0.000001 &&
              data < 0.000001)) {
    error = false;
  }
}

void Model::auxiliary_calculations(const bool &type, const int &operators) {
  if (type == false) {
    if (!operation_stack.empty()) {
      CheckODZ(operators, operation_stack.top().data_);
      if (operators == UNARY_MINUS) {
        operation_stack.top().data_ = -1 * (operation_stack.top().data_);
      } else if (operators == COS) {
        operation_stack.top().data_ = cos(operation_stack.top().data_);
      } else if (operators == SIN) {
        operation_stack.top().data_ = sin(operation_stack.top().data_);
      } else if (operators == TAN) {
        operation_stack.top().data_ = tan(operation_stack.top().data_);
      } else if (operators == ACOS) {
        operation_stack.top().data_ = acos(operation_stack.top().data_);
      } else if (operators == ASIN) {
        operation_stack.top().data_ = asin(operation_stack.top().data_);
      } else if (operators == ATAN) {
        operation_stack.top().data_ = atan(operation_stack.top().data_);
      } else if (operators == SQRT) {
        operation_stack.top().data_ = sqrt(operation_stack.top().data_);
      } else if (operators == LN) {
        operation_stack.top().data_ = log(operation_stack.top().data_);
      } else if (operators == LOG) {
        operation_stack.top().data_ = log10(operation_stack.top().data_);
      }
    }
  } else {
    if (operation_stack.size() >= 2) {
      CheckODZ(operators, operation_stack.top().data_);
      double second = operation_stack.top().data_;
      operation_stack.pop();
      if (operators == MULT) {
        operation_stack.top().data_ *= (second);
      } else if (operators == DIV) {
        operation_stack.top().data_ /= (second);
      } else if (operators == DEGREE) {
        operation_stack.top().data_ = pow(operation_stack.top().data_, second);
      } else if (operators == MOD) {
        operation_stack.top().data_ = fmod(operation_stack.top().data_, second);
      } else if (operators == BINARY_PLUS) {
        operation_stack.top().data_ += second;
      } else if (operators == BINARY_MINUS) {
        operation_stack.top().data_ -= second;
      }
    }
  }
}

double Model::calculation() {
  for (int i = 0; i < (int)output_array.size() && error == true; i++) {
    if (output_array[i].type_ == NUMBER) {
      operation_stack.push(output_array[i]);
    } else if (output_array[i].type_ == UNARY_MINUS ||
               (output_array[i].type_ >= COS && output_array[i].type_ <= LOG)) {
      auxiliary_calculations(false, output_array[i].type_);
    } else {
      auxiliary_calculations(true, output_array[i].type_);
    }
  }
  return !operation_stack.empty() ? operation_stack.top().data_ : 0;
}

const std::pair<double, bool> Model::smart_calc(const std::string &str,
                                                const double &x) {
  x_ = x;
  error = true;
  parser(str);
  input_validation();
  dublicat_validation();
  deicstra_algorithm();
  const std::pair<double, bool> result(calculation(), error);
  array_of_tokens.clear();
  output_array.clear();
  error = true;
  for (int i = 0; i < (int)operation_stack.size(); i++) {
    operation_stack.pop();
  }
  return result;
}

std::vector<double> Model::calc_annuity(double sum, double percent,
                                        int months) {
  double res = 0;
  if (percent > 0 && sum > 0 && months > 0) {
    double months_percent = percent / 12;
    double annuity_ratio =
        (months_percent * pow((1 + months_percent), months)) /
        (pow((1 + months_percent), months) - 1);
    res = sum * annuity_ratio;
  } else {
    error = false;
  }
  return {res, (months * res) - sum, months * res};
}

double Model::calc_total_payout(double sum, double percent, int months) {
  double res = calc_mounth_payout(sum, percent, months);
  return months > 1 ? res + calc_total_payout(sum - (sum / months), percent,
                                              months - 1)
                    : 0;
}

double Model::calc_mounth_payout(double sum, double percent, int months) {
  double part_of_the_principal = sum / months;
  double interest_amount = sum * percent * (30.0 / 365.0);
  return part_of_the_principal + interest_amount;
}

std::vector<double> Model::calc_differentiated(double sum, double percent,
                                               int months) {
  double res = 0;
  double total_payout = 0;
  if (percent > 0 && sum > 0 && months > 0) {
    res = calc_mounth_payout(sum, percent, months);
    total_payout = calc_total_payout(sum, percent, months);
  } else {
    error = false;
  }
  return {res, total_payout - sum, total_payout};
}

std::pair<const std::vector<double>, const bool> Model::calc_credit(
    const std::string &sum_str, const std::string &percent_str,
    const std::string &months_str, bool type) {
  error = true;
  double sum = create_number(sum_str);
  double percent = create_number(percent_str) / 100.0;
  int months = (int)create_number(months_str);
  std::pair<std::vector<double>, bool> result;
  if (type == true) {
    result.first = calc_differentiated(sum, percent, months);
  } else {
    result.first = calc_annuity(sum, percent, months);
  }
  result.second = error;
  return result;
}

std::pair<std::vector<double>, bool> Model::calc_deposit(
    const std::vector<std::string> &input_vector,
    const bool &interest_capitalization, const int &payment_period,
    const std::pair<std::vector<std::pair<std::string, std::string>>,
                    std::vector<std::pair<std::string, std::string>>>
        &add_and_get_lists) {
  error = true;
  std::vector<double> input_vector_double;
  for (int i = 0; i < 4; i++) {
    if (i == 2 || i == 3) {
      input_vector_double.push_back(create_number(input_vector[i]) / 100.0);
    } else {
      input_vector_double.push_back(create_number(input_vector[i]));
    }
  }
  const std::pair<std::vector<double>, bool> result(
      deposit_result(input_vector_double, interest_capitalization,
                     payment_period, add_and_get_lists),
      error);
  return result;
}

double Model::operations_in_month(
    Model::Date date,
    const std::vector<std::pair<std::string, std::string>> &operations_vector,
    const int &type) {
  double res = 0;
  Model::Date this_month(date);
  this_month.get_next_date(type);
  for (int i = 0; i < (int)operations_vector.size(); i++) {
    int day = (operations_vector[i].first[0] - '0') * 10 +
              (operations_vector[i].first[1] - '0');
    int month = (operations_vector[i].first[3] - '0') * 10 +
                (operations_vector[i].first[4] - '0');
    int year = (operations_vector[i].first[6] - '0') * 1000 +
               (operations_vector[i].first[7] - '0') * 100 +
               (operations_vector[i].first[8] - '0') * 10 +
               (operations_vector[i].first[9] - '0');
    Model::Date tmp_date(day, month, year);
    if (tmp_date >= date && !(tmp_date >= this_month)) {
      res += create_number(operations_vector[i].second);
    }
  }
  return res;
}

void Model::Date::get_next_date(const int &payment_period) {
  if (payment_period == 0 || payment_period == 3) {
    next_month();
  } else if (payment_period == 1) {
    for (int j = 0; j < 6; j++) {
      next_month();
    }
  } else {
    next_year();
  }
}

int Model::create_count(const int &payment_period, const double &month) {
  int count;
  if (payment_period == 0 || payment_period == 3) {
    count = (int)month;
  } else if (payment_period == 1) {
    count = (int)month / 6;
  } else {
    count = (int)month / 12;
  }
  return count;
}

std::vector<double> Model::deposit_result(
    std::vector<double> input_vector_double,
    const bool &interest_capitalization, const int &payment_period,
    const std::pair<std::vector<std::pair<std::string, std::string>>,
                    std::vector<std::pair<std::string, std::string>>>
        &add_and_get_lists) {
  std::vector<double> result_vector(3);
  if (input_vector_double[0] > 0 && input_vector_double[1] > 0 &&
      input_vector_double[2] > 0 && input_vector_double[3] >= 0) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    Model::Date actual_date((int)(ltm->tm_mday), (int)(1 + ltm->tm_mon),
                            (int)(1900 + ltm->tm_year));
    int count = create_count(payment_period, input_vector_double[1]);
    input_vector_double[2] /= count;
    input_vector_double[3] /= count;
    for (int i = 0; i < count; i++) {
      double add_in_month = operations_in_month(
          actual_date, add_and_get_lists.first, payment_period);
      double get_in_month = operations_in_month(
          actual_date, add_and_get_lists.second, payment_period);
      input_vector_double[0] += add_in_month;
      input_vector_double[0] -= get_in_month;
      double add_in_this_period =
          input_vector_double[0] * input_vector_double[2];
      double nalog = input_vector_double[0] * input_vector_double[3];
      if (interest_capitalization) {
        input_vector_double[0] += add_in_this_period - nalog;
        result_vector[0] += 0;
      } else {
        result_vector[0] += add_in_this_period - nalog;
      }
      result_vector[1] += nalog;
      result_vector[2] = input_vector_double[0];
      actual_date.get_next_date(payment_period);
    }
  } else {
    error = false;
  }
  return result_vector;
}

bool Model::Date::is_great_or_equal(const Model::Date &date) {
  bool result = true;
  if (this->date.year_ == date.date.year_) {
    if (this->date.month_ == date.date.month_) {
      if (this->date.day_ < date.date.month_) {
        result = false;
      }
    } else if (this->date.month_ < date.date.month_) {
      result = false;
    }
  } else if (this->date.year_ < date.date.year_) {
    result = false;
  }
  return result;
}

bool Model::Date::operator>=(const Model::Date &date) {
  return is_great_or_equal(date);
}

Model::Date::Date(int day, int month, int year) {
  date.day_ = day;
  date.month_ = month;
  date.year_ = year;
}

Model::Date::Date(const Date &other) {
  date.day_ = other.date.day_;
  date.month_ = other.date.month_;
  date.year_ = other.date.year_;
}

void Model::Date::next_month() {
  if (date.month_ == 12) {
    date.month_ = 0;
    next_year();
  } else {
    date.month_++;
  }
}

void Model::Date::next_year() { date.year_++; }

}  // namespace s21
