#pragma once

#include "esphome/core/component.h"
#include "esphome/core/defines.h"
#include "esphome/core/helpers.h"
#include "esphome/components/uart/uart.h"

#include <vector>
#include <unordered_map>

namespace esphome {
namespace levoit {
//bool auto_off = false;
enum class LevoitDeviceModel : uint8_t { NONE, CORE_300S, CORE_400S, CLASSIC_300S };

enum class LevoitPacketType : uint8_t { SEND_MESSAGE = 0x22, ACK_MESSAGE = 0x12, STATUS_MESSAGE = 0x02, ERROR = 0x52 };

enum class LevoitPayloadType : uint32_t {
  //confirmed working:
  
  SET_WIFI_STATUS_LED = 0x0129A1, //works
  SET_POWER_STATE = 0x0100A0, //works
  STATUS_RESPONSE = 0x018540,
  SET_LIGHT_BRIGHTNESS = 0x0103A0,
  SET_HUMIDITY_LEVEL = 0x0160A2,
  SET_HUMIDIFIER_MODE_MANUAL = 0x0129A1,
  SET_HUMIDIFIER_MODE_SLEEP = 0x018240,
  SET_HUMIDIFIER_MODE_AUTO = 0x018040,
  HUMIDIFIER_TARGET_CONFIRM = 0x018440,
  AUTO_OFF = 0x01E5A5,
  TIMER_LIGHT = 0x016AA2,
  //partially working:
  SET_SCREEN_BRIGHTNESS = 0x0105A1, //can turn screen on and off
  
  
  //Not sure:
  TIMER_STATUS = 0x0165A2,
  SET_TIMER_TIME = 0x0164A2,
  TIMER_START_OR_CLEAR = 0x0166A2,

 //not working/not applicable:
  //STATUS_REQUEST = 0x013140, //not possible on classic 300
  //STATUS_RESPONSE = 0x013040,
  SET_DISPLAY_LOCK = 0x0100D1,
  SET_FAN_AUTO_MODE = 0x01E6A5,
  SET_FAN_MANUAL = 0x0160A2,
  SET_FAN_MODE = 0x01E0A5,
  SET_FILTER_LED = 0x01E2A5,
  RESET_FILTER = 0x01E4A5,
};

struct LevoitListener {
  LevoitPayloadType type;
  std::function<void(uint8_t *buf, size_t len)> func;
};

typedef struct LevoitCommand {
  LevoitPayloadType payloadType;
  LevoitPacketType packetType;
  std::vector<uint8_t> payload;
} LevoitPacket;

using PayloadTypeOverrideMap = std::unordered_map<LevoitDeviceModel, std::unordered_map<LevoitPayloadType, uint32_t>>;

static const PayloadTypeOverrideMap MODEL_SPECIFIC_PAYLOAD_TYPES = {
    //{LevoitDeviceModel::CORE_400S,
     /*{
         {LevoitPayloadType::STATUS_REQUEST, 0x01b140}, {LevoitPayloadType::STATUS_RESPONSE, 0x01b040},
         // ... add other model-specific overrides here ...
     }},

     {LevoitDeviceModel::CLASSIC_300S,
     {
         //{LevoitPayloadType::STATUS_REQUEST, 0x01b140}, {LevoitPayloadType::STATUS_RESPONSE, 0x01b040}, ESP doesn't send a request for status, 
         //it just sends a status message every ~4 seconds every ~4 senconds
         // ... add other model-specific overrides here ...
     }},*/


    // ... add other device models and their overrides here ...
};

class Levoit : public Component, public uart::UARTDevice {
 public:
  
  LevoitDeviceModel device_model_ = LevoitDeviceModel::CORE_300S;
  float get_setup_priority() const override { return setup_priority::LATE; }
  void setup() override;
  void loop() override;
  void dump_config() override;
  uint8_t humidity_target;
  uint8_t humidity_level;
  bool auto_off;
  int humidity_mode;
  void register_listener(LevoitPayloadType payloadType, const std::function<void(uint8_t *buf, size_t len)> &func);
  uint32_t get_model_specific_payload_type(LevoitPayloadType type);
  void send_command(const LevoitCommand &command);
  void set_device_model(std::string model);

 protected:
  bool validate_message_();
  void handle_char_(uint8_t c);
  void handle_payload_(LevoitPayloadType type, uint8_t sequenceNumber, uint8_t *payload, size_t len);
  void process_command_queue_();
  void send_raw_command(LevoitCommand command);
  std::vector<uint8_t> rx_message_;
  uint32_t last_command_timestamp_ = 0;
  uint32_t last_rx_char_timestamp_ = 0;
  std::vector<LevoitCommand> command_queue_;
  uint8_t sequenceNumber = 0;
  bool lastCommandAcked = false;
  int lastCommandRetries = 0;
  std::vector<LevoitListener> listeners_;
};

}  // namespace levoit
}  // namespace esphome
