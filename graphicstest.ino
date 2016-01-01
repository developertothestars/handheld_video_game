#include "SPI.h"
#include "ILI9341_t3.h"

struct SPRITEINFO
{
   uint16_t width,
   uint16_t height;
   uint16_t color;
   uint8_t  data;
};

// For the Adafruit shield, these are the default.
#define TFT_DC  9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

extern unsigned char mothership_bmp[];
extern unsigned char row_one_a_bmp[];
extern unsigned char row_two_a_bmp[];
extern unsigned char row_four_a_bmp[];
extern unsigned char cannon_bmp[];

int lives;
int alien_top;
int alien_left;

void setup() {
  tft.begin();
  tft.setRotation(1);
}


void showline(int x, int y, int d, char *str)
{
   while (*str)
   {
      tft.drawChar(x, y, *str, ILI9341_GREEN, ILI9341_BLACK, 1);
      str++;
      x += 8;
      delay(d);
   }
}


void showscore(int player, int score)
{
   int xpos;
   char buf[5];

   xpos = 0;
   switch (player)
   {
      case 1:
      xpos = 74;
      break;

      case 2:
      xpos = 218;
      break;

      case 3:
      xpos = 138;
      break;
   }
   if (score == -1)
      sprintf(buf, "    ");
   else
      sprintf(buf, "%04d", score);
   showline(xpos, 16, 0, buf);
}


void showlives(void)
{
    int i;
    
    tft.drawChar(58, 232, '0' + lives, ILI9341_GREEN, ILI9341_BLACK, 1);
    for (i = 0; i < lives - 1; i++)
        tft.writeRect(75 + 15 * i, 232, 13, 8, (uint16_t *)cannon_bmp);
}


void attractmode(void)
{
   tft.fillScreen(ILI9341_BLACK);

   showsprite(0, 0, small_invader);

   delay(5000);
   return;

   showline(58, 0, 0, "SCORE<1> HI-SCORE SCORE<2>");
   showscore(1, 0);
   showscore(3, 1810);
   showscore(2, 0);
   tft.setTextColor(ILI9341_GREEN);
   showline(76, 216, 0, "*THE DA VINCI CODERS*");
   tft.setTextColor(ILI9341_WHITE);
   showline(186, 232, 0, "CREDIT 00");
   showline(146, 48, 100, "PLAY");
   showline(108, 80, 100, "SPACE INVADERS");
   showline(90, 112, 0, "*SCORE ADVANCE TABLE*");
   tft.writeRect(112, 128, 16, 7, (uint16_t *)mothership_bmp);
   tft.writeRect(116, 144, 8, 8, (uint16_t *)row_one_a_bmp);
   tft.writeRect(115, 160, 11, 8, (uint16_t *)row_two_a_bmp);
   tft.writeRect(114, 176, 12, 8, (uint16_t *)row_four_a_bmp);
   showline(130, 128, 100, "=? MYSTERY");
   showline(130, 144, 100, "=30 POINTS");
   showline(130, 160, 100, "=20 POINTS");
   showline(130, 176, 100, "=10 POINTS");
   delay(1000);
}


void startplay(void)
{
   int i;
   int score;
    
   score = 0;
   lives = 5;
   alien_top = 48;
   alien_left = 72;
   tft.fillRect(76, 48, 255, 223, ILI9341_BLACK);
   showscore(1, score - 1);
   showscore(2, -1);
   showline(103, 115, 0, "PLAY PLAYER<1>");
   showlives();
   for (i = 0; i < 11; i++)
   {
       delay(100);
       score = 1 - score;
       showscore(1, score - 1);
   }
   delay(100);
}


void play(void)
{
}


void loop(void)
{
   attractmode();
   startplay();
   play();
}
