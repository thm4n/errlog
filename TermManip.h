#ifndef _DEFS_H_
#define _DEFS_H_

#define HIDE_CURSOR  (printf("\x1b[?25l"))
#define SHOW_CURSOR  (printf("\x1b[?25h"))

#define RETURN_HOME  (printf("\033[0;0H"))
#define ColorReset   (printf("\033[0m"))

#define Black  30
#define Red    31
#define Green  32
#define Yellow 33
#define Blue   34
#define Purple 35
#define Cyan   36
#define White  37

#define FG 0
#define BG 1

#define _ATTR_REG        0
#define _ATTR_LIGHT      1
#define _ATTR_DIM        2
#define _ATTR_UNDERSCORE 4
#define _ATTR_BLINK      5
#define _ATTR_REVERSE    7
#define _ATTR_HIDDEN     8

const char* _setColor(int ground, int attrib, int color);

#define setColor(color) (_setColor(FG, _ATTR_REG, color))
#define setLightColor(color) (_setColor(FG, _ATTR_LIGHT, color))

#define dropline(index)    (index + DEF_TERM_WIDTH)
#define lineReturn(index)  (index % DEF_TERM_WIDTH)
#define lineDropRet(index) (dropline(lineReturn(index)))

#endif