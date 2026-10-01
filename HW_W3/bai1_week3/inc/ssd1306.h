/* inc/ssd1306.h */
#ifndef SSD1306_H
#define SSD1306_H
#include <stdint.h>

#define SSD1306_ADDR        0x3C   /* một số module dùng 0x3D */
#define SSD1306_COL_OFFSET  2      /* SH1106 thì đặt 2 */

void ssd1306_init(void);
void ssd1306_clear(void);
void ssd1306_pixel(int x, int y, int on);
void ssd1306_draw_bitmap(const uint8_t *bmp);  /* 1024 byte, dạng page */
void ssd1306_update(void);
#endif
