/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                       S T R I N G B U F F E R                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Stringbuffer stellt einen Puffer fuer die Sammlung von Zeichen */
/* zur Darstellung auf dem Bildschirm oder anderen Ausgabegeraeten bereit.   */
/* Die Ausgabe der Zeichen erfolgt, sobald der Puffer voll ist oder wenn     */
/* explizit die Methode flush() aufgerufen wird.                             */
/* Da Stringbuffer geraeteunabhaengig sein soll, ist flush() eine virtuelle  */
/* Methode, die von den abgeleiteten Klassen definiert werden muss.          */
/*****************************************************************************/

#ifndef __strbuf_include__
#define __strbuf_include__

class Stringbuffer
 {
private:
  Stringbuffer(const Stringbuffer &copy); // Verhindere Kopieren

protected:
  enum {
    BUFFER_SIZE = 1024
  };
  char buffer[BUFFER_SIZE];
  int size;

public:
  Stringbuffer() : size(0) {}

  // Diese Methode fügt das Zeichen c an das Ende der bereits gesammelten
  // Zeichen an. Wenn die Pufferkapazität des Stringbuffer-Objektes nun
  // erschöpft ist, müssen die gesammelten Zeichen durch Aufruf der Methode
  // flush () verarbeitet werden.
  void put(char c);

  // Mit dieser Methode sollen die gesammelten Zeichen verarbeitet und so
  // Platz für neue Zeichen geschaffen werden. Die Implementierung der
  // Methode soll jedoch erst in den abgeleiteten Klassen erfolgen.
  virtual void flush() = 0;
};

#endif
