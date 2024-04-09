#include "esphome/core/log.h"
#include "levoit_number.h"

namespace esphome {
namespace levoit {

static const char *const TAG = "levoit.number";
void LevoitNumber::setup() {
    this->parent_->register_listener(LevoitPayloadType::STATUS_RESPONSE, [this](uint8_t *payloadData, size_t payloadLen) {
      if (this->purpose_ == LevoitNumberPurpose::HUMIDITY_LEVEL) {
        this->publish_state(payloadData[14]);
      }
      if (this->purpose_ == LevoitNumberPurpose::TARGET_HUMIDITY) {
        this->publish_state(payloadData[10]);
      }
  });
}

void LevoitNumber::control(float value) {
    if (this->purpose_ == LevoitNumberPurpose::HUMIDITY_LEVEL) {
      if(this->has_state()){
        this->parent_->humidity_level = value;
        if(this->parent_->humidity_mode == 1){
          this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_HUMIDITY_LEVEL,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00, 0x00, 0x01, this->parent_->humidity_level}});
        }
    }
    }

    if (this->purpose_ == LevoitNumberPurpose::TARGET_HUMIDITY) {
      if(this->has_state()){
        this->parent_->humidity_target = value;
        uint8_t humidity_positive_offset = value + 5;
        uint8_t humidity_negative_offset = value - 5;
        if(this->parent_->humidity_mode == 0){
        
        this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_HUMIDIFIER_MODE_AUTO,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00, this->parent_->humidity_target, humidity_negative_offset, humidity_positive_offset, 0x09, 0x05, 0x01}});
        this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::HUMIDIFIER_TARGET_CONFIRM,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00}});
        }
        if(this->parent_->humidity_mode == 2) {
          this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_HUMIDIFIER_MODE_SLEEP,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00, this->parent_->humidity_target, humidity_negative_offset, humidity_positive_offset, 0x09, 0x05, 0x01}});
          this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::HUMIDIFIER_TARGET_CONFIRM,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00}});
        }
      }
    }
}

void LevoitNumber::dump_config() {
    ESP_LOGI("", "Levoit Number", this);
}

} //namespace levoit
} //namespace esphome
