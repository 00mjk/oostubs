/* $Id: cgascr.cc 5834 2013-10-08 17:04:08Z os $ */

/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             C G A _ S C R E E N                           */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe dieser Klasse kann man auf den Bildschirm des PCs zugreifen.    */
/* Der Zugriff erfolgt direkt auf der Hardwareebene, d.h. ueber den Bild-    */
/* schirmspeicher bzw. die I/O-Ports der Grafikkarte.                        */
/*****************************************************************************/

#include "machine/cgascr.h"

static char *const CGA_START = (char *)0xb8000;

void CGA_Screen::show(int x, int y, char c, unsigned char attrib) {
  char *pos = CGA_START + 2 * (x + y * 80);

  pos[0] = c;
  pos[1] = attrib;
}

void CGA_Screen::setpos(int x, int y) {
  IO_Port index(0x3d4);
  IO_Port data(0x3d5);

  unsigned short pos = x + (y * 80);
  // Cursor, higher 8 bits.
  index.outb(14);
  data.outb((pos >> 8) & 0xff);

  // Cursor, lower 8 bits.
  index.outb(15);
  data.outb(pos & 0xff);
}

void CGA_Screen::getpos(int &x, int &y) {
  IO_Port index(0x3d4);
  IO_Port data(0x3d5);

  unsigned short pos = 0;
  // Cursor, higher 8 bits.
  index.outb(14);
  pos |= (unsigned short)data.inb() << 8;

  // Cursor, lower 8 bits.
  index.outb(15);
  pos |= data.inb();

  x = pos % 80;
  y = pos / 80;
}

void CGA_Screen::print(const char *text, int length, unsigned char attrib) {
  int x, y;
  getpos(x, y);

  for (int i = 0; i != length; ++i) {
    // '\n' behandeln.
    if (text[i] == '\n') {
      ++y;
      x = 0;
    } else {
      // 1 Zeichen ausgeben.
      show(x, y, text[i], attrib);
      ++x;
    }

    // Wenn das Ende der Zeile erreicht ist umbrechen.
    if (x >= 80) {
      ++y;
      x = 0;
    }

    // Wenn das Ende des Bildschirms erreicht ist nach oben scrollen.
    if (y >= 25) {
      // Gesamten CGA-Speicher eine Zeile nach oben kopieren.
      for (int i = 0; i != 2 * 80 * 24; ++i)
        CGA_START[i] = CGA_START[i + (2 * 80)];
      // Letzte Zeile ausnullen.
      for (int i = 2 * 80 * 24; i != 2 * 80 * 25; i += 2) {
        CGA_START[i] = ' ';
	CGA_START[i+1] = 0x0f;
      }
      y = 24;
    }
  }

  setpos(x, y);
}

void CGA_Screen::clear() {
	for (int i = 0; i != 2 * 80 * 25; i += 2) {
		CGA_START[i] = ' ';
		CGA_START[i+1] = 0x0f;
	}
}

