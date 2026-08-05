#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct { char c; unsigned char col[5]; } Glyph;

static const Glyph FONT[] = {
    {' ', {0x00,0x00,0x00,0x00,0x00}},
    {'.', {0x00,0x60,0x60,0x00,0x00}},
    {',', {0x00,0x50,0x30,0x00,0x00}},
    {'-', {0x08,0x08,0x08,0x08,0x08}},
    {'(', {0x00,0x1C,0x22,0x41,0x00}},
    {')', {0x00,0x41,0x22,0x1C,0x00}},
    {':', {0x00,0x36,0x36,0x00,0x00}},
    {'0', {0x3E,0x51,0x49,0x45,0x3E}},
    {'1', {0x00,0x42,0x7F,0x40,0x00}},
    {'2', {0x42,0x61,0x51,0x49,0x46}},
    {'3', {0x21,0x41,0x45,0x4B,0x31}},
    {'4', {0x18,0x14,0x12,0x7F,0x10}},
    {'5', {0x27,0x45,0x45,0x45,0x39}},
    {'6', {0x3C,0x4A,0x49,0x49,0x30}},
    {'7', {0x01,0x71,0x09,0x05,0x03}},
    {'8', {0x36,0x49,0x49,0x49,0x36}},
    {'9', {0x06,0x49,0x49,0x29,0x1E}},
    {'A', {0x7E,0x11,0x11,0x11,0x7E}},
    {'B', {0x7F,0x49,0x49,0x49,0x36}},
    {'C', {0x3E,0x41,0x41,0x41,0x22}},
    {'D', {0x7F,0x41,0x41,0x22,0x1C}},
    {'E', {0x7F,0x49,0x49,0x49,0x41}},
    {'F', {0x7F,0x09,0x09,0x09,0x01}},
    {'G', {0x3E,0x41,0x49,0x49,0x7A}},
    {'H', {0x7F,0x08,0x08,0x08,0x7F}},
    {'I', {0x00,0x41,0x7F,0x41,0x00}},
    {'J', {0x20,0x40,0x41,0x3F,0x01}},
    {'K', {0x7F,0x08,0x14,0x22,0x41}},
    {'L', {0x7F,0x40,0x40,0x40,0x40}},
    {'M', {0x7F,0x02,0x0C,0x02,0x7F}},
    {'N', {0x7F,0x04,0x08,0x10,0x7F}},
    {'O', {0x3E,0x41,0x41,0x41,0x3E}},
    {'P', {0x7F,0x09,0x09,0x09,0x06}},
    {'Q', {0x3E,0x41,0x51,0x21,0x5E}},
    {'R', {0x7F,0x09,0x19,0x29,0x46}},
    {'S', {0x46,0x49,0x49,0x49,0x31}},
    {'T', {0x01,0x01,0x7F,0x01,0x01}},
    {'U', {0x3F,0x40,0x40,0x40,0x3F}},
    {'V', {0x1F,0x20,0x40,0x20,0x1F}},
    {'W', {0x3F,0x40,0x38,0x40,0x3F}},
    {'X', {0x63,0x14,0x08,0x14,0x63}},
    {'Y', {0x07,0x08,0x70,0x08,0x07}},
    {'Z', {0x61,0x51,0x49,0x45,0x43}},
};
#define FONT_COUNT (sizeof(FONT)/sizeof(FONT[0]))

static const Glyph* find_glyph(char c) {
    if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';
    for (size_t i = 0; i < FONT_COUNT; i++) if (FONT[i].c == c) return &FONT[i];
    return &FONT[0];
}

static void put_block(SDL_Surface *surf, int x, int y, int scale, Uint32 color) {
    SDL_Rect r = { x, y, scale, scale };
    SDL_FillRect(surf, &r, color);
}

