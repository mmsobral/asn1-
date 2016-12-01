#ifndef ASN1BITSTRING_H
#define ASN1BITSTRING_H

#include <BIT_STRING.h>

// Classe para auxiliar o uso de BIT STRING
class ASN1BitString {
 private:
  BIT_STRING_t * ptr;
  int bits;
 public:
  // Construtor: parâmetros são um BIT STRING e seu tamanho em bits
  ASN1BitString(BIT_STRING_t & bs, int nbits);
  ASN1BitString(BIT_STRING_t & bs);
  ~ASN1BitString() {}

  // Ativa um bit na posição "pos"
  void set(int pos);

  // Desativa um bit na posição "pos"
  void reset(int pos);

  // retorna o valor do bit na posição "pos"
  bool get(int pos);

  // desativa todos os bits
  void clear();

  // ativa todos os bits
  void enable();
  
  // define todo o valor do bit string a partir do conteudo apontado 
  // por "ptr". Esse conteudo deve ter pelo menos "size"  bytes.
  ASN1BitString & operator=(uint8_t * buffer);
  
  // copia todo o valor do bit string para a area de memoria apontada
  // por "ptr". Esse area deve ter pelo menos "size"  bytes de capacidade.
  void get_bits(uint8_t * buffer) const;
private:
    void init();
    // redimensiona o tamanho do buffer para caber pelo menos "pos+1" bits
    void resize(int pos);
};

#endif
