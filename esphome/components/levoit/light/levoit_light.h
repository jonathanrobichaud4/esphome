#pragma once

#include "esphome/core/component.h"
#include "esphome/components/levoit/levoit.h"
#include "esphome/components/monochromatic/monochromatic_light_output.h"
#include "esphome/components/light/light_state.h"
//#include "esphome/components/output/float_output.h"

namespace esphome {
namespace levoit {

class LevoitLight : public Component, public monochromatic::MonochromaticLightOutput, public light::LightOutput{
 public:
  LevoitLight(Levoit *parent) : parent_(parent) {}
  void set_output(output::FloatOutput *output) { output_ = output; }
  void setup() override;
  void set_output(output::FloatOutput * output);
  void dump_config() override;

  light::LightTraits get_traits() override {
    auto traits = light::LightTraits();
    traits.set_supported_color_modes({light::ColorMode::BRIGHTNESS});
    return traits;
  }

  void write_state(light::LightState *state) override {
    float bright;
    state->current_values_as_brightness(&bright);
    this->output_->set_level(bright);

    // Send brightness command over UART
   // uint8_t brightness_value = static_cast<uint8_t>(bright * 255.0f); // assuming brightness is normalized
    //uart_->write({0x00, brightness_value});
  }

  protected:
 // void write_state(output::FloatOutput brightness) override;
  Levoit *parent_;
  output::FloatOutput *output_;
  //light::LightState light_state_;
  //std::unique_ptr<light::LightState> light_state_;

 private:
  //bool power;
  //float brightness;
  esphome::output::FloatOutput * brightness;
};

}  // namespace levoit
}  // namespace esphome
