#pragma once
#include "esphome/core/component.h"
#include "esphome/components/levoit/levoit.h"
#include "esphome/components/light/light_state.h"
#include "esphome/components/light/light_output.h"  // Include for LightOutput
#include "esphome/components/light/light_call.h"  // Include for LightCall
namespace esphome {
  namespace levoit {

    enum LevoitLightPurpose : uint8_t { NIGHT_LIGHT };
    class LevoitLight : public light::LightOutput, public light::LightCall, public light::LightState, light::LightColorValues {
      public:
        
  
      LevoitLight(Levoit *parent) : parent_(parent), LightState(this), LightCall(this)  {}
        void setup() override;
        void dump_config() override;
         

      light::LightTraits get_traits() override;

      //void LevoitLight::setup_state(light::LightState *state) override;

      void write_state(light::LightState *state) override;
        
      private: 
        float* brightness;
      protected:
        Levoit *parent_;
        float *output_;
        //light::LightState *state_{nullptr};
        
        //output::FloatOutput *output_;
    };
  }
}  // namespace levoit
  // namespace esphome
