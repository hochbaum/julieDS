#ifndef JULIEDS_LCD_H
#define JULIEDS_LCD_H

#include "nds.h"

#include <raylib.h>

void lcd_draw_pixel(struct nds_system *nds, short x, short y, struct lcd_color pixel);

struct lcd_color lcd_get_pixel(struct nds_system *nds, int x, int y);

Color lcd_color_to_raylib_color(struct lcd_color lcd_color);

#endif //JULIEDS_LCD_H