import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from esphome.const import CONF_ID

from .. import levoit_ns, CONF_LEVOIT_ID, Levoit
# TODO: ADD ICONS
CONF_HUMIDITY_LEVEL = "humidity_level"
CONF_LIGHT = "night_light"
CONF_TARGET_HUMIDITY = "target_humidity"

LevoitNumber = levoit_ns.class_("LevoitNumber", cg.Component, number.Number)
LevoitNumberPurpose = levoit_ns.enum("LevoitNumberPurpose")

CONFIG_SCHEMA = (
    cv.Schema({
        cv.GenerateID(CONF_LEVOIT_ID): cv.use_id(Levoit),
        cv.Optional(CONF_HUMIDITY_LEVEL): number.number_schema(LevoitNumber),
        cv.Optional(CONF_TARGET_HUMIDITY): number.number_schema(LevoitNumber),
        cv.Optional(CONF_LIGHT): number.number_schema(LevoitNumber)
      
    })
)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_LEVOIT_ID])
    if humidity_level := config.get(CONF_HUMIDITY_LEVEL):
        var = cg.new_Pvariable(humidity_level[CONF_ID], parent, LevoitNumberPurpose.HUMIDITY_LEVEL)
        await number.register_number(var, humidity_level, min_value=1, max_value=9, step=1)
        await cg.register_component(var, humidity_level)
    if target_humidity := config.get(CONF_TARGET_HUMIDITY):
        var = cg.new_Pvariable(target_humidity[CONF_ID], parent, LevoitNumberPurpose.TARGET_HUMIDITY)
        await number.register_number(var, target_humidity, min_value=1, max_value=100, step=1)
        await cg.register_component(var, target_humidity)
    if night_light := config.get(CONF_LIGHT):
        var = cg.new_Pvariable(night_light[CONF_ID], parent, LevoitNumberPurpose.LIGHT)
        await number.register_number(var, night_light, min_value=0, max_value=100, step=1)
        await cg.register_component(var, night_light)
