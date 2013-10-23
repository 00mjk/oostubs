/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            O _ S T R E A M                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse O_Stream enthaelt die Definition des << Operators fuer die     */
/* wichtigsten der vordefinierten Datentypen und realisiert somit die        */
/* bekannte Ausgabefunktion der C++ IO_Stream Bibliothek. Zur Zeit wird die  */
/* Darstellung von Zeichen, Zeichenketten und ganzen Zahlen unterstuetzt.    */
/* Ein weiterer << Operator erlaubt die Verwendung von Manipulatoren.        */
/*                                                                           */
/* Neben der Klasse O_Stream sind hier auch die Manipulatoren hex, dec, oct  */
/* und bin fuer die Wahl der Basis bei der Zahlendarstellung, sowie endl     */
/* fuer den Zeilenumbruch definiert.                                         */
/*****************************************************************************/

#include "object/o_stream.h"

O_Stream &O_Stream::operator<<(unsigned char c) {
  put(c);
  return *this;
}

O_Stream &O_Stream::operator<<(char c) { return *this << (unsigned char)c; }

// Anfügen der Zahl number in dem gewählten Zahlensystem.
O_Stream &O_Stream::operator<<(unsigned short number) {
  return *this << (unsigned long)number;
}

O_Stream &O_Stream::operator<<(short number) { return *this << (long)number; }

O_Stream &O_Stream::operator<<(unsigned int number) {
  return *this << (unsigned long)number;
}

O_Stream &O_Stream::operator<<(int number) { return *this << (long)number; }

O_Stream &O_Stream::operator<<(unsigned long number) {
  char buf[sizeof(unsigned long) * 8 + 1]; // Platz fuer binaer + terminator.
  int pos = sizeof(buf);
  buf[--pos] = 0; // Puffer terminieren.

  while (number) {
    unsigned x = number % unsigned(base);
    buf[--pos] = (x < 10 ? '0' + x : 'a' + x - 10);
    number /= unsigned(base);
  }

  return *this << (buf + pos);
}

O_Stream &O_Stream::operator<<(long number) {
  if (base == DEC && number < 0) {
    *this << '-';
    number = -(unsigned long)number;
  }

  return *this << (unsigned long)number;
}

// Anfügen des Zeigerwertes pointer im Hexadezimalsystem.
O_Stream &O_Stream::operator<<(void *pointer) {
  bases old_mode = base;
  *this << hex << (unsigned long)pointer;
  base = old_mode;
  return *this;
}

// Anfügen der nullterminierten Zeichenkette text (ohne die Nullterminierung).
O_Stream &O_Stream::operator<<(const char *text) {
  while (*text)
    *this << *text++;

  return *this;
}

// ENDL: fuegt einen Zeilenumbruch in die Ausgabe ein.
O_Stream &endl(O_Stream &os) {
  os << '\n';
  os.flush();
  return os;
}

// BIN: waehlt das binaere Zahlensystem aus.
O_Stream &bin(O_Stream &os) {
  os.base = O_Stream::BIN;
  return os;
}

// OCT: waehlt das oktale Zahlensystem aus.
O_Stream &oct(O_Stream &os) {
  os.base = O_Stream::OCT;
  return os;
}

// DEC: waehlt das dezimale Zahlensystem aus.
O_Stream &dec(O_Stream &os) {
  os.base = O_Stream::DEC;
  return os;
}

// HEX: waehlt das hexadezimale Zahlensystem aus.
O_Stream &hex(O_Stream &os) {
  os.base = O_Stream::HEX;
  return os;
}
