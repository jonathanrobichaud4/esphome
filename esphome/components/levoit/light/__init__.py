# import esphome.codegen as cg
# import esphome.config_validation as cv
# from esphome.components import light
# from esphome.const import (
#      ICON_LIGHTBULB,
#      CONF_OUTPUT_ID,
#      CONF_LIGHT,
#  )

# from .. import levoit_ns, CONF_LEVOIT_ID, Levoit

# DEPENDENCIES = ["levoit"]
# CODEOWNERS = ["@acvigue"]

# # CONF_LIGHT = "night_light"

# LevoitLight = levoit_ns.class_("LevoitLight", light.LightOutput, cg.Component)

# CONFIG_SCHEMA = light.BRIGHTNESS_ONLY_LIGHT_SCHEMA.extend(
#     {
#         cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(LevoitLight),
#         cv.GenerateID(CONF_LEVOIT_ID): cv.use_id(Levoit),
#     }
# ).extend(cv.COMPONENT_SCHEMA)


# async def to_code(config):
#     parent = await cg.get_variable(config[CONF_LEVOIT_ID]) 
#     var = cg.new_Pvariable(config[CONF_OUTPUT_ID], parent)
#     await cg.register_component(var, config)
#     await light.register_light(var, config)
    
#     print("Parent: ", parent)
#     print("Config: ", config)
#     print("Output ID: ", config[CONF_OUTPUT_ID])
    

#     #out = yield cg.get_variable(config[CONF_OUTPUT])
#     #cg.add(var.set_output(out))

#     # if config_light := config.get(CONF_LIGHT):
#     #     var = await light.new_light(config_light, parent, LevoitLightPurpose.NIGHT_LIGHT)
#     #     await cg.register_component(var, config_light)
