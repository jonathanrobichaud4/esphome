#pragma once

#include "esphome/core/component.h"
#include "esphome/components/levoit/levoit.h"
#include "esphome/components/number/number.h"

namespace esphome {
namespace levoit {

enum LevoitNumberPurpose: uint8_t { HUMIDITY_LEVEL};

class LevoitNumber : public number::Number, public Component {
 public:
  LevoitNumber(Levoit *parent, LevoitNumberPurpose purpose) : parent_(parent), purpose_(purpose) {}
  void setup() override;
  void dump_config() override;

  protected:
    void control(float value) override;
    Levoit *parent_;
    LevoitNumberPurpose purpose_;

};

} //namespace Levoit
} //namespace esphome
