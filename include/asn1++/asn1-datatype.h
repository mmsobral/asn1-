#ifndef ASN1DATATYPE_H
#define ASN1DATATYPE_H

#include <asn_application.h>

// Classe para auxiliar o uso do tipo de dados ASN1 definido pelo usuário
// Definida como template para suportar qualquer tipo de dados 
template <typename T> class ASN1DataType  {
 protected:
  T * pkt;
  asn_TYPE_descriptor_t * DESC;
  bool destroy;

 public:
  // Construtor: parâmetro é o descritor do tipo de dados definido por T
  // cria um valor vazio do tipo de dados
  ASN1DataType(asn_TYPE_descriptor_t * desc);

  // Construtor: parâmetros são o descritor do tipo de dados definido por T e 
  // uma instância do tipo de dados existente
  ASN1DataType(asn_TYPE_descriptor_t * desc, T * apkt);
  virtual ~ASN1DataType();

  void set_destroy(bool val);

  // retorna um ponteiro para o descritor do tipo de dados
  asn_TYPE_descriptor_t * get_desc();

  // Apresenta o tipo de dados na tela (debug)
  void show() const;

  // Verifica se valores do tipo de dados respeitam as restrições da especificação
  // ASN1
  void check_constraints();

  // retorna um ponteiro para a instância do tipo de dados
  T * _get_data();
};

#include <asn1++/asn1-datatype-impl.h>

#endif
