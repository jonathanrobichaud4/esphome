#pragma once

#include "esphome/core/component.h"
#include "esphome/components/levoit/levoit.h"
#include "esphome/components/output/float_output.h"

namespace esphome {
namespace levoit {

enum LevoitFloatPurpose: uint8_t { LIGHT};

class LevoitFloat : public output::FloatOutput, public Component {
 public:
  LevoitFloat(Levoit *parent, LevoitFloatPurpose purpose) : parent_(parent), purpose_(purpose) {}
  void setup() override;
  void dump_config() override;

  protected:
    void write_state(float value) override;
    Levoit *parent_;
    LevoitFloatPurpose purpose_;
    //output::FloatOutput:: *call_{nullptr};

};

} //namespace Levoit
} //namespace esphome
