#pragma once

#include "esphome/core/component.h"
#include "esphome/components/levoit/levoit.h"
#include "esphome/components/number/number.h"
// /#include "esphome/components/output/float_output.h"

namespace esphome {
namespace levoit {

enum LevoitNumberPurpose: uint8_t { HUMIDITY_LEVEL, LIGHT};

class LevoitNumber : public number::Number, public Component{//output::FloatOutput {
 public:
  LevoitNumber(Levoit *parent, LevoitNumberPurpose purpose) : parent_(parent), purpose_(purpose) {}
  void setup() override;
  void dump_config() override;
  //bool auto_off = false;

  protected:
    void control(float value) override;
    Levoit *parent_;
    LevoitNumberPurpose purpose_;
    number::NumberCall *call_{nullptr};

};

} //namespace Levoit
} //namespace esphome
