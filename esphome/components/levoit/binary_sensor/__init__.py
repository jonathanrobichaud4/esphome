import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import CONF_OUTPUT_ID

from .. import levoit_ns, CONF_LEVOIT_ID, Levoit
# TODO: ADD ICONS
CONF_TANK_SENSOR = "tank_sensor"
CONF_WATER_SENSOR = "water_sensor"

LevoitBinarySensor = levoit_ns.class_("LevoitBinarySensor", cg.Component, binary_sensor.BinarySensor)
LevoitBinarySensorPurpose = levoit_ns.enum("LevoitBinarySensorPurpose")

CONFIG_SCHEMA = (
    cv.Schema({
        cv.GenerateID(CONF_LEVOIT_ID): cv.use_id(Levoit),
        cv.Optional(CONF_TANK_SENSOR): binary_sensor.binary_sensor_schema(LevoitBinarySensor),
        cv.Optional(CONF_WATER_SENSOR): binary_sensor.binary_sensor_schema(LevoitBinarySensor),
      
    })
)


async def to_code(config):
    
    parent = await cg.get_variable(config[CONF_LEVOIT_ID])

    if tank_sensor := config.get(CONF_TANK_SENSOR):
        var = await binary_sensor.new_binary_sensor(tank_sensor, parent, LevoitBinarySensorPurpose.TANK_SENSOR)
        await cg.register_component(var, tank_sensor)

    if water_sensor := config.get(CONF_WATER_SENSOR):
        var = await binary_sensor.new_binary_sensor(water_sensor, parent, LevoitBinarySensorPurpose.WATER_SENSOR)
        await cg.register_component(var, water_sensor)
