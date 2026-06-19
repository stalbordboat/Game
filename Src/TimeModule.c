// MIT LICENSE - Copyright (c) Ralph Desir 2025
// Description: Time Retrieval Methods
#include "Internal.h"

PRIVATE mrb_sym sym_year        = 0;
PRIVATE mrb_sym sym_month       = 0;
PRIVATE mrb_sym sym_day         = 0;
PRIVATE mrb_sym sym_hour        = 0;
PRIVATE mrb_sym sym_minute      = 0;
PRIVATE mrb_sym sym_second      = 0;
PRIVATE mrb_sym sym_nanosecond  = 0;
PRIVATE mrb_sym sym_day_of_week = 0;
PRIVATE mrb_sym sym_utc_offset  = 0;

PRIVATE SDL_INLINE
void InitDateTimeSymbols(mrb_state *mrb) {
    sym_year        = mrb_intern_lit(mrb, "year");
    sym_month       = mrb_intern_lit(mrb, "month");
    sym_day         = mrb_intern_lit(mrb, "day");
    sym_hour        = mrb_intern_lit(mrb, "hour");
    sym_minute      = mrb_intern_lit(mrb, "minute");
    sym_second      = mrb_intern_lit(mrb, "second");
    sym_nanosecond  = mrb_intern_lit(mrb, "nanosecond");
    sym_day_of_week = mrb_intern_lit(mrb, "day_of_week");
    sym_utc_offset  = mrb_intern_lit(mrb, "utc_offset");
}

PRIVATE SDL_INLINE
bool GetDateTime(SDL_DateTime *date_time, SDL_Time time, bool use_local) {
    SDL_Time ticks   = 0;
    bool     status  = false;
    bool     no_time = (time < 0);

    if(no_time) {
        status = SDL_GetCurrentTime(&ticks);
        if(!status) {
            return false;
        }
    }
    else {
        ticks = time;
    }

    status = SDL_TimeToDateTime(ticks, date_time, use_local);
    if(!status) {
        return false;
    }

    return true;
}

PRIVATE
mrb_value self_now(mrb_state *mrb, mrb_value self) {
    SDL_DateTime date_time = {0};
    bool         status    = false;
    mrb_int      time      = -1;
    mrb_bool     use_local = true;
    mrb_value    hash      = {0};
    mrb_value    key       = {0};
    mrb_value    val       = {0};

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "|ib", &time, &use_local);

    status = GetDateTime(&date_time, time, use_local);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    hash = mrb_hash_new_capa(mrb, 9);

    key = mrb_symbol_value(sym_year);
    val = mrb_int_value(mrb, date_time.year);
    mrb_hash_set(mrb, hash, key, val);

    key = mrb_symbol_value(sym_month);
    val = mrb_int_value(mrb, date_time.month);
    mrb_hash_set(mrb, hash, key, val);

    key = mrb_symbol_value(sym_day);
    val = mrb_int_value(mrb, date_time.day);
    mrb_hash_set(mrb, hash, key, val);

    key = mrb_symbol_value(sym_hour);
    val = mrb_int_value(mrb, date_time.hour);
    mrb_hash_set(mrb, hash, key, val);

    key = mrb_symbol_value(sym_minute);
    val = mrb_int_value(mrb, date_time.minute);
    mrb_hash_set(mrb, hash, key, val);

    key = mrb_symbol_value(sym_second);
    val = mrb_int_value(mrb, date_time.second);
    mrb_hash_set(mrb, hash, key, val);

    key = mrb_symbol_value(sym_nanosecond);
    val = mrb_int_value(mrb, date_time.nanosecond);
    mrb_hash_set(mrb, hash, key, val);

    key = mrb_symbol_value(sym_day_of_week);
    val = mrb_int_value(mrb, date_time.day_of_week);
    mrb_hash_set(mrb, hash, key, val);

    key = mrb_symbol_value(sym_utc_offset);
    val = mrb_int_value(mrb, date_time.utc_offset);
    mrb_hash_set(mrb, hash, key, val);

    return hash;
}

PRIVATE
mrb_value self_date_format(mrb_state *mrb, mrb_value self) {
    bool           status = false;
    SDL_DateFormat format = 0;

    UNUSED_ARGUMENT self;

    status = SDL_GetDateTimeLocalePreferences(&format, NULL);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, format);
}

PRIVATE
mrb_value self_time_format(mrb_state *mrb, mrb_value self) {
    bool           status = false;
    SDL_TimeFormat format = 0;

    UNUSED_ARGUMENT self;

    status = SDL_GetDateTimeLocalePreferences(NULL, &format);
    if(!status) {
        RaiseRuntimeError(mrb);
    }

    return mrb_int_value(mrb, format);
}

PRIVATE
mrb_value self_to_seconds(mrb_state *mrb, mrb_value self) {
    mrb_int ns = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "i", &ns);

    return mrb_int_value(mrb, SDL_NS_TO_SECONDS(ns));
}

PRIVATE
mrb_value self_to_nanoseconds(mrb_state *mrb, mrb_value self) {
    mrb_int s = 0;

    UNUSED_ARGUMENT self;

    IGNORE_RETURN mrb_get_args(mrb, "i", &s);

    return mrb_int_value(mrb, SDL_SECONDS_TO_NS(s));
}

PUBLIC
void DefineTimeModule(mrb_state *mrb) {
    struct RClass *time = NULL;

    InitDateTimeSymbols(mrb);

    SAVE_ARENA(mrb);

    time = mrb_define_module(mrb, "Time");

    mrb_define_const(mrb, time, "MAX",                  mrb_int_value(mrb, SDL_MAX_TIME));
    mrb_define_const(mrb, time, "MIN",                  mrb_int_value(mrb, SDL_MIN_TIME));
    mrb_define_const(mrb, time, "DATE_FORMAT_YYYYMMDD", mrb_int_value(mrb, SDL_DATE_FORMAT_YYYYMMDD));
    mrb_define_const(mrb, time, "DATE_FORMAT_DDMMYYYY", mrb_int_value(mrb, SDL_DATE_FORMAT_DDMMYYYY));
    mrb_define_const(mrb, time, "DATE_FORMAT_MMDDYYYY", mrb_int_value(mrb, SDL_DATE_FORMAT_MMDDYYYY));
    mrb_define_const(mrb, time, "FORMAT_24HR",          mrb_int_value(mrb, SDL_TIME_FORMAT_24HR));
    mrb_define_const(mrb, time, "FORMAT_12HR",          mrb_int_value(mrb, SDL_TIME_FORMAT_12HR));

    mrb_define_module_function(mrb, time, "now",            self_now,            MRB_ARGS_OPT(2));
    mrb_define_module_function(mrb, time, "date_format",    self_date_format,    MRB_ARGS_NONE());
    mrb_define_module_function(mrb, time, "format",         self_time_format,    MRB_ARGS_NONE());
    mrb_define_module_function(mrb, time, "to_seconds",     self_to_seconds,     MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, time, "to_nanoseconds", self_to_nanoseconds, MRB_ARGS_REQ(1));

    RESTORE_ARENA(mrb);
}
