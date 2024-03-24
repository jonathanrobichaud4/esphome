import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import (
     ICON_LIGHTBULB
 )

from .. import levoit_ns, CONF_LEVOIT_ID, Levoit

DEPENDENCIES = ["levoit"]
CODEOWNERS = ["@acvigue"]

CONF_LIGHT = "night_light"

LevoitLight = levoit_ns.class_("LevoitLight", light.LightOutput, cg.Component)
LevoitLightPurpose = levoit_ns.enum("LevoitLightPurpose")
#LevoitLight = levoit_ns.class_('LevoitLight', light.LightOutput)

# CONFIG_SCHEMA = (
#     cv.Schema({
#         cv.GenerateID(CONF_LEVOIT_ID): cv.use_id(Levoit),
#         cv.Optional(CONF_LIGHT): light.BRIGHTNESS_ONLY_LIGHT_SCHEMA(LevoitLight).extend(cv.COMPONENT_SCHEMA),
#     })
# )

# CONFIG_SCHEMA = light.BRIGHTNESS_ONLY_LIGHT_SCHEMA.extend({
#     cv.GenerateID(CONF_LEVOIT_ID): cv.declare_id(LevoitLight),
#     #cv.Required(CONF_OUTPUT): cv.use_id(output.FloatOutput)
# })

CONFIG_SCHEMA = light.BRIGHTNESS_ONLY_LIGHT_SCHEMA.extend(
    {
        cv.GenerateID(CONF_LIGHT): cv.declare_id(LevoitLight),
        cv.GenerateID(CONF_LEVOIT_ID): cv.use_id(Levoit),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_LEVOIT_ID])
    
    var = cg.new_Pvariable(config[CONF_LIGHT], parent)
    await light.register_light(var, config)

    #out = yield cg.get_variable(config[CONF_OUTPUT])
    #cg.add(var.set_output(out))

    # if config_light := config.get(CONF_LIGHT):
    #     var = await light.new_light(config_light, parent, LevoitLightPurpose.NIGHT_LIGHT)
    #     await cg.register_component(var, config_light)
