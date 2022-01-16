// https://github.com/libsdl-org/SDL_ttf/blob/main/SDL_ttf.h

/* Get the dimensions of a rendered string of text */
extern DECLSPEC int SDLCALL TTF_SizeText(TTF_Font *font, const char *text, int *w, int *h);
extern DECLSPEC int SDLCALL TTF_SizeUTF8(TTF_Font *font, const char *text, int *w, int *h);
extern DECLSPEC int SDLCALL TTF_SizeUNICODE(TTF_Font *font, const Uint16 *text, int *w, int *h);

/* Get the measurement string of text without rendering
   e.g. the number of characters that can be rendered before reaching 'measure_width'
   in:
   measure_width - in pixels to measure this text
   out:
   count  - number of characters that can be rendered
   extent - latest calculated width
*/
extern DECLSPEC int SDLCALL TTF_MeasureText(TTF_Font *font, const char *text, int measure_width, int *extent, int *count);
extern DECLSPEC int SDLCALL TTF_MeasureUTF8(TTF_Font *font, const char *text, int measure_width, int *extent, int *count);
extern DECLSPEC int SDLCALL TTF_MeasureUNICODE(TTF_Font *font, const Uint16 *text, int measure_width, int *extent, int *count);


goal: render a file of text

for that we need to render each word separately, making sure not to 