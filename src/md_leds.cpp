//#ifdef UNUSED
#include <md_leds.h>

// --- declaration
  // --- Matrix2812
#ifdef XXXX
      TaskHandle_t* const prunHdl    = NULL;
      md_ws2812_matrix*   prunMatrix = NULL;
      uint64_t            taskT_us   = 500;
  // --- tasks
  void runText2812Task(void* pvParameters)
    {
      //#if (WIFI_DEBUG_MODE > CFG_DEBUG_NONE)
      while(true)
        {
          //SOUT(micros()); SOUT(" runTask ");

          //prunMatrix->display_scroll();

          //String taskMessage = "runText task on core ";
          //taskMessage = taskMessage + xPortGetCoreID();
          //SOUT(micros()); SOUT(" "); SOUTLN(taskMessage);
        //#endif
          sleep(1);
        }
    }
#endif
// --- global functions
#ifdef XXXX
  void startrunText2812Task()
    {
      xTaskCreatePinnedToCore(
          runText2812Task, // TaskFunction_t pvTaskCode,
					"runText2812Task",	// const char * const pcName,
					10000, // const uint32_t usStackDepth,
					NULL, // void * const pvParameters,
					0, // UBaseType_t uxPriority,
					prunHdl, // TaskHandle_t * const pvCreatedTask,
					0);  // const BaseType_t xCoreID);
      SOUTLN("runText2812 task created on core 0");
    }
#endif

// --- classes
  // --- class md_ws2812_matrix
      md_ws2812_matrix::md_ws2812_matrix(uint16_t mtW, uint16_t mtH, uint8_t tX, uint8_t tY, uint8_t pin, uint8_t matrixType, neoPixelType ledType)
        {
          _mType = matrixType;
          _mtW   = mtW;
          _mtH   = mtH;
          _tX   = tX;
          _tY   = tY;
          if (tX * tY == 0)
            {
              tX = 0;
              tY = 0;
              _pMatrix = new Adafruit_NeoMatrix(_mtW, _mtH, pin, _mType, ledType);
            }
            else
            {
              _pMatrix = new Adafruit_NeoMatrix(_mtW, _mtH, _tX, _tY, pin, _mType, ledType);
            }
        }

      void md_ws2812_matrix::begin(bool doSetup)
        {
          _pMatrix->begin();
          if (doSetup)
            {
              _pMatrix->setTextWrap(false);
              _pMatrix->setBrightness(100);
              _pMatrix->fillScreen(COL16_WHITE_MEDIUM);
              //display_boxes();
              //usleep(300000);
              _pMatrix->clear();
              _pMatrix->show();
            }
        }

      // Convert a BGR 4/4/4 bitmap to RGB 5/6/5 used by Adafruit_GFX
      void md_ws2812_matrix::fixdrawRGBBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h)
        {
          static uint16_t *RGB_bmp_fixed = (uint16_t *) malloc( w*h*2);
          for (uint16_t pixel=0; pixel<w*h; pixel++)
            {
            	uint8_t r,g,b;
            	uint16_t color = pgm_read_word(bitmap + pixel);
                	//Serial._pMatrix->print(color, HEX);
            	b = (color & 0xF00) >> 8;
            	g = (color & 0x0F0) >> 4;
            	r = color & 0x00F;
                	//Serial._pMatrix->print(" ");
                	//Serial._pMatrix->print(b);
                	//Serial._pMatrix->print("/");
                	//Serial._pMatrix->print(g);
                	//Serial._pMatrix->print("/");
                	//Serial._pMatrix->print(r);
                	//Serial._pMatrix->print(" -> ");
                	// expand from 4/4/4 bits per color to 5/6/5
            	b = map(b, 0, 15, 0, 31);
            	g = map(g, 0, 15, 0, 63);
            	r = map(r, 0, 15, 0, 31);
                	//Serial._pMatrix->print(r);
                	//Serial._pMatrix->print("/");
                	//Serial._pMatrix->print(g);
                	//Serial._pMatrix->print("/");
                	//Serial._pMatrix->print(b);
            	RGB_bmp_fixed[pixel] = (r << 11) + (g << 5) + b;
                	//Serial._pMatrix->print(" -> ");
                	//Serial.println(RGB_bmp_fixed[pixel], HEX);
            }
          _pMatrix->drawRGBBitmap(x, y, RGB_bmp_fixed, w, h);
        }
      // In a case of a tile of neomatrices, this test is helpful to make sure that the
        // pixels are all in sequence (to check your wiring order and the tile options you
        // gave to the constructor).
      void md_ws2812_matrix::count_pixels()
        {
          uint16_t lc = _mtH - 1;
          uint16_t lr = _mtW - 1;
          uint16_t l2c = lc;
          uint16_t l2r = lr;
          uint16_t l3c = lc - 1;
          uint16_t l3r = lr - 1;
          uint16_t l4c = lc - 1;
          uint16_t l4r = lr - 1;

          _pMatrix->clear();
          for (uint16_t i=0; i<_mtH; i++)
            {
            	for (uint16_t j=0; j<_mtW; j++)
                {
            	    _pMatrix->drawPixel(j, i, i%3==0?COL16_BLUE_HIGH:i%3==1?COL16_RED_HIGH:COL16_GREEN_HIGH);
            	    _pMatrix->drawPixel(lc, lr, lr%3==0?COL16_BLUE_MEDIUM:lr%3==1?COL16_RED_MEDIUM:COL16_GREEN_MEDIUM);
            	    _pMatrix->drawPixel(l2c, l2r, l2r%3==0?COL16_BLUE_LOW:l2r%3==1?COL16_RED_LOW:COL16_GREEN_LOW);
            	    _pMatrix->drawPixel(l3c, l3r, l3r%3==0?COL16_BLUE_LOW:l3r%3==1?COL16_RED_LOW:COL16_GREEN_LOW);
            	    _pMatrix->drawPixel(l4c, l4r, COL16_BLACK);
                  l4c = l3c;
                  l4r = l3r;
                  l3c = l2c;
                  l3r = l2r;
                  l2c = lc;
                  l2r = lr;
                  lc = j;
                  lr = i;
                  // depending on the matrix size, it's too slow to display each pixel, so
              	    // make the scan init faster. This will however be too fast on a small matrix.
            	    //if (!(j%7))
                    _pMatrix->show();
                    //usleep(300);
            	    //yield();
            	  }
            }
        }
      // Fill the screen with multiple levels of white to gauge the quality
      void md_ws2812_matrix::display_four_white()
        {
          _pMatrix->clear();
          _pMatrix->fillRect(0,0, _mtW,  _mtH,   COL16_WHITE_HIGH);
          _pMatrix->show(); usleep(300000);
          _pMatrix->drawRect(1,1, _mtW-2,_mtH-2, COL16_WHITE_MEDIUM);
          _pMatrix->show(); usleep(300000);
          _pMatrix->drawRect(2,2, _mtW-4,_mtH-4, COL16_WHITE_LOW);
          _pMatrix->show(); usleep(300000);
          _pMatrix->drawRect(3,3, _mtW-6,_mtH-6, COL16_WHITE_VERYLOW);
          _pMatrix->show(); usleep(300000);
        }

      void md_ws2812_matrix::display_bitmap(uint8_t bmp_num, uint16_t color)
        {
          static uint16_t bmx,bmy;

          // Clear the space under the bitmap that will be drawn as
          // drawing a single color pixmap does not write over pixels
          // that are nul, and leaves the data that was underneath
          _pMatrix->fillRect(bmx,bmy, bmx+8,bmy+8, COL16_BLACK);
          _pMatrix->drawBitmap(bmx, bmy, mono_bmp[bmp_num], 8, 8, color);
          bmx += 8;
          if (bmx >= _mtW) bmx = 0;
          if (!bmx) bmy += 8;
          if (bmy >= _mtH) bmy = 0;
          _pMatrix->show();
        }

      void md_ws2812_matrix::display_rgbBitmap(uint8_t bmp_num)
        {
          static uint16_t bmx,bmy;

          fixdrawRGBBitmap(bmx, bmy, RGB_bmp[bmp_num], 8, 8);
          bmx += 8;
          if (bmx >= _mtW) bmx = 0;
          if (!bmx) bmy += 8;
          if (bmy >= _mtH) bmy = 0;
          _pMatrix->show();
        }

      void md_ws2812_matrix::display_lines()
        {
          _pMatrix->clear();

          // 4 levels of crossing red lines.
          _pMatrix->drawLine(0,_mtW/2-2, _mtW-1,2, COL16_RED_VERYLOW);
          _pMatrix->drawLine(0,_mtW/2-1, _mtW-1,3, COL16_RED_LOW);
          _pMatrix->drawLine(0,_mtW/2,   _mtW-1,   _mtW/2,   COL16_RED_MEDIUM);
          _pMatrix->drawLine(0,_mtW/2+1, _mtW-1,   _mtW/2+1, COL16_RED_HIGH);

          // 4 levels of crossing green lines.
          _pMatrix->drawLine(_mtW/2-2, 0, _mtW/2-2, _mtH-1, COL16_GREEN_VERYLOW);
          _pMatrix->drawLine(_mtW/2-1, 0, _mtW/2-1, _mtH-1, COL16_GREEN_LOW);
          _pMatrix->drawLine(_mtW/2+0, 0, _mtW/2+0, _mtH-1, COL16_GREEN_MEDIUM);
          _pMatrix->drawLine(_mtW/2+1, 0, _mtW/2+1, _mtH-1, COL16_GREEN_HIGH);

          // Diagonal blue line.
          _pMatrix->drawLine(0,0, _mtW-1,_mtH-1, COL16_BLUE_HIGH);
          _pMatrix->drawLine(0,_mtH-1, _mtW-1,0, COL16_ORANGE_MEDIUM);
          _pMatrix->show();
        }

      void md_ws2812_matrix::display_boxes()
        {
          for (uint8_t n=0; n<_tX ; n++ )
            {
              _pMatrix->clear();
              _pMatrix->drawRect(n*_mtW + 0, 0, _mtW,  _mtH,   COL16_BLUE_HIGH);
              _pMatrix->drawRect(n*_mtW + 1, 1, _mtW-2,_mtH-2, COL16_GREEN_MEDIUM);
              _pMatrix->fillRect(n*_mtW + 2, 2, _mtW-4,_mtH-4, COL16_RED_HIGH);
              _pMatrix->fillRect(n*_mtW + 3, 3, _mtW-6,_mtH-6, COL16_ORANGE_MEDIUM);
              _pMatrix->show();
              usleep(50000);
            }
          _pMatrix->clear();
          _pMatrix->show();
        }

      void md_ws2812_matrix::display_circles()
        {
          _pMatrix->clear();
          _pMatrix->drawCircle(_mtW/2,_mtH/2, 2, COL16_RED_MEDIUM);
          _pMatrix->drawCircle(_mtW/2-1-min(_mtW,_mtH)/8,
                     _mtH/2-1-min(_mtW,_mtH)/8,
                     min(_mtW,_mtH)/4, COL16_BLUE_HIGH);
          _pMatrix->drawCircle(_mtW/2+1+min(_mtW,_mtH)/8,
                     _mtH/2+1+min(_mtW,_mtH)/8,
                     min(_mtW,_mtH)/4-1, COL16_ORANGE_MEDIUM);
          _pMatrix->drawCircle(1,_mtH-2, 1, COL16_GREEN_LOW);
          _pMatrix->drawCircle(_mtW-2,1, 1, COL16_GREEN_HIGH);
          if (min(_mtW,_mtH)>12)
            {
              _pMatrix->drawCircle(_mtW/2-1, _mtH/2-1,
                         min(_mtH/2-1,_mtW/2-1), COL16_CYAN_HIGH);
            }
          _pMatrix->show();
        }

      void md_ws2812_matrix::display_resolution()
        {
          _pMatrix->setTextSize(1);
          // not wide enough;
          if (_mtW<16) return;
          _pMatrix->clear();
          // Font is 5x7, if display is too small
          // 8 can only display 1 char
          // 16 can almost display 3 chars
          // 24 can display 4 chars
          // 32 can display 5 chars
          _pMatrix->setCursor(0, 0);
          _pMatrix->setTextColor(_pMatrix->Color(255,0,0));
          if (_mtW>10) _pMatrix->print(_mtW/10);
          _pMatrix->setTextColor(_pMatrix->Color(255,128,0));
          _pMatrix->print(_mtW % 10);
          _pMatrix->setTextColor(_pMatrix->Color(0,255,0));
          _pMatrix->print('x');
          // not wide enough to _pMatrix->print 5 chars, go to next line
          if (_mtW<25)
            {
            	if (_mtH==13)
                {
                  _pMatrix->setCursor(6, 7);
                }
            	else if (_mtH>=13)
                {
            	    _pMatrix->setCursor(_mtW-11, 8);
            	  }
              else
                {
            	    // we're not tall enough either, so we wait and display
            	    // the 2nd value on top.
            	    _pMatrix->show();
            	    delay(2000);
            	    _pMatrix->clear();
            	    _pMatrix->setCursor(_mtW-11, 0);
            	  }
            }
          _pMatrix->setTextColor(_pMatrix->Color(0,255,128));
          _pMatrix->print(_mtH/10);
          _pMatrix->setTextColor(_pMatrix->Color(0,128,255));
          _pMatrix->print(_mtH % 10);
          // enough room for a 2nd line
          if ((_mtW>25 && _mtH >14) || _mtH>16)
            {
            	_pMatrix->setCursor(0, _mtH-7);
            	_pMatrix->setTextColor(_pMatrix->Color(0,255,255));
            	if (_mtW>16) _pMatrix->print('*');
            	_pMatrix->setTextColor(_pMatrix->Color(255,0,0));
            	_pMatrix->print('R');
            	_pMatrix->setTextColor(_pMatrix->Color(0,255,0));
            	_pMatrix->print('G');
            	_pMatrix->setTextColor(_pMatrix->Color(0,0,255));
            	_pMatrix->print("B");
            	_pMatrix->setTextColor(_pMatrix->Color(255,255,0));
            	// this one could be displayed off screen, but we don't care :)
            	_pMatrix->print("*");

            	// We have a big array, great, let's assume 32x32 and add something in the middle
            	if (_mtH>24 && _mtW>25)
                {
            	    for (uint16_t i=0; i<_mtW; i+=8) fixdrawRGBBitmap(i, _mtH/2-7+(i%16)/8*6, RGB_bmp[10], 8, 8);
            	  }
            }
          _pMatrix->show();
        }

#ifdef XXXX
        void md_ws2812_matrix::start_scroll_task(scroll2812_t* out, int16_t* pos, uint64_t updateT_us)
          {
            if (prunMatrix == NULL)
              {
                _scrOut = out;
                _scrPos = pos;
                //display_scroll(true);
                //startrunText2812Task();
                prunMatrix = this;
              }
            taskT_us   = updateT_us;
          }
#endif
      //void md_ws2812_matrix::scroll_matrix(bool startup)
      void md_ws2812_matrix::start_scroll_matrix(scroll2812_t* out, int16_t* xpos, int16_t xlast)
        {
          _scrOut = out;
          _scrPos = xpos;
          _maxPos = *xpos;
          _minPos = xlast;
          scroll_matrix(true);
        }

      void md_ws2812_matrix::scroll_matrix(bool startup)
        {
          uint8_t  bitmw  = 8; // = bitmh
          uint8_t  lettw  = 6;
          uint16_t bcol   = COL16_BLACK;
          uint16_t tlen   = strlen(_scrOut->text.text) * lettw ;
          int16_t  x      = *_scrPos;
              //SOUT("scroll_matrix ... x="); SOUT(x); SOUT(" min "); SOUT(_minPos);

          _pMatrix->setTextWrap(false);  // we don't wrap text so it scrolls nicely
          _pMatrix->setTextSize(1);
          _pMatrix->setRotation(0); //

          //for (x=_mtW+2*bitmw ; x>=-(tlen + 4*bitmw - lettw); x--)
          //  {
          // delete old output
              //SOUT(" clear ");
          _pMatrix->clear();
          //write new output
          _pMatrix->setBrightness(_scrOut->bmpB.bright);
          if (_scrOut->bmpB.bmp_num > NU)
            {
              //SOUT(" drawBitmap ");
              _pMatrix->drawBitmap(x-bitmw-1, 0, mono_bmp[_scrOut->bmpB.bmp_num], 8, 8, _scrOut->bmpB.col);
            }
          if (_scrOut->bmpE.bmp_num > NU)
            {
              _pMatrix->setBrightness(_scrOut->bmpE.bright);
              _pMatrix->drawBitmap(x+tlen, 0, mono_bmp[_scrOut->bmpE.bmp_num], 8, 8, _scrOut->bmpE.col);
            }
        	if (_scrOut->text.text != NULL)
            {
              _pMatrix->setCursor(x,0);
            	_pMatrix->setTextColor(_scrOut->text.col);
            	_pMatrix->print(_scrOut->text.text);
              //SOUT("scroll_matrix ... x="); SOUT((x));
            }
              //SOUT(" md_leds.show ");
          _pMatrix->show();
              //SOUTLN(" ready ");
            //}
//          if ( x < -(tlen + 2*bitmw - lettw))
          if ( --x < _minPos)
            {
              x=_maxPos;
            }

          *_scrPos = x;
        }

      void md_ws2812_matrix::scroll_colorLine(bool startup)
        {
                  SOUT(" scroll_colorLine ... ");

          if ( startup == true )
            {
              SOUT(" startup ");
              _pMatrix->setRotation(0);
              _pMatrix->setBrightness(5);
              _bitmw = sizeof(RGB_bmp[0]) / 2;
              _lpos  = 0;
              _lsize = _mtW % _bitmw + 1;
            }
          else
            {
              SOUT(" start loop ... ");
              for (uint8_t i = 0; i < _lsize ; i ++ )
                {
                  SOUT("i"); SOUT(i); SOUT(" ");
                  for (uint8_t j = 0; j < _bitmw ; j++ )
                    {
                      SOUT("j"); SOUT(j); SOUT(" ");
                      _pMatrix->drawPixel(_lpos, 0, RGB_bmp[i][j]);
                      _lpos++;
                      if (_lpos > _lsize) { _lpos= 0; }
                    }
                }
              SOUTLN();
            }
          _pMatrix->show();
        }

      // Scroll within big bitmap so that all if it becomes visible or bounce a small one.
        // If the bitmap is bigger in one dimension and smaller in the other one, it will
        // be both panned and bounced in the appropriate dimensions.
      #ifdef UNUSED
          void display_panOrBounceBitmap (uint8_t bitmapSize)
            {
              // keep integer math, deal with values 16 times too big
              // start by showing upper left of big bitmap or centering if the display is big
              int16_t xf = max(0, (matrixW-bitmapSize)/2) << 4;
              int16_t yf = max(0, (matrixH-bitmapSize)/2) << 4;
              // scroll speed in 1/16th
              int16_t xfc = 6;
              int16_t yfc = 3;
              // scroll down and right by moving upper left corner off screen
              // more up and left (which means negative numbers)
              int16_t xfdir = -1;
              int16_t yfdir = -1;

              for (uint16_t i=1; i<200; i++)
                {
                	bool updDir = false;

                	// Get actual x/y by dividing by 16.
                	int16_t x = xf >> 4;
                	int16_t y = yf >> 4;

                	_pMatrix->clear();
                	// bounce 8x8 tri color smiley face around the screen
                	if (bitmapSize == 8) _pMatrix->fixdrawRGBBitmap(x, y, RGB_bmp[10], 8, 8);
                	// pan 24x24 pixmap
                	if (bitmapSize == 24)
                    {
                      _pMatrix->drawRGBBitmap(x, y, (const uint16_t *) bitmap24, bitmapSize, bitmapSize);
                    }
                      #ifdef BM32
                        	if (bitmapSize == 32) _pMatrix->drawRGBBitmap(x, y, (const uint16_t *) bitmap32, bitmapSize, bitmapSize);
                        #endif
                	pMatrix->show();

                	// Only pan if the display size is smaller than the pixmap
                	// but not if the difference is too small or it'll look bad.
                	if (bitmapSize-matrixW > 2)
                    {
                	    xf += xfc*xfdir;
                	    if (xf >= 0)                      { xfdir = -1; updDir = true ; };
                	    // we don't go negative past right corner, go back positive
                	    if (xf <= ((matrixW-bitmapSize) << 4)) { xfdir = 1;  updDir = true ; };
                	  }
                	if (bitmapSize-matrixH > 2)
                    {
                	    yf += yfc*yfdir;
                	    // we shouldn't display past left corner, reverse direction.
                	    if (yf >= 0)                      { yfdir = -1; updDir = true ; };
                	    if (yf <= ((matrixW-bitmapSize) << 4)) { yfdir = 1;  updDir = true ; };
                	  }
                	// only bounce a pixmap if it's smaller than the display size
                	if (matrixW>bitmapSize)
                    {
                	    xf += xfc*xfdir;
                	    // Deal with bouncing off the 'walls'
                	    if (xf >= (matrixW-bitmapSize) << 4) { xfdir = -1; updDir = true ; };
                	    if (xf <= 0)           { xfdir =  1; updDir = true ; };
                	  }
                	if (matrixH>bitmapSize)
                    {
                	    yf += yfc*yfdir;
                	    if (yf >= (matrixH-bitmapSize) << 4) { yfdir = -1; updDir = true ; };
                	    if (yf <= 0)           { yfdir =  1; updDir = true ; };
                	  }

                	if (updDir)
                    {
                	    // Add -1, 0 or 1 but bind result to 1 to 1.
                	    // Let's take 3 is a minimum speed, otherwise it's too slow.
                	    xfc = _pMatrix->constrain(xfc + random(-1, 2), 3, 16);
                	    yfc = _pMatrix->constrain(xfc + random(-1, 2), 3, 16);
                	  }
                	delay(10);
                }
            }
        #endif

//#endif