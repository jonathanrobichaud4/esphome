#pragma once
#include "esphome/core/component.h"
#include "esphome/components/levoit/levoit.h"
#include "esphome/components/light/light_output.h"  // Include for LightOutput
namespace esphome {
  namespace levoit {

    //enum LevoitLightPurpose : uint8_t { NIGHT_LIGHT };
    class LevoitLight : public Component, public light::LightOutput {
      public:
        LevoitLight(Levoit *parent) : parent_(parent) {}
        void setup() override;
        void dump_config() override;
        light::LightTraits get_traits() override;
        void setup_state(light::LightState *state) override;
        void write_state(light::LightState *state) override;
      //LevoitLight(Levoit *parent) : parent_(parent), LightState(this), LightCall(this)  {}
      //void LevoitLight::setup_state(light::LightState *state) override;
      //private: 
        //float* brightness;
      protected:
        Levoit *parent_;
        float *output_;
        light::LightState *state_{nullptr};
        
        //output::FloatOutput *output_;
    };
  }
}  // namespace levoit
  // namespace esphome
