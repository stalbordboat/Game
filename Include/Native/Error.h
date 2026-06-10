// MIT LICENSE - Copyright (c) Ralph Desir 2025
#ifndef EXERROR_H
#define EXERROR_H

#include "Common.h"

#define GAME_EXIT_SUCCESS 0
#define GAME_EXIT_FAILURE 1

PRIVATE SDL_INLINE
void RaiseError(mrb_state *mrb, struct RClass *c, const char *msg) {
    mrb_raisef(mrb, c, "%s: %s", msg, SDL_GetError());
}

PRIVATE SDL_INLINE
void RaiseStandardError(mrb_state *mrb) {
    RaiseError(mrb, E_STANDARD_ERROR, "Standard Error");
}

PRIVATE SDL_INLINE
void RaiseRuntimeError(mrb_state *mrb) {
    RaiseError(mrb, E_RUNTIME_ERROR, "Runtime Error");
}

PRIVATE SDL_INLINE
void RaiseTypeError(mrb_state *mrb) {
    RaiseError(mrb, E_TYPE_ERROR, "Type Error");
}

PRIVATE SDL_INLINE
void RaiseZeroDivisionError(mrb_state *mrb) {
    RaiseError(mrb, E_ZERODIV_ERROR, "Zero Division Error");
}

PRIVATE SDL_INLINE
void RaiseArgumentError(mrb_state *mrb) {
    RaiseError(mrb, E_ARGUMENT_ERROR, "Argument Error");
}

PRIVATE SDL_INLINE
void RaiseIndexError(mrb_state *mrb) {
    RaiseError(mrb, E_INDEX_ERROR, "Index Error");
}

PRIVATE SDL_INLINE
void RaiseRangeError(mrb_state *mrb) {
    RaiseError(mrb, E_RANGE_ERROR, "Range Error");
}

PRIVATE SDL_INLINE
void RaiseNameError(mrb_state *mrb) {
    RaiseError(mrb, E_NAME_ERROR, "Name Error");
}

PRIVATE SDL_INLINE
void RaiseNoMethodError(mrb_state *mrb) {
    RaiseError(mrb, E_NOMETHOD_ERROR, "No Method Error");
}

PRIVATE SDL_INLINE
void RaiseScriptError(mrb_state *mrb) {
    RaiseError(mrb, E_SCRIPT_ERROR, "Script Error");
}

PRIVATE SDL_INLINE
void RaiseSyntaxError(mrb_state *mrb) {
    RaiseError(mrb, E_SYNTAX_ERROR, "Syntax Error");
}

PRIVATE SDL_INLINE
void RaiseLocalJumpError(mrb_state *mrb) {
    RaiseError(mrb, E_LOCALJUMP_ERROR, "Local Jump Error");
}

PRIVATE SDL_INLINE
void RaiseRegExError(mrb_state *mrb) {
    RaiseError(mrb, E_REGEXP_ERROR, "RegEx Error");
}

PRIVATE SDL_INLINE
void RaiseFrozenError(mrb_state *mrb) {
    RaiseError(mrb, E_FROZEN_ERROR, "Frozen Error");
}

PRIVATE SDL_INLINE
void RaiseNoTimpError(mrb_state *mrb) {
    RaiseError(mrb, E_NOTIMP_ERROR, "No Timp Error");
}

PRIVATE SDL_INLINE
void RaiseKeyError(mrb_state *mrb) {
    RaiseError(mrb, E_KEY_ERROR, "Key Error");
}

PRIVATE SDL_INLINE
void RaiseFloatDomainError(mrb_state *mrb) {
    RaiseError(mrb, E_FLOATDOMAIN_ERROR, "Float Domain Error");
}

PRIVATE SDL_INLINE
void SetErrorMrbState(mrb_state *mrb) {
    mrb_sym    sym = 0;
    mrb_value  val = {0};
    char      *msg = NULL;

    SDL_assert(mrb->exc);

    val = mrb_obj_value(mrb->exc);
    sym = mrb_intern_lit(mrb, "to_s");
    val = mrb_funcall_argv(mrb, val, sym, 0, NULL);
    msg = mrb_str_to_cstr(mrb, val);

    IGNORE_RETURN SDL_SetError("%s", msg);
}

PRIVATE SDL_INLINE
void SetErrorPhysfs(void) {
    int         code = 0;
    const char *msg  = 0;

    code = PHYSFS_getLastErrorCode();
    msg  = PHYSFS_getErrorByCode(code);

    IGNORE_RETURN SDL_SetError("%s", msg);
}

#endif /*EXERROR_H*/
