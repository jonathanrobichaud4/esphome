#pragma once

#include "esphome/core/component.h"
#include "esphome/components/levoit/levoit.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace levoit {

enum LevoitBinarySensorPurpose : uint8_t { TANK_SENSOR, WATER_SENSOR};

class LevoitBinarySensor : public binary_sensor::BinarySensor, public Component {
 public:
  LevoitBinarySensor(Levoit *parent, LevoitBinarySensorPurpose purpose) : parent_(parent), purpose_(purpose) {}
  void setup() override;
  void dump_config() override;

  protected:
    Levoit *parent_;
    LevoitBinarySensorPurpose purpose_;
};

} //namespace Levoit
} //namespace esphome
