// #pragma once
// #include "esphome/core/component.h"
// #include "esphome/components/levoit/levoit.h"
// #include "esphome/core/helpers.h"
// #include "esphome/components/light/light_output.h"  // Include for LightOutput
// namespace esphome {
//   namespace levoit {

//     //enum LevoitLightPurpose : uint8_t { NIGHT_LIGHT };
//     class LevoitLight : public Component, public light::LightOutput {
//       public:
//         LevoitLight(Levoit *parent) : parent_(parent) {}
//         void setup() override;
//         void dump_config() override;
//         light::LightTraits get_traits() override;
//         void setup_state(light::LightState *state) override { this->state_ = state; };
//         void write_state(light::LightState *state) override;
//       //LevoitLight(Levoit *parent) : parent_(parent), LightState(this), LightCall(this)  {}
//       //void LevoitLight::setup_state(light::LightState *state) override;
//       //private: 
//         //float* brightness;
//       protected:
//         Levoit *parent_;
//         float *output_;
//         light::LightState *state_{nullptr};
//         void publish_state_(uint8_t brightness);
//         bool control_dimmer_(uint8_t brightness);
//         void process_command_();
//         uint8_t last_brightness_{0};
//         bool last_binary_{false};
//         uint8_t min_value_{0};
//         uint8_t max_value_{100};
        
//         //output::FloatOutput *output_;
//     };
//   }
// }  // namespace levoit
//   // namespace esphome
