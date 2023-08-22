#include "s21_controller.h"

namespace s21 {

std::pair<double, bool> Controller::input(const std::string &str,
                                          const double &x) {
  return model->smart_calc(str, x);
}

std::pair<const std::vector<double>, const bool> Controller::credit(
    const std::string &sum_str, const std::string &percent_str,
    const std::string &months_str, bool type) {
  return model->calc_credit(sum_str, percent_str, months_str, type);
}

std::pair<std::vector<double>, bool> Controller::deposit(
    const std::vector<std::string> &input_vector,
    const bool &interest_capitalization, const int &payment_period,
    const std::pair<std::vector<std::pair<std::string, std::string>>,
                    std::vector<std::pair<std::string, std::string>>>
        &add_and_get_lists) {
  return model->calc_deposit(input_vector, interest_capitalization,
                             payment_period, add_and_get_lists);
}

}  // namespace s21
