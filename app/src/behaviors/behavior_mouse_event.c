#define DT_DRV_COMPAT zmk_behavior_mouse_event

#include <device.h>
#include <drivers/behavior.h>
#include <logging/log.h>

#include <zmk/behavior.h>
#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static int behavior_mouse_event_init(const struct device *dev) { return 0; };

static int on_keymap_binding_pressed_1(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
  LOG_DBG("position %d keycode 0x%02X", event.position, binding->param1);
  LOG_DBG("IF THIS APPERAS IN LOGS I WILL CONSIDER IT A SUCCESS");
  return ZMK_EVENT_RAISE(zmk_keycode_state_changed_from_encoded(
      binding->param1, true, event.timestamp));
}

static int on_keymap_binding_released_1(struct zmk_behavior_binding *binding,
                                      struct zmk_behavior_binding_event event) {
  LOG_DBG("position %d keycode 0x%02X", event.position, binding->param1);
  LOG_DBG("IF THIS APPERAS IN LOGS I WILL CONSIDER IT A SUCCESS");
  return ZMK_EVENT_RAISE(zmk_keycode_state_changed_from_encoded(
      binding->param1, false, event.timestamp));
}

static int
on_mouse_event_binding_convert_central_state_dependent_params(struct zmk_behavior_binding *binding,
                                                         struct zmk_behavior_binding_event event) {
    const struct device *ext_power = device_get_binding("MOUSE_EVENT");
    if (ext_power == NULL) {
        LOG_ERR("Unable to retrieve ext_power device: %d", binding->param1);
        return -EIO;
    }
    /* if (binding->param1 == EXT_POWER_TOGGLE_CMD) { */
    /*     binding->param1 = ext_power_get(ext_power) > 0 ? EXT_POWER_OFF_CMD : EXT_POWER_ON_CMD; */
    /* } */

    return 0;
}


static const struct behavior_driver_api behavior_mouse_event_driver_api = {
    .binding_convert_central_state_dependent_params = on_mouse_event_binding_convert_central_state_dependent_params,
    .binding_pressed = on_keymap_binding_pressed_1,
    .binding_released = on_keymap_binding_released_1};

#define ME_INST(n)                                                             \
  DEVICE_AND_API_INIT(behavior_mouse_event_##n, DT_INST_LABEL(n),              \
                      behavior_mouse_event_init, NULL, NULL, APPLICATION,      \
                      CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,                     \
                      &behavior_mouse_event_driver_api);

DT_INST_FOREACH_STATUS_OKAY(ME_INST)
