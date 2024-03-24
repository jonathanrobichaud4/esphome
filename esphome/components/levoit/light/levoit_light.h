#pragma once
#include "esphome/core/component.h"
#include "esphome/components/levoit/levoit.h"
#include "esphome/components/light/light_state.h"
#include "esphome/components/light/light_output.h"  // Include for LightOutput
namespace esphome {
  namespace levoit {

    class LevoitLight : public Component, public light::LightOutput {
      public:
        void setup() override;
        LevoitLight(Levoit *parent, float *output) : parent_(parent), output_(output) {
          output_ = output;
        }
        light::LightTraits get_traits() override {
          auto traits = light::LightTraits();
          traits.set_supported_color_modes({light::ColorMode::BRIGHTNESS});
          return traits;
        }

        

        //void set_output(output::FloatOutput *output) { output_ = output; }

        


        void write_state(light::LightState *state) override;
        void dump_config() override;
        

      protected:
        Levoit *parent_;
        float *output_;
        //output::FloatOutput *output_;
    };
  }
}  // namespace levoit
  // namespace esphome