static void draw_text(SDL_Surface *surf, int x, int y, const char *text, int scale, Uint32 color) {
    int cx = x;
    for (const char *p = text; *p; p++) {
        const Glyph *g = find_glyph(*p);
        for (int col = 0; col < 5; col++) {
            unsigned char bits = g->col[col];
            for (int row = 0; row < 7; row++) {
                if (bits & (1 << row)) put_block(surf, cx + col * scale, y + row * scale, scale, color);
            }
        }
        cx += 6 * scale;
    }
}

static int text_width(const char *text, int scale) {
    return (int)strlen(text) * 6 * scale;
}

static void draw_line(SDL_Surface *surf, int x0, int y0, int x1, int y1, Uint32 color, int thickness) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    while (1) {
        SDL_Rect r = { x0 - thickness / 2, y0 - thickness / 2, thickness, thickness };
        SDL_FillRect(surf, &r, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

static void draw_rect_outline(SDL_Surface *surf, int x, int y, int w, int h, Uint32 color) {
    draw_line(surf, x, y, x + w, y, color, 1);
    draw_line(surf, x, y + h, x + w, y + h, color, 1);
    draw_line(surf, x, y, x, y + h, color, 1);
    draw_line(surf, x + w, y, x + w, y + h, color, 1);
}

#define MAX_POINTS 32
typedef struct {
    char method[16];
    char varying[8];
    int xval[MAX_POINTS];
    double t[MAX_POINTS];
    int count;
} Series;

#define MAX_SERIES 8
static Series all_series[MAX_SERIES];
static int series_count = 0;

static Series* find_or_create_series(const char *method, const char *varying) {
    for (int i = 0; i < series_count; i++) {
        if (strcmp(all_series[i].method, method) == 0 && strcmp(all_series[i].varying, varying) == 0)
            return &all_series[i];
    }
    if (series_count >= MAX_SERIES) { fprintf(stderr, "too many series\n"); exit(1); }
    Series *s = &all_series[series_count++];
    strncpy(s->method, method, sizeof(s->method) - 1);
    strncpy(s->varying, varying, sizeof(s->varying) - 1);
    s->count = 0;
    return s;
}

static void load_csv(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) { fprintf(stderr, "could not open %s\n", path); exit(1); }
    char line[256];
    if (!fgets(line, sizeof(line), f)) { fclose(f); return; }
    while (fgets(line, sizeof(line), f)) {
        char method[16], varying[8];
        int n, k;
        double t;
        if (sscanf(line, "%15[^,],%7[^,],%d,%d,%lf", method, varying, &n, &k, &t) == 5) {
            Series *s = find_or_create_series(method, varying);
            int xv = (strcmp(varying, "k") == 0) ? k : n;
            if (s->count < MAX_POINTS) { s->xval[s->count] = xv; s->t[s->count] = t; s->count++; }
        }
    }
    fclose(f);
}

static const char *METHODS[2] = { "Sequential", "Pairwise" };
static const char *METHOD_LABELS[2] = { "SEQUENTIAL (METHOD 1)", "PAIRWISE (METHOD 2)" };

static Uint32 method_color(SDL_PixelFormat *fmt, int idx) {
    Uint8 r[2] = {220, 40};
    Uint8 g[2] = {90, 150};
    Uint8 b[2] = {40, 220};
    return SDL_MapRGB(fmt, r[idx], g[idx], b[idx]);
}

static void draw_chart(SDL_Surface *surf, int x, int y, int w, int h, const char *varying, const char *title, const char *xlabel) {
    Uint32 black = SDL_MapRGB(surf->format, 0, 0, 0);
    Uint32 gray = SDL_MapRGB(surf->format, 210, 210, 210);
    Uint32 white = SDL_MapRGB(surf->format, 255, 255, 255);

    SDL_Rect bg = { x, y, w, h };
    SDL_FillRect(surf, &bg, white);

    int margin_left = 80, margin_bottom = 55, margin_top = 40, margin_right = 20;
    int plot_x = x + margin_left;
    int plot_y = y + margin_top;
    int plot_w = w - margin_left - margin_right;
    int plot_h = h - margin_top - margin_bottom;

    double max_x = 1, max_t = 1e-9;
    for (int i = 0; i < 2; i++) {
        Series *s = find_or_create_series(METHODS[i], varying);
        for (int p = 0; p < s->count; p++) {
            if (s->xval[p] > max_x) max_x = s->xval[p];
            if (s->t[p] > max_t) max_t = s->t[p];
        }
    }

    for (int gline = 0; gline <= 4; gline++) {
        int gy = plot_y + plot_h - gline * plot_h / 4;
        draw_line(surf, plot_x, gy, plot_x + plot_w, gy, gray, 1);
    }
    draw_rect_outline(surf, plot_x, plot_y, plot_w, plot_h, black);

    for (int i = 0; i < 2; i++) {
        Series *s = find_or_create_series(METHODS[i], varying);
        Uint32 color = method_color(surf->format, i);
        int prev_px = 0, prev_py = 0, has_prev = 0;
        for (int p = 0; p < s->count; p++) {
            int px = plot_x + (int)(s->xval[p] / max_x * plot_w);
            int py = plot_y + plot_h - (int)(s->t[p] / max_t * plot_h);
            if (has_prev) draw_line(surf, prev_px, prev_py, px, py, color, 2);
            SDL_Rect dot = { px - 3, py - 3, 6, 6 };
            SDL_FillRect(surf, &dot, color);
            prev_px = px; prev_py = py; has_prev = 1;
        }
    }

    draw_text(surf, x + 10, y + 8, title, 2, black);

    char buf[32];
    snprintf(buf, sizeof(buf), "%.5f", max_t);
    draw_text(surf, x + 4, plot_y - 4, buf, 1, black);

    snprintf(buf, sizeof(buf), "%s=%d", xlabel, (int)max_x);
    draw_text(surf, plot_x + plot_w - text_width(buf, 1), plot_y + plot_h + 8, buf, 1, black);
}

int main(int argc, char **argv) {
    const char *csv_path = (argc > 1) ? argv[1] : "results_q3.csv";
    load_csv(csv_path);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    int chart_w = 620, chart_h = 380;
    int img_w = chart_w * 2 + 30;
    int img_h = chart_h + 90;

    SDL_Surface *surf = SDL_CreateRGBSurface(0, img_w, img_h, 32,
        0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    if (!surf) { fprintf(stderr, "SDL_CreateRGBSurface failed: %s\n", SDL_GetError()); return 1; }

    Uint32 white = SDL_MapRGB(surf->format, 255, 255, 255);
    Uint32 black = SDL_MapRGB(surf->format, 0, 0, 0);
    SDL_FillRect(surf, NULL, white);

    draw_chart(surf, 10, 10, chart_w - 10, chart_h, "k", "TIME VS K (N FIXED)", "K");
    draw_chart(surf, 10 + chart_w, 10, chart_w - 10, chart_h, "n", "TIME VS N (K FIXED)", "N");

    int lx = 20, ly = chart_h + 30;
    for (int i = 0; i < 2; i++) {
        Uint32 color = method_color(surf->format, i);
        SDL_Rect swatch = { lx, ly + 2, 18, 14 };
        SDL_FillRect(surf, &swatch, color);
        lx += 24;
        draw_text(surf, lx, ly, METHOD_LABELS[i], 2, black);
        lx += text_width(METHOD_LABELS[i], 2) + 50;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        fprintf(stderr, "IMG_Init failed: %s\n", IMG_GetError());
    }
    const char *out_path = "mergek_growth_sdl.png";
    if (IMG_SavePNG(surf, out_path) != 0) {
        fprintf(stderr, "IMG_SavePNG failed: %s\n", IMG_GetError());
        SDL_SaveBMP(surf, "mergek_growth_sdl.bmp");
        printf("Saved mergek_growth_sdl.bmp\n");
    } else {
        printf("Saved %s\n", out_path);
    }

    SDL_FreeSurface(surf);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
