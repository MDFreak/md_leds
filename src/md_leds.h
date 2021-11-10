#ifndef _MD_LEDS_H_
  #define _MD_LEDS_H_

  // --- basic system
    #include <Arduino.h>
    #include <md_defines.h>
    #include <md_util.h>

  // --- WS2812 matrix
    #include <Adafruit_GFX.h>
    #include <Adafruit_NeoMatrix.h>
    #include <Adafruit_NeoPixel.h>

    // --- 16 Bit color declarations
      #define COL16_RGB   RGB
      #define COL16_RBG   RBG
      #define COL16_GRB   GRB
      #define COL16_GBR   GBR
      #define COL16_BRG   BRG
      #define COL16_BGR   BGR

      #define COL16_BLACK		0

      #define COL16_RED_VERYLOW 	  (10 <<  11)
      #define COL16_RED_LOW 		    (17 <<  11)
      #define COL16_RED_MEDIUM 		  (24 << 11)
      #define COL16_RED_HIGH 		    (31 << 11)

      #define COL16_GREEN_VERYLOW	  (20 <<  5)
      #define COL16_GREEN_LOW 		  (34 << 5)
      #define COL16_GREEN_MEDIUM 	  (48 << 5)
      #define COL16_GREEN_HIGH 		  (63 << 5)

      #define COL16_BLUE_VERYLOW	  10
      #define COL16_BLUE_LOW 		    17
      #define COL16_BLUE_MEDIUM 	  24
      #define COL16_BLUE_HIGH 		  31

      #define COL16_YELLOW_VERYLOW  (COL16_RED_VERYLOW + COL16_GREEN_VERYLOW)
      #define COL16_YELLOW_LOW      (COL16_RED_LOW     + COL16_GREEN_LOW)
      #define COL16_YELLOW_Medium   (COL16_RED_MEDIUM  + COL16_GREEN_MEDIUM)
      #define COL16_YELLOW_HIGH     (COL16_RED_HIGH    + COL16_GREEN_HIGH)

      #define COL16_ORANGE_VERYLOW	(COL16_RED_VERYLOW + COL16_GREEN_VERYLOW)
      #define COL16_ORANGE_LOW		  (COL16_RED_LOW     + COL16_GREEN_LOW)
      #define COL16_ORANGE_MEDIUM	  (COL16_RED_MEDIUM  + COL16_GREEN_MEDIUM)
      #define COL16_ORANGE_HIGH		  (COL16_RED_HIGH    + COL16_GREEN_HIGH)

      #define COL16_PURPLE_VERYLOW	(COL16_RED_VERYLOW + COL16_BLUE_VERYLOW)
      #define COL16_PURPLE_LOW		  (COL16_RED_LOW     + COL16_BLUE_LOW)
      #define COL16_PURPLE_MEDIUM	  (COL16_RED_MEDIUM  + COL16_BLUE_MEDIUM)
      #define COL16_PURPLE_HIGH		  (COL16_RED_HIGH    + COL16_BLUE_HIGH)

      #define COL16_CYAN_VERYLOW	  (COL16_GREEN_VERYLOW + COL16_BLUE_VERYLOW)
      #define COL16_CYAN_LOW		    (COL16_GREEN_LOW     + COL16_BLUE_LOW)
      #define COL16_CYAN_MEDIUM		  (COL16_GREEN_MEDIUM  + COL16_BLUE_MEDIUM)
      #define COL16_CYAN_HIGH		    (COL16_GREEN_HIGH    + COL16_BLUE_HIGH)

      #define COL16_WHITE_VERYLOW	  (COL16_RED_VERYLOW + COL16_GREEN_VERYLOW + COL16_BLUE_VERYLOW)
      #define COL16_WHITE_LOW		    (COL16_RED_LOW     + COL16_GREEN_LOW     + COL16_BLUE_LOW)
      #define COL16_WHITE_MEDIUM	  (COL16_RED_MEDIUM  + COL16_GREEN_MEDIUM  + COL16_BLUE_MEDIUM)
      #define COL16_WHITE_HIGH		  (COL16_RED_HIGH    + COL16_GREEN_HIGH    + COL16_BLUE_HIGH)

    // --- mono color bitmaps 8x8
      typedef struct  // mono_col_bmp_t
        {
          int16_t  bmp_num; // -1 = no bmp
          uint16_t col;     //  0 = don't change
          uint8_t  bright;  //  0 = don't change
        } mono_col_bmp_t;

      typedef struct  // mono_col_txt_t
        {
          char*    text;    // NULL = no text
          uint16_t col;     //  0 = don't change
          uint8_t  bright;  //  0 = don't change
        } mono_col_txt_t;

      typedef struct
        {
          mono_col_bmp_t bmpB;
          mono_col_txt_t text;
          mono_col_bmp_t bmpE;
        } scroll2812_t;

      enum // bitmaps
        {
          MD_BITMAP_BIN_AA55 = 0,
          MD_BITMAP_BIN_55AA,
          MD_BITMAP_SMILY,
          MD_BITMAP_NOTSMIL,
          MD_BITMAP_FROWNY,
          MD_BITMAP_ARROW_R,
          MD_BITMAP_ARROW_L,
          MD_BITMAP_ARROW_U,
          MD_BITMAP_ARROW_D
        };

      static const uint8_t PROGMEM
        mono_bmp[][8] =
          {
          	{   // 0: BIN_AA55
          	    B10101010,
          	    B01010101,
          	    B10101010,
          	    B01010101,
          	    B10101010,
          	    B01010101,
          	    B10101010,
          	    B01010101,
              },
          	{   // 1: BIN_55AA
          	    B01010101,
          	    B10101010,
          	    B01010101,
          	    B10101010,
          	    B01010101,
          	    B10101010,
          	    B01010101,
          	    B10101010,
         			},
          	{   // 2: smiley
          	    B00111100,
          	    B01000010,
          	    B10100101,
          	    B10000001,
          	    B10100101,
          	    B10011001,
          	    B01000010,
          	    B00111100
              },
          	{   // 3: neutral
          	    B00111100,
          	    B01000010,
          	    B10100101,
          	    B10000001,
          	    B10111101,
          	    B10000001,
          	    B01000010,
          	    B00111100
              },
          	{   // 4; frowny
          	    B00111100,
          	    B01000010,
          	    B10100101,
          	    B10000001,
          	    B10011001,
          	    B10100101,
          	    B01000010,
          	    B00111100
              },
          	{   // 5; ->
          	    B00000000,
          	    B00010000,
          	    B00001000,
          	    B01111100,
          	    B00001000,
          	    B00010000,
          	    B00000000,
          	    B00000000
              },
          	{   // 6; <-
          	    B00000000,
          	    B00010000,
          	    B00100000,
          	    B01111100,
          	    B00100000,
          	    B00010000,
          	    B00000000,
          	    B00000000
              },
          	{   // 7; arrow up
          	    B00010000,
          	    B00111000,
          	    B01010100,
          	    B00010000,
          	    B00010000,
          	    B00010000,
          	    B00000000,
          	    B0000000
              },
          	{   // 8; arrow down
          	    B00000000,
          	    B00010000,
          	    B00010000,
          	    B00010000,
          	    B01010100,
          	    B00111000,
          	    B00010000,
          	    B00000000
              },
          };
    // --- color test bitmaps
      static const uint16_t PROGMEM
        // These bitmaps were written for a backend that only supported
          // 4 bits per color with Blue/Green/Red ordering while neomatrix
          // uses native 565 color mapping as RGB.
          // I'm leaving the arrays as is because it's easier to read
          // which color is what when separated on a 4bit boundary
          // The demo code will modify the arrays at runtime to be compatible
          // with the neomatrix color ordering and bit depth.
        RGB_bmp[][64] =
          {
              // 00: blue/red
              {	  0x000, 0x100, 0x200, 0x400, 0x600, 0x800, 0xA00, 0xF00,
      	          0x001, 0x101, 0x201, 0x401, 0x601, 0x801, 0xA01, 0xF01,
            	    0x002, 0x102, 0x202, 0x402, 0x602, 0x802, 0xA02, 0xF02,
                	0x004, 0x104, 0x204, 0x404, 0x604, 0x804, 0xA04, 0xF04,
                	0x006, 0x106, 0x206, 0x406, 0x606, 0x806, 0xA06, 0xF06,
                	0x008, 0x108, 0x208, 0x408, 0x608, 0x808, 0xA08, 0xF08,
                	0x00A, 0x10A, 0x20A, 0x40A, 0x60A, 0x80A, 0xA0A, 0xF0A,
                	0x00F, 0x10F, 0x20F, 0x40F, 0x60F, 0x80F, 0xA0F, 0xF0F,
                },
              // 01: green/red
              {	  0x000, 0x100, 0x200, 0x400, 0x600, 0x800, 0xA00, 0xF00,
      	          0x010, 0x110, 0x210, 0x410, 0x610, 0x810, 0xA10, 0xF10,
            	    0x020, 0x120, 0x220, 0x420, 0x620, 0x820, 0xA20, 0xF20,
                	0x040, 0x140, 0x240, 0x440, 0x640, 0x840, 0xA40, 0xF40,
                	0x060, 0x160, 0x260, 0x460, 0x660, 0x860, 0xA60, 0xF60,
                	0x080, 0x180, 0x280, 0x480, 0x680, 0x880, 0xA80, 0xF80,
                	0x0A0, 0x1A0, 0x2A0, 0x4A0, 0x6A0, 0x8A0, 0xAA0, 0xFA0,
                	0x0F0, 0x1F0, 0x2F0, 0x4F0, 0x6F0, 0x8F0, 0xAF0, 0xFF0,
                },
              // 02: blue/green
              {	  0x000, 0x010, 0x020, 0x040, 0x060, 0x080, 0x0A0, 0x0F0,
      	          0x001, 0x011, 0x021, 0x041, 0x061, 0x081, 0x0A1, 0x0F1,
            	    0x002, 0x012, 0x022, 0x042, 0x062, 0x082, 0x0A2, 0x0F2,
                	0x004, 0x014, 0x024, 0x044, 0x064, 0x084, 0x0A4, 0x0F4,
                	0x006, 0x016, 0x026, 0x046, 0x066, 0x086, 0x0A6, 0x0F6,
                	0x008, 0x018, 0x028, 0x048, 0x068, 0x088, 0x0A8, 0x0F8,
                	0x00A, 0x01A, 0x02A, 0x04A, 0x06A, 0x08A, 0x0AA, 0x0FA,
                	0x00F, 0x01F, 0x02F, 0x04F, 0x06F, 0x08F, 0x0AF, 0x0FF,
                },
              // 03: grey / red
              {	  0x000, 0x011, 0x022, 0x044, 0x066, 0x088, 0x0AA, 0x0FF,
                	0x100, 0x111, 0x122, 0x144, 0x166, 0x188, 0x1AA, 0x1FF,
                	0x200, 0x211, 0x222, 0x244, 0x266, 0x288, 0x2AA, 0x2FF,
                	0x400, 0x411, 0x422, 0x444, 0x466, 0x488, 0x4AA, 0x4FF,
                	0x600, 0x611, 0x622, 0x644, 0x666, 0x688, 0x6AA, 0x6FF,
                	0x800, 0x811, 0x822, 0x844, 0x866, 0x888, 0x8AA, 0x8FF,
                	0xA00, 0xA11, 0xA22, 0xA44, 0xA66, 0xA88, 0xAAA, 0xAFF,
                	0xF00, 0xF11, 0xF22, 0xA44, 0xF66, 0xF88, 0xFAA, 0xFFF,
                },
              // 04: grey / green
              {	  0x000, 0x101, 0x202, 0x404, 0x606, 0x808, 0xA0A, 0xF0F,
                	0x010, 0x121, 0x212, 0x414, 0x616, 0x818, 0xA1A, 0xF1F,
                	0x020, 0x131, 0x222, 0x424, 0x626, 0x828, 0xA2A, 0xF2F,
                	0x040, 0x151, 0x242, 0x444, 0x646, 0x848, 0xA4A, 0xF4F,
                	0x060, 0x171, 0x262, 0x464, 0x666, 0x868, 0xA6A, 0xF6F,
                	0x080, 0x191, 0x282, 0x484, 0x686, 0x888, 0xA8A, 0xF8F,
                	0x0A0, 0x1A1, 0x2A2, 0x4A4, 0x6A6, 0x8A8, 0xAAA, 0xFAF,
                	0x0F0, 0x1F1, 0x2F2, 0x4F4, 0x6F6, 0x8F8, 0xAFA, 0xFFF,
                },
              // 05: grey / blue
              {	  0x000, 0x110, 0x220, 0x440, 0x660, 0x880, 0xAA0, 0xFF0,
                	0x001, 0x112, 0x221, 0x441, 0x661, 0x881, 0xAA1, 0xFF1,
                	0x002, 0x113, 0x222, 0x442, 0x662, 0x882, 0xAA2, 0xFF2,
                	0x004, 0x115, 0x224, 0x444, 0x664, 0x884, 0xAA4, 0xFF4,
                	0x006, 0x117, 0x226, 0x446, 0x666, 0x886, 0xAA6, 0xFF6,
                	0x008, 0x119, 0x228, 0x448, 0x668, 0x888, 0xAA8, 0xFF8,
                	0x00A, 0x11A, 0x22A, 0x44A, 0x66A, 0x88A, 0xAAA, 0xFFA,
                	0x00F, 0x11F, 0x22F, 0x44F, 0x66F, 0x88F, 0xAAF, 0xFFF,
                },
            };
    //
  // --- class md_ws2812_matrix
    class md_ws2812_matrix
      {
        public:
          md_ws2812_matrix(uint16_t matrixW, uint16_t matrixH, uint8_t tX=0, uint8_t tY=0,
                           uint8_t pin = 6,
                           uint8_t matrixType = NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS +
                                                NEO_TILE_TOP   + NEO_TILE_LEFT   + NEO_TILE_ROWS +
                                                NEO_MATRIX_ZIGZAG,
                           neoPixelType ledType = NEO_GRB + NEO_KHZ800);

          void begin(bool doSetup = true);
          void clear() { _pMatrix->clear(); }

            // Convert a BGR 4/4/4 bitmap to RGB 5/6/5 used by Adafruit_GFX
          void fixdrawRGBBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h);
            // In a case of a tile of neomatrices, this test is helpful to make sure that the
              // pixels are all in sequence (to check your wiring order and the tile options you
              // gave to the constructor).
          void count_pixels();
            // Fill the screen with multiple levels of white to gauge the quality
          void display_four_white();
          void display_bitmap(uint8_t bmp_num, uint16_t color);
          void display_rgbBitmap(uint8_t bmp_num);
          void display_lines();
          void display_boxes();
          void display_circles();
          void display_resolution();
          //void start_scroll_task(scroll2812_t* out, int16_t* pos, uint64_t updateT_us = 500000u);
          //void scroll_matrix(bool startup = false);
          void start_scroll_matrix(scroll2812_t* out, int16_t* xpos, int16_t xlast);
          void scroll_matrix(bool startup = false);
          void scroll_colorLine(bool startup = false);
          //void display_scroll(uint8_t anzBM_front, char* ptext, uint8_t anzBM_end, uint8_t brightness = 10);

        private:
          Adafruit_NeoMatrix *_pMatrix = NULL;
          int16_t             _mtW, _mtH;
          uint8_t             _mType, _tX, _tY;
          scroll2812_t*       _scrOut = NULL;
          int16_t*            _scrPos = NULL;
          int16_t             _maxPos = 0;
          int16_t             _minPos = 0;
          uint8_t             _bitmw; // = bitmap width
          int16_t             _lpos;
          int16_t             _lsize;

      };
#endif // _MD_LEDS_H_