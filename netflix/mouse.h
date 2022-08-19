#pragma once

typedef int(*pDD_btn)(int btn);
typedef int(*pDD_movR)(int dx, int dy);
typedef int(*pDD_mov)(int dx, int dy);

inline pDD_btn mouse_button;
inline pDD_movR mouse_move_rel;
inline pDD_mov mouse_move_abs;