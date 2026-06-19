// MIT LICENSE - Copyright (c) Ralph Desir 2026
// Description: Represents Gamepad Devices
#include "Internal.h"

PRIVATE
mrb_value self_ids(mrb_state *mrb, mrb_value self) {
    SDL_JoystickID *ids    = NULL;
    int             count  = 0;
    mrb_value       ary    = {0};
    bool            status = false;

    UNUSED_ARGUMENT self;

    ids = SDL_GetJoysticks(&count);
    if(!ids) {
        RaiseRuntimeError(mrb);
    }

    ary = mrb_ary_new_capa(mrb, count);

    for(int i = 0;i < count;++i) {
        status = SDL_IsGamepad(ids[i]);
        if(status) {
            mrb_ary_push(mrb, ary, mrb_int_value(mrb, ids[i]));
        }
    }

    FreeBuffer(ids);

    return ary;
}

PRIVATE
mrb_value self_name(mrb_state *mrb, mrb_value self) {
    mrb_int id = 0;

    IGNORE_RETURN mrb_get_args(mrb, "i", &id);

    UNUSED_ARGUMENT self;

    return mrb_str_new_cstr(mrb, SDL_GetGamepadNameForID(id));
}

PRIVATE
mrb_value self_add_mapping(mrb_state *mrb, mrb_value self) {
    const char *in_mapping = NULL;
    mrb_value   ex_mapping = {0};
    int         status     = 0;
    mrb_sym     sym        = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_mapping);

    in_mapping = mrb_str_to_cstr(mrb, ex_mapping);

    status = SDL_AddGamepadMapping(in_mapping);
    if(status == -1) {
        RaiseRuntimeError(mrb);
    }

    switch(status) {
        case 0:
            sym = mrb_intern_lit(mrb, "updated");
            break;
        case 1:
            sym = mrb_intern_lit(mrb, "added");
            break;
    }

    return mrb_symbol_value(sym);
}

PRIVATE
mrb_value self_reload_mappings(mrb_state *mrb, mrb_value self) {
    bool status = false;

    UNUSED_ARGUMENT self;

    status = SDL_ReloadGamepadMappings();
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value self_open(mrb_state *mrb, mrb_value self) {
    struct RClass *gamepad = NULL;
    mrb_value      argv[1] = {0};
    mrb_int        which   = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "i", &which);

    gamepad = mrb_class_get(mrb, "Gamepad");
    argv[0] = mrb_int_value(mrb, which);

    return mrb_obj_new(mrb, gamepad, 1, argv);
}

PRIVATE
mrb_value initialize(mrb_state *mrb, mrb_value self) {
    SDL_Gamepad *gamepad = NULL;
    mrb_int      which   = 0;
    mrb_sym      sym     = 0;
    mrb_value    val     = {0};

    IGNORE_RETURN mrb_get_args(mrb, "i", &which);

    gamepad = SDL_OpenGamepad(which);
    if(!gamepad) {
        RaiseRuntimeError(mrb);
    }

    sym = mrb_intern_lit(mrb, "@is_closed");
    val = mrb_false_value();
    mrb_iv_set(mrb, self, sym, val);

    sym = mrb_intern_lit(mrb, "@id");
    val = mrb_int_value(mrb, which);
    mrb_iv_set(mrb, self, sym, val);

    DATA_PTR(self) = gamepad;

    return self;
}

PRIVATE
mrb_value initialize_copy(mrb_state *mrb, mrb_value copy) {
    UNUSED_ARGUMENT mrb;
    UNUSED_ARGUMENT copy;

    IGNORE_RETURN SDL_SetError("Gamepad cannot be copied");
    RaiseRuntimeError(mrb);

    return copy;
}

PRIVATE
mrb_value close(mrb_state *mrb, mrb_value self) {
    SDL_Gamepad *gamepad = DATA_PTR(self);
    mrb_sym      sym     = 0;
    mrb_value    val     = {0};

    UNUSED_ARGUMENT mrb;
    UNUSED_ARGUMENT self;

    SDL_CloseGamepad(gamepad);
    DATA_PTR(self) = NULL;

    sym = mrb_intern_lit(mrb, "@is_closed");
    val = mrb_true_value();
    mrb_iv_set(mrb, self, sym, val);

    return mrb_nil_value();
}

PRIVATE
mrb_value is_closed(mrb_state *mrb, mrb_value self) {
    return mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@is_closed"));
}

PUBLIC
mrb_value name(mrb_state *mrb, mrb_value self) {
    SDL_Gamepad *gamepad = DATA_PTR(self);

    return mrb_str_new_cstr(mrb, SDL_GetGamepadName(gamepad));
}

PRIVATE
mrb_value has_rumble(mrb_state *mrb, mrb_value self) {
    SDL_Gamepad     *gamepad = DATA_PTR(self);
    mrb_bool         status  = FALSE;
    SDL_PropertiesID id      = 0;

    UNUSED_ARGUMENT self;

    id = SDL_GetGamepadProperties(gamepad);
    if(id == 0) {
        RaiseRuntimeError(mrb);
    }

    status = SDL_GetBooleanProperty(id, SDL_PROP_GAMEPAD_CAP_RUMBLE_BOOLEAN, false);

    return mrb_bool_value(status);
}

PRIVATE
mrb_value rumble(mrb_state *mrb, mrb_value self) {
    SDL_Gamepad *gamepad   = DATA_PTR(self);
    mrb_int      low_freq  = 0;
    mrb_int      high_freq = 0;
    mrb_int      duration  = 0;
    mrb_int      status    = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "iii", &low_freq, &high_freq, &duration);

    status = SDL_RumbleGamepad(gamepad, low_freq, high_freq, duration);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value has_rumble_triggers(mrb_state *mrb, mrb_value self) {
    SDL_Gamepad     *gamepad = DATA_PTR(self);
    mrb_bool         status  = FALSE;
    SDL_PropertiesID id      = 0;

    UNUSED_ARGUMENT self;

    id = SDL_GetGamepadProperties(gamepad);
    if(id == 0) {
        RaiseRuntimeError(mrb);
    }

    status = SDL_GetBooleanProperty(id, SDL_PROP_GAMEPAD_CAP_TRIGGER_RUMBLE_BOOLEAN, false);

    return mrb_bool_value(status);
}

PRIVATE
mrb_value rumble_triggers(mrb_state *mrb, mrb_value self) {
    SDL_Gamepad *gamepad  = DATA_PTR(self);
    mrb_int      left     = 0;
    mrb_int      right    = 0;
    mrb_int      duration = 0;
    mrb_int      status   = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "iii", &left, &right, &duration);

    status = SDL_RumbleGamepadTriggers(gamepad, left, right, duration);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value has_led(mrb_state *mrb, mrb_value self) {
    SDL_Gamepad     *gamepad = DATA_PTR(self);
    mrb_bool         status  = FALSE;
    SDL_PropertiesID id      = 0;

    UNUSED_ARGUMENT self;

    id = SDL_GetGamepadProperties(gamepad);
    if(id == 0) {
        RaiseRuntimeError(mrb);
    }

    status = SDL_GetBooleanProperty(id, SDL_PROP_GAMEPAD_CAP_PLAYER_LED_BOOLEAN, false);

    return mrb_bool_value(status);
}

PRIVATE
mrb_value led(mrb_state *mrb, mrb_value self) {
    SDL_Gamepad *gamepad = DATA_PTR(self);
    mrb_int      r       = 0;
    mrb_int      g       = 0;
    mrb_int      b       = 0;
    mrb_int      status  = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "iii", &r, &g, &b);

    status = SDL_SetGamepadLED(gamepad, r, g, b);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_nil_value();
}

PRIVATE
mrb_value power_state(mrb_state *mrb, mrb_value self) {
    SDL_Gamepad *gamepad = DATA_PTR(self);

    return mrb_int_value(mrb, SDL_GetGamepadPowerInfo(gamepad, NULL));
}

PRIVATE
mrb_value percent(mrb_state *mrb, mrb_value self) {
    SDL_Gamepad *gamepad = DATA_PTR(self);
    int          count   = 0;

    SDL_GetGamepadPowerInfo(gamepad, &count);

    return mrb_int_value(mrb, count);
}

PRIVATE
mrb_value is_connected(mrb_state *mrb, mrb_value self) {
    SDL_Gamepad *gamepad = DATA_PTR(self);

    UNUSED_ARGUMENT mrb;

    return mrb_bool_value(SDL_GamepadConnected(gamepad));
}

PRIVATE
mrb_value connection_state(mrb_state *mrb, mrb_value self) {
    SDL_Gamepad                 *gamepad = DATA_PTR(self);
    SDL_JoystickConnectionState  state   = SDL_JOYSTICK_CONNECTION_UNKNOWN;

    UNUSED_ARGUMENT self;

    state = SDL_GetGamepadConnectionState(gamepad);
    if(state == SDL_JOYSTICK_CONNECTION_INVALID) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, state);
}

PRIVATE
mrb_value get_mapping(mrb_state *mrb, mrb_value self) {
    SDL_Gamepad *gamepad    = DATA_PTR(self);
    char        *in_mapping = NULL;
    mrb_value    ex_mapping = {0};

    in_mapping = SDL_GetGamepadMapping(gamepad);
    ex_mapping = mrb_str_new_cstr     (mrb, in_mapping);

    FreeBuffer(in_mapping);

    return ex_mapping;
}

PRIVATE
mrb_value set_mapping(mrb_state *mrb, mrb_value self) {
    char          *in_mapping = NULL;
    mrb_value      ex_mapping = {0};
    mrb_sym        sym        = 0;
    mrb_value      val        = {0};
    SDL_JoystickID id         = 0;
    bool           status     = false;

    IGNORE_RETURN mrb_get_args(mrb, "S", &ex_mapping);

    sym = mrb_intern_lit(mrb, "@id");
    val = mrb_iv_get(mrb, self, sym);
    id  = mrb_int(mrb, val);

    in_mapping = mrb_str_to_cstr      (mrb, ex_mapping);
    status     = SDL_SetGamepadMapping(id, in_mapping);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return ex_mapping;
}

PRIVATE
mrb_value guid(mrb_state *mrb, mrb_value self) {
    mrb_sym        sym     = 0;
    mrb_value      val     = {0};
    SDL_JoystickID id      = 0;
    SDL_GUID       guid    = {0};
    char           str[33] = {0};

    sym  = mrb_intern_lit(mrb, "@id");
    val  = mrb_iv_get(mrb, self, sym);
    id   = mrb_int(mrb, val);
    guid = SDL_GetGamepadGUIDForID(id);
    SDL_GUIDToString(guid, str, sizeof(str));

    return mrb_str_new_cstr(mrb, str);
}

PUBLIC
void DefineGamepadClass(mrb_state *mrb) {
    struct RClass *gamepad = NULL;

    SAVE_ARENA(mrb);

    gamepad = mrb_define_class(mrb, "Gamepad", mrb->object_class);

    mrb_define_const(mrb, gamepad, "RUMBLE_MAX",            mrb_int_value(mrb, 65535));
    mrb_define_const(mrb, gamepad, "RUMBLE_MIN",            mrb_int_value(mrb, 0));
    mrb_define_const(mrb, gamepad, "POWERSTATE_UNKNOWN",    mrb_int_value(mrb, SDL_POWERSTATE_UNKNOWN));
    mrb_define_const(mrb, gamepad, "POWERSTATE_ON_BATTERY", mrb_int_value(mrb, SDL_POWERSTATE_ON_BATTERY));
    mrb_define_const(mrb, gamepad, "POWERSTATE_NO_BATTERY", mrb_int_value(mrb, SDL_POWERSTATE_NO_BATTERY));
    mrb_define_const(mrb, gamepad, "POWERSTATE_CHARGING",   mrb_int_value(mrb, SDL_POWERSTATE_CHARGING));
    mrb_define_const(mrb, gamepad, "POWERSTATE_CHARGED",    mrb_int_value(mrb, SDL_POWERSTATE_CHARGED));
    mrb_define_const(mrb, gamepad, "CONNECTION_UNKNOWN",    mrb_int_value(mrb, SDL_JOYSTICK_CONNECTION_UNKNOWN));
    mrb_define_const(mrb, gamepad, "CONNECTION_WIRED",      mrb_int_value(mrb, SDL_JOYSTICK_CONNECTION_WIRED));
    mrb_define_const(mrb, gamepad, "CONNECTION_WIRELESS",   mrb_int_value(mrb, SDL_JOYSTICK_CONNECTION_WIRELESS));

    mrb_define_class_method(mrb, gamepad, "ids",             self_ids,             MRB_ARGS_NONE());
    mrb_define_class_method(mrb, gamepad, "name",            self_name,            MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, gamepad, "add_mapping",     self_add_mapping,     MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, gamepad, "reload_mappings", self_reload_mappings, MRB_ARGS_NONE());
    mrb_define_class_method(mrb, gamepad, "open",            self_open,            MRB_ARGS_REQ(1));

    mrb_define_method(mrb, gamepad, "initialize",       initialize,          MRB_ARGS_REQ(1));
    mrb_define_method(mrb, gamepad, "initialize_copy",  initialize_copy,     MRB_ARGS_REQ(1));
    mrb_define_method(mrb, gamepad, "close",            close,               MRB_ARGS_NONE());
    mrb_define_method(mrb, gamepad, "closed?",          is_closed,           MRB_ARGS_NONE());
    mrb_define_method(mrb, gamepad, "name",             name,                MRB_ARGS_NONE());
    mrb_define_method(mrb, gamepad, "rumble?",          has_rumble,          MRB_ARGS_NONE());
    mrb_define_method(mrb, gamepad, "rumble",           rumble,              MRB_ARGS_REQ(3));
    mrb_define_method(mrb, gamepad, "rumble_triggers?", has_rumble_triggers, MRB_ARGS_NONE());
    mrb_define_method(mrb, gamepad, "rumble_triggers",  rumble_triggers,     MRB_ARGS_REQ(3));
    mrb_define_method(mrb, gamepad, "led?",             has_led,             MRB_ARGS_NONE());
    mrb_define_method(mrb, gamepad, "led",              led,                 MRB_ARGS_REQ(3));
    mrb_define_method(mrb, gamepad, "power_state",      power_state,         MRB_ARGS_NONE());
    mrb_define_method(mrb, gamepad, "percent",          percent,             MRB_ARGS_NONE());
    mrb_define_method(mrb, gamepad, "connected?",       is_connected,        MRB_ARGS_NONE());
    mrb_define_method(mrb, gamepad, "connection_state", connection_state,    MRB_ARGS_NONE());
    mrb_define_method(mrb, gamepad, "mapping",          get_mapping,         MRB_ARGS_NONE());
    mrb_define_method(mrb, gamepad, "mapping=",         set_mapping,         MRB_ARGS_REQ(1));
    mrb_define_method(mrb, gamepad, "guid",             guid,                MRB_ARGS_NONE());

    RESTORE_ARENA(mrb);
}
