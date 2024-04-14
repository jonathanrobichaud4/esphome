#include "esphome/core/log.h"
#include "levoit_select.h"
//#include <components/levoit/number/levoit_number.h>

namespace esphome {
namespace levoit {

static const char *const TAG = "levoit.select";

void LevoitSelect::setup() {
  this->parent_->register_listener(LevoitPayloadType::STATUS_RESPONSE, [this](const uint8_t *payloadBuf, size_t payloadLen) {
    switch (this->parent_->device_model_){
      case LevoitDeviceModel::CLASSIC_300S:
        if (this->purpose_ == LevoitSelectPurpose::HUMIDIFIER_MODE) {
          uint8_t humidifierMode = payloadBuf[13];
          if (humidifierMode == 0x00) {
            this->parent_->humidity_mode = 0;
            this->publish_state("auto");
          } else if (humidifierMode == 0x01) {
            this->parent_->humidity_mode = 1;
            this->publish_state("manual");
          } else if (humidifierMode == 0x02) {
            this->parent_->humidity_mode = 2;
            this->publish_state("sleep");
          }
        }

      default:
            if (this->purpose_ == LevoitSelectPurpose::PURIFIER_FAN_MODE) {
        uint8_t purifierFanMode = payloadBuf[5];
        if (purifierFanMode == 0x00) {
          this->publish_state("Manual");
        } else if (purifierFanMode == 0x01) {
          this->publish_state("Sleep");
        } else if (purifierFanMode == 0x02) {
          this->publish_state("Auto");
        }
      } else if (this->purpose_ == LevoitSelectPurpose::PURIFIER_AUTO_MODE) {
        uint8_t purifierAutoMode = payloadBuf[15];
        if (purifierAutoMode == 0x00) {
          this->publish_state("Default");
        } else if (purifierAutoMode == 0x01) {
          this->publish_state("Quiet");
        } else if (purifierAutoMode == 0x02) {
          this->publish_state("Efficient");
        }
      }
    }
    
    });
}

void LevoitSelect::control(const std::string &value) {
  switch (this->parent_->device_model_){
    case LevoitDeviceModel::CLASSIC_300S:
      if (this->purpose_ == LevoitSelectPurpose::HUMIDIFIER_MODE) {
        uint8_t humidity_positive_offset = this->parent_->humidity_target - 5;
        uint8_t humidity_negative_offset = this->parent_->humidity_target + 5;
        if (value == "manual") {
          
          this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_HUMIDIFIER_MODE_MANUAL,
                                                     .packetType = LevoitPacketType::SEND_MESSAGE,
                                                     .payload = {0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00}});
          this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_HUMIDITY_LEVEL,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00, 0x00, 0x01, this->parent_->humidity_level}});
        } else if (value == "sleep") {
          this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_HUMIDIFIER_MODE_SLEEP,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00, this->parent_->humidity_target, humidity_negative_offset, humidity_positive_offset, 0x09, 0x05, 0x01}});
        } else if (value == "auto") {
          this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_HUMIDIFIER_MODE_AUTO,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00, this->parent_->humidity_target, humidity_negative_offset, humidity_positive_offset, 0x09, 0x05, 0x01}});
        }
      }
    default:
      if (this->purpose_ == LevoitSelectPurpose::PURIFIER_FAN_MODE) {
        if (value == "Manual") {
          switch (this->parent_->device_model_) {
            case LevoitDeviceModel::CORE_400S:
              // enter manual mode by setting speed
              // TODO: would be nice to set to last known speed setting; but
              // can't access that from here afaik
              this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_FAN_MANUAL,
                                                        .packetType = LevoitPacketType::SEND_MESSAGE,
                                                        .payload = {0x00, 0x00, 0x01, 0x01}});
              break;

            default:
              // set fan mode = 0
              this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_FAN_MODE,
                                                        .packetType = LevoitPacketType::SEND_MESSAGE,
                                                        .payload = {0x00, 0x00}});
          }

        } else if (value == "Sleep") {
          this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_FAN_MODE,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00, 0x01}});
        } else if (value == "Auto") {
          this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_FAN_MODE,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00, 0x02}});
        }
      } else if (this->purpose_ == LevoitSelectPurpose::PURIFIER_AUTO_MODE) {
        if (value == "Default") {
          this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_FAN_AUTO_MODE,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00, 0x00, 0x00, 0x00}});
        } else if (value == "Quiet") {
          this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_FAN_AUTO_MODE,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00, 0x01, 0x00, 0x00}});
        } else if (value == "Efficient") {
          this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_FAN_AUTO_MODE,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00, 0x02, 0xEC, 0x04}});
        }
      }
  }
}

void LevoitSelect::dump_config() { LOG_SELECT("", "Levoit Select", this); }

}  // namespace levoit
}  // namespace esphome
