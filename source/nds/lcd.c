#include "nds/lcd.h"
#include "nds/nds.h"

void lcd_draw_pixel(struct nds_system *nds, short x, short y, struct lcd_color pixel) {
     nds->vram.framebuf[y * NDS_SCREEN_WIDTH + x] = pixel;
}

inline struct lcd_color lcd_get_pixel(struct nds_system *nds, int x, int y) {
    return nds->vram.framebuf[y * NDS_SCREEN_WIDTH + x];
}

inline Color lcd_color_to_raylib_color(struct lcd_color lcd_color) {
    return (Color){ .a = 255, .r = lcd_color.r, .g = lcd_color.g, .b = lcd_color.b };
}