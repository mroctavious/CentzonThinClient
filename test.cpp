#include "src/RFID/RFID.h"

int main (void)
{
  RFID *pko = new RFID();
  MFRC522::MIFARE_Key key;
  while(1){
    pko->update();
    if (pko->getStatus() == NEW_CARD) std::cout << "New card" << std::endl;
  }

  delete pko;
  return 0;
}