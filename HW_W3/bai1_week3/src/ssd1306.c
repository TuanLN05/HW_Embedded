/* src/ssd1306.c */
#include <string.h>
#include "ssd1306.h"
#include "i2c.h"

static uint8_t fb[128 * 8];   /* 128 cột x 8 page = 1024 byte */

static void cmd(uint8_t c)
{
    uint8_t b[2] = { 0x00, c };   /* 0x00 = control byte: lệnh */
    i2c1_write(SSD1306_ADDR, b, 2);
}

void ssd1306_init(void)
{
    static const uint8_t seq[] = {
        0xAE,             /* tắt màn hình */
        0xD5, 0x80,       /* clock */
        0xA8, 0x3F,       /* multiplex 64 */
        0xD3, 0x00,       /* display offset */
        0x40,             /* start line 0 */
        0x8D, 0x14,       /* bật charge pump */
        0x20, 0x02,       /* page addressing mode */
        0xA1,             /* đảo cột (nếu ảnh bị ngược trái/phải: 0xA0) */
        0xC8,             /* đảo hàng (nếu bị ngược trên/dưới: 0xC0) */
        0xDA, 0x12,       /* COM pins */
        0x81, 0xCF,       /* độ tương phản */
        0xD9, 0xF1,
        0xDB, 0x40,
        0xA4,             /* hiển thị theo RAM */
        0xA6,             /* không đảo màu */
        0xAF              /* bật màn hình */
    };
    for (volatile uint32_t i = 0; i < 200000; i++);   /* chờ OLED lên nguồn */
    for (uint32_t i = 0; i < sizeof(seq); i++) cmd(seq[i]);
}

void ssd1306_clear(void)
{
    memset(fb, 0, sizeof(fb));
}

void ssd1306_pixel(int x, int y, int on)
{
    if (x < 0 || x >= 128 || y < 0 || y >= 64) return;
    if (on) fb[x + (y / 8) * 128] |=  (1u << (y % 8));
    else    fb[x + (y / 8) * 128] &= ~(1u << (y % 8));
}

void ssd1306_draw_bitmap(const uint8_t *bmp)
{
    memcpy(fb, bmp, sizeof(fb));
}

void ssd1306_update(void)
{
    uint8_t buf[129];
    buf[0] = 0x40;                       /* control byte: dữ liệu */
    for (uint8_t p = 0; p < 8; p++) {
        cmd(0xB0 | p);                                   /* chọn page */
        cmd(0x00 | (SSD1306_COL_OFFSET & 0x0F));         /* cột thấp */
        cmd(0x10 | (SSD1306_COL_OFFSET >> 4));           /* cột cao */
        memcpy(&buf[1], &fb[p * 128], 128);
        i2c1_write(SSD1306_ADDR, buf, 129);
    }
}
