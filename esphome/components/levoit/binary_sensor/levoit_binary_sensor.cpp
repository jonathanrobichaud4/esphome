#include "esphome/core/log.h"
#include "levoit_binary_sensor.h"

namespace esphome {
namespace levoit {

static const char *const TAG = "levoit.binary_sensor";

void LevoitBinarySensor::setup() {
    this->parent_->register_listener(LevoitPayloadType::STATUS_RESPONSE, [this](uint8_t *payloadData, size_t payloadLen) {
      if (this->purpose_ == LevoitBinarySensorPurpose::TANK_SENSOR) {
        this->publish_state(payloadData[5]);
      }
      else if (this->purpose_ == LevoitBinarySensorPurpose::WATER_SENSOR) {
        this->publish_state(payloadData[6]);
      }
  });
}

void LevoitBinarySensor::dump_config() {
    LOG_BINARY_SENSOR("", "Levoit Binary Sensor", this);
}

} //namespace levoit
} //namespace esphome
