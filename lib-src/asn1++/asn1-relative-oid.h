#ifndef ASN1ROID_H
#define ASN1ROID_H

#include <RELATIVE-OID.h>

// Classe para auxiliar o acesso e modificação de RELATIVE OID (um caso especial de OID)
// Tem mesmas operações que ASN1Oid
class ASN1RelativeOid : public ASN1Oid {
 public:
  // Construtor: parâmetro é um RELATIVE OID (ROID)
  ASN1RelativeOid(RELATIVE_OID_t & oid);

  // Construtor: cria automaticamente o OID encapsulado
  ASN1RelativeOid();

  virtual ~ASN1RelativeOid() {}

  // Operador de atribuição: facilita a definição do ROID por meio de uma string
  virtual ASN1RelativeOid & operator=(const string & oid);
 protected:
  virtual int get_arcs(OBJECT_IDENTIFIER_t *oid,
        void *arcs, unsigned int type_size, unsigned int slots) const;
  virtual int set_arcs(OBJECT_IDENTIFIER_t *oid,
        void *arcs, unsigned int type_size, unsigned int slots);
};

#endif
