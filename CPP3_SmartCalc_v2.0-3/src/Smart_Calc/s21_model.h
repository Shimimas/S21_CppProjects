#ifndef Model_H
#define Model_H

#include <stdarg.h>

#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

namespace s21 {

typedef enum {
  NUMBER = 0,
  OPEN_BRACKET = 1,
  CLOSE_BRACKET = 2,
  UNARY_PLUS = 3,
  UNARY_MINUS = 4,
  MULT = 5,
  DIV = 6,
  DEGREE = 7,
  MOD = 8,
  BINARY_PLUS = 9,
  BINARY_MINUS = 10,
  COS = 11,
  SIN = 12,
  TAN = 13,
  ACOS = 14,
  ASIN = 15,
  ATAN = 16,
  SQRT = 17,
  LN = 18,
  LOG = 19,
  IKS = 20,
  NT = 21
} operation_t;

class Model {
 private:
  typedef struct lexeme_struct {
    double data_ = 0;
    operation_t type_;
    lexeme_struct(double value, int type)
        : data_(value), type_((operation_t)type){};
  } lexeme_t;

  class Date {
   public:
    Date(int day, int month, int year);
    Date(const Date &other);
    ~Date(){};

    bool operator>=(const Date &other);

    void next_month();
    void next_year();
    void get_next_date(const int &payment_period);

   private:
    typedef struct date_struct {
      int day_ = 0;
      int month_ = 0;
      int year_ = 0;
    } date_t;

    date_t date;

    bool is_great_or_equal(const Date &date);
  };

  std::vector<lexeme_t> array_of_tokens;
  std::vector<lexeme_t> output_array;
  std::stack<lexeme_t> operation_stack;
  double x_ = 0;
  bool error = true;

  bool definition_of_tokens(int &i, const std::string &str, const int &amount,
                            ...);
  double create_number(const std::string &number_string);
  void deicstra_algorithm();
  void input_validation();
  bool operator_associativity(const int &type);
  int operation_priority(const int &type);
  void auxiliary_calculations(const bool &type, const int &operators);
  double calculation();
  void parser(const std::string &str);
  void create_operators_stack(const int &i);
  void from_stack_to_output_array();
  void dublicat_validation();
  double from_exp_form_to_double(const std::string &number_string);
  void number_processing(int &i, const std::string &str);
  std::vector<double> calc_annuity(double sum, double percent, int months);
  std::vector<double> calc_differentiated(double sum, double percent,
                                          int months);
  double calc_total_payout(double sum, double percent, int months);
  double calc_mounth_payout(double sum, double percent, int months);
  void CheckODZ(const int &type, double data);
  std::vector<double> deposit_result(
      std::vector<double> input_vector_double,
      const bool &interest_capitalization, const int &payment_period,
      const std::pair<std::vector<std::pair<std::string, std::string>>,
                      std::vector<std::pair<std::string, std::string>>>
          &add_and_get_lists);
  double operations_in_month(
      Date date,
      const std::vector<std::pair<std::string, std::string>> &operations_vector,
      const int &type);
  int create_count(const int &payment_period, const double &month);

 public:
  Model(){};
  ~Model(){};

  const std::pair<double, bool> smart_calc(const std::string &str,
                                           const double &x);
  std::pair<const std::vector<double>, const bool> calc_credit(
      const std::string &sum_str, const std::string &percent_str,
      const std::string &months_str, bool type);
  std::pair<std::vector<double>, bool> calc_deposit(
      const std::vector<std::string> &input_vector,
      const bool &interest_capitalization, const int &payment_period,
      const std::pair<std::vector<std::pair<std::string, std::string>>,
                      std::vector<std::pair<std::string, std::string>>>
          &add_and_get_lists);
};

}  // namespace s21

#endif
