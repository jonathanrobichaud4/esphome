#include "esphome/core/log.h"
#include "levoit_number.h"

namespace esphome {
namespace levoit {

static const char *const TAG = "levoit.number";
//bool auto_off = false;
void LevoitNumber::setup() {
    this->parent_->register_listener(LevoitPayloadType::STATUS_RESPONSE, [this](uint8_t *payloadData, size_t payloadLen) {
      if (this->purpose_ == LevoitNumberPurpose::HUMIDITY_LEVEL) {
        this->publish_state(payloadData[14]);
      }
      /*if (this->purpose_ == LevoitNumberPurpose::TARGET_HUMIDITY) {
        this->publish_state(payloadData[6]);
      }*/
  });
}

void LevoitNumber::control(float value) {
    if (this->purpose_ == LevoitNumberPurpose::HUMIDITY_LEVEL) {
      if(this->has_state()){
        uint8_t humidity_level = value;
        ESP_LOGI(TAG, "Humidity level set to: %f", value);
        this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_HUMIDITY_LEVEL,
                                                  .packetType = LevoitPacketType::SEND_MESSAGE,
                                                  .payload = {0x00, 0x00, 0x01, humidity_level}});
    }
    }

    //Can I set the target withpout recalling the selected mode?
    if (this->purpose_ == LevoitNumberPurpose::TARGET_HUMIDITY) {
      //if(this->has_state()){
        this->parent_->humidity_target = value;
        uint8_t humidity_positive_offset = value - 5;
        uint8_t humidity_negative_offset = value + 5;
        ESP_LOGI(TAG, "Humidity Positive offset target set to: %f", humidity_positive_offset);
        ESP_LOGI(TAG, "Humidity Negative offset target set to: %f", humidity_negative_offset);
        ESP_LOGI(TAG, "Humidity target set to: %f", value);
        ESP_LOGI(TAG, "Humidity target set to: %f", this->parent_->humidity_target);
        ESP_LOGI(TAG, "Humidity mode set to: %f", this->parent_->humidity_mode);
        if(this->parent_->humidity_mode == 0){
        
        this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_HUMIDIFIER_MODE_AUTO,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00, this->parent_->humidity_target, humidity_negative_offset, humidity_positive_offset, 0x09, 0x05, 0x01}});
        this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::HUMIDIFIER_TARGET_CONFIRM,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00}});

        ESP_LOGI(TAG, "Humidity target set to: %f", value);
        ESP_LOGI(TAG, "Humidity target set to: %f", this->parent_->humidity_target);
        ESP_LOGI(TAG, "Humidity target set to: %d", this->parent_->humidity_mode);
        }
        if(this->parent_->humidity_mode == 2) {
          this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_HUMIDIFIER_MODE_SLEEP,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00, this->parent_->humidity_target, humidity_negative_offset, humidity_positive_offset, 0x09, 0x05, 0x01}});
          this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::HUMIDIFIER_TARGET_CONFIRM,
                                                    .packetType = LevoitPacketType::SEND_MESSAGE,
                                                    .payload = {0x00}});
          ESP_LOGI(TAG, "Humidity target set to: %f", value);
          ESP_LOGI(TAG, "Humidity target set to: %f", this->parent_->humidity_target);
          ESP_LOGI(TAG, "Humidity target set to: %f", this->parent_->humidity_mode);
        }
      //}
        // if(this->parent_->humidity_mode == 1){
        //   this->parent_->humidity_target = value;
        //   uint8_t humidity_positive_offset = this->parent_->humidity_target - 5;
        //   uint8_t humidity_negative_offset = this->parent_->humidity_target + 5;
        //   this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_HUMIDIFIER_MODE_MANUAL,
        //                                           .packetType = LevoitPacketType::SEND_MESSAGE,
        //                                           .payload = {0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00}});
        //   this->parent_->send_command(LevoitCommand{.payloadType = LevoitPayloadType::SET_HUMIDIFIER_TARGET_HUMIDITY,
        //                                           .packetType = LevoitPacketType::SEND_MESSAGE,
        //                                           .payload = {0x00, 0x00, 0x01, this->parent_->humidity_target, humidity_positive_offset, humidity_negative_offset}});
        // }
    }
}

void LevoitNumber::dump_config() {
    ESP_LOGI("", "Levoit Number", this);
}

} //namespace levoit
} //namespace esphome
