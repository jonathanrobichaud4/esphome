import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from esphome.const import CONF_OUTPUT_ID

from .. import levoit_ns, CONF_LEVOIT_ID, Levoit
# TODO: ADD ICONS
CONF_HUMIDITY_LEVEL = "humidity_level"

LevoitNumber = levoit_ns.class_("LevoitNumber", cg.Component, number.Number)
LevoitNumberPurpose = levoit_ns.enum("LevoitNumberPurpose")

CONFIG_SCHEMA = (
    cv.Schema({
        cv.GenerateID(CONF_LEVOIT_ID): cv.use_id(Levoit),
        cv.Optional(CONF_HUMIDITY_LEVEL): number.number_schema(LevoitNumber)
      
    })
)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_LEVOIT_ID])
    if humidity_level := config.get(CONF_HUMIDITY_LEVEL):
        var = await number.new_number(humidity_level, parent, LevoitNumberPurpose.HUMIDITY_LEVEL, 0.0, 10.0 , 1)
        await cg.register_component(var, humidity_level)
