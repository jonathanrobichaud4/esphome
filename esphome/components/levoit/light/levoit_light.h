#pragma once
#include "esphome/core/component.h"
#include "esphome/components/levoit/levoit.h"
#include "esphome/components/light/light_state.h"
#include "esphome/components/light/light_output.h"  // Include for LightOutput
#include "esphome/components/light/light_call.h"  // Include for LightCall
namespace esphome {
  namespace levoit {

    class LevoitLight : public light::LightOutput, public light::LightCall, public light::LightState, light::LightColorValues {
      public:
        
  
      LevoitLight(Levoit *parent) : LightState(this), LightCall(this), parent_(parent) {}
        void setup() override;
        void dump_config() override;
        light::LightTraits get_traits() override {
          auto traits = light::LightTraits();
          traits.set_supported_color_modes({light::ColorMode::BRIGHTNESS});
          return traits;
        }

      void write_state(light::LightState *state) override;
        
      private: 
        float* brightness;
      protected:
        Levoit *parent_;
        float *output_;
        
        //output::FloatOutput *output_;
    };
  }
}  // namespace levoit
  // namespace esphome
