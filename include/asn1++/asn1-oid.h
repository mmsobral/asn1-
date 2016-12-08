#ifndef ASN1OID_H
#define ASN1OID_H

#include <OBJECT_IDENTIFIER.h>
#include <string>

using namespace std;

// Classe para auxiliar o acesso e modificação de OBJECT IDENTIFIER
class ASN1Oid {
 private:
  OBJECT_IDENTIFIER_t * ptr;
  bool external;
 public:
  // Construtor: o parâmetro é um OBJECT IDENTIFIER
  ASN1Oid(OBJECT_IDENTIFIER_t & oid);
  ASN1Oid(const ASN1Oid & oid);
  ASN1Oid(const string & oid);

  // Construtor: cria automaticamente o OID encapsulado
  ASN1Oid();

  virtual ~ASN1Oid();

  // Operador de atribuição: facilita a definição do OID por meio de uma string (ex: "1.3.6.4")
  virtual ASN1Oid & operator=(const string & oid);
  virtual ASN1Oid & operator=(const ASN1Oid & oid);

  // retorna o valor do OID como uma string
  string str() const;

  // obtem o prefixo deste OID N níveis acima
  void get_prefix(ASN1Oid & oid, unsigned int N) const;

  // obtem o prefixo deste OID um nível acima
  void get_prefix(ASN1Oid & oid) const;

  // Operador de concatenação, que posibilita concatenar OIDs
  virtual ASN1Oid & operator+=(const ASN1Oid & other);
  virtual ASN1Oid & operator+=(const string & oid);

  // retorna true se o outro OID for um prefixo deste OID
  bool operator>(const ASN1Oid & other) const;

  // retorna true se este OID for um prefixo do outro OID
  bool operator<(const ASN1Oid & other) const;

  // retorna true se este OID for igual ao outro OID
  bool operator==(const ASN1Oid & other) const;

  // Iterador: possibilita o acesso sequencial a cada número do OID
  class iterator {
    friend class ASN1Oid;
    private:
     int pos;
     long *arcs;
     int len;
    public:
      iterator(const ASN1Oid & ptr);
      iterator();
      iterator(const iterator & it);
      ~iterator();
      iterator& operator++();
      iterator operator++(int);
      long& operator*() const;
      bool operator==(const iterator &it) const;
      bool operator!=(const iterator &it) const;
  };  
  iterator begin() const;
  iterator end() const;
 protected:
  virtual int get_arcs(OBJECT_IDENTIFIER_t *oid,
        void *arcs, unsigned int type_size, unsigned int slots) const;
  virtual int set_arcs(OBJECT_IDENTIFIER_t *oid,
        void *arcs, unsigned int type_size, unsigned int slots);
  void fromString(const string & oid);
};

#endif
