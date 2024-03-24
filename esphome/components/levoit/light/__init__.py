import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import (
     ICON_LIGHTBULB, CONF_LIGHT
 )

from .. import levoit_ns, CONF_LEVOIT_ID, Levoit

DEPENDENCIES = ["levoit"]
CODEOWNERS = ["@acvigue"]

LevoitLight = levoit_ns.class_("LevoitLight", cg.Component, light.LightOutput)
LevoitLightPurpose = levoit_ns.enum("LevoitLightPurpose")
#LevoitLight = levoit_ns.class_('LevoitLight', light.LightOutput)

CONFIG_SCHEMA = (
    cv.Schema({
        cv.GenerateID(CONF_LEVOIT_ID): cv.use_id(Levoit),
        cv.Optional(CONF_LIGHT): light.BRIGHTNESS_ONLY_LIGHT_SCHEMA(LevoitLight).extend(cv.COMPONENT_SCHEMA),
    })
)

async def to_code(config):
    parent = await cg.get_variable(config[CONF_LEVOIT_ID])

    if config_light := config.get(CONF_LIGHT):
        var = await light.new_light(config_light, parent, LevoitLightPurpose.LIGHT)
        await cg.register_component(var, config_light)
