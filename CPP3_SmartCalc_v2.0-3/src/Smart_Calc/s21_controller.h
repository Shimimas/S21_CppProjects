#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>

#include "s21_model.h"

namespace s21 {

class Controller {
 private:
  Model *model;

 public:
  Controller(Model *m) : model(m){};
  std::pair<double, bool> input(const std::string &str, const double &x);
  std::pair<const std::vector<double>, const bool> credit(
      const std::string &sum_str, const std::string &percent_str,
      const std::string &months_str, bool type);
  std::pair<std::vector<double>, bool> deposit(
      const std::vector<std::string> &input_vector,
      const bool &interest_capitalization, const int &payment_period,
      const std::pair<std::vector<std::pair<std::string, std::string>>,
                      std::vector<std::pair<std::string, std::string>>>
          &add_and_get_lists);
};

}  // namespace s21

#endif
