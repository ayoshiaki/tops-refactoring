#include "ProbabilisticModelParameterValue2.hpp"

#include <iostream>

#include <boost/lexical_cast.hpp>

namespace tops {

  // ProbabilisticModelParameterValue2
  std::string ProbabilisticModelParameterValue2::str() {
    return "ProbabilisticModelParameterValue2";
  }
  std::string ProbabilisticModelParameterValue2::parameterType() {
    return "ProbabilisticModelParameterValue2";
  }
  StringParameterValue2* ProbabilisticModelParameterValue2::toStringParameter() {
    std::cerr << "Invalid conversion" << std::endl;
    return NULL;
  }

  IntegerParameterValue2* ProbabilisticModelParameterValue2::toIntegerParameter() {
    std::cerr << "Invalid conversion" << std::endl;
    return NULL;
  }

  DoubleParameterValue2* ProbabilisticModelParameterValue2::toDoubleParameter() {
    std::cerr << "Invalid conversion" << std::endl;
    return NULL;
  }

  IntegerListParameterValue2* ProbabilisticModelParameterValue2::toIntegerListParameter() {
    std::cerr << "Invalid conversion" << std::endl;
    return NULL;
  }

  DoubleListParameterValue2* ProbabilisticModelParameterValue2::toDoubleListParameter() {
    std::cerr << "Invalid conversion" << std::endl;
    return NULL;
  }

  StringListParameterValue2* ProbabilisticModelParameterValue2::toStringListParameter() {
    std::cerr << "Invalid conversion" << std::endl;
    return NULL;
  }

  ProbabilityParameterValue2* ProbabilisticModelParameterValue2::toProbabilityParameter() {
    std::cerr << "Invalid conversion" << std::endl;
    return NULL;
  }

  IdentifierParameterValue2* ProbabilisticModelParameterValue2::toIdentifierParameter() {
    std::cerr << "Invalid conversion" << std::endl;
    return NULL;
  }

  ProbabilisticModelConfiguration* ProbabilisticModelParameterValue2::toConfigurationParameter() {
    std::cerr << "Invalid conversion" << std::endl;
    return NULL;
  }

  // StringParameterValue2
  std::string StringParameterValue2::parameterType() {
    return "StringParameterValue2";
  }

  std::string StringParameterValue2::str() {
    return _value;
  }

  std::string StringParameterValue2::value() {
    return _value;
  }

  StringParameterValue2* StringParameterValue2::toStringParameter() {
    return this;
  }

  // IntegerParameterValue2
  std::string IntegerParameterValue2::parameterType() {
    return "IntegerParameterValue2";
  }

  std::string IntegerParameterValue2::str() {
    return boost::lexical_cast<std::string>(_value);
  }

  int IntegerParameterValue2::value() {
    return _value;
  }

  IntegerParameterValue2* IntegerParameterValue2::toIntegerParameter() {
    return this;
  }

  // DoubleParameterValue2
  std::string DoubleParameterValue2::parameterType() {
    return "DoubleParameterValue2";
  }

  double DoubleParameterValue2::value() {
    return _value;
  }

  std::string DoubleParameterValue2::str() {
    return boost::lexical_cast<std::string>(_value);
  }

  DoubleParameterValue2* DoubleParameterValue2::toDoubleParameter() {
    return this;
  }

  // IntegerListParameterValue2
  std::string IntegerListParameterValue2::parameterType() {
    return "IntegerListParameterValue2";
  }

  std::string IntegerListParameterValue2::str() {
    std::string str = "(";
    std::vector<int>::iterator it;
    for (it = _value.begin(); it != _value.end(); it++) {
      str += boost::lexical_cast<std::string>(*it) + ", ";
    }
    str += ")";
    return str;
  }

  std::vector<int> IntegerListParameterValue2::value() {
    return _value;
  }

  // DoubleListParameterValue2
  std::string DoubleListParameterValue2::parameterType() {
    return "DoubleListParameterValue2";
  }

  std::vector<double> DoubleListParameterValue2::value() {
    return _value;
  }

  std::string DoubleListParameterValue2::str() {
    std::string str = "(";
    std::vector<double>::iterator it;
    for (it = _value.begin(); it != _value.end(); it++) {
      str += boost::lexical_cast<std::string>(*it) + ", ";
    }
    str += ")";
    return str;
  }

  // StringListParameterValue2
  std::string StringListParameterValue2::parameterType() {
    return "StringListParameterValue2";
  }

  std::vector<std::string> StringListParameterValue2::value() {
    return _value;
  }

  std::string StringListParameterValue2::str() {
    std::string str = "(";
    std::vector<std::string>::iterator it;
    for (it = _value.begin(); it != _value.end(); it++) {
      str += (*it) + ", ";
    }
    str += ")";
    return str;
  }

  // ProbabilityParameterValue2
  std::string ProbabilityParameterValue2::parameterType() {
    return "ProbabilityParameterValue2";
  }

  std::map<std::string, double> ProbabilityParameterValue2::value() {
    return _value;
  }

  // IdentifierParameterValue2
  std::string IdentifierParameterValue2::parameterType() {
    return "IdentifierParameterValue2";
  }

  std::string IdentifierParameterValue2::value() {
    return _value;
  }
}
