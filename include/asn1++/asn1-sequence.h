#ifndef ASN1SEQUENCE
#define ASN1SEQUENCE

#include <asn_SET_OF.h>

// Classe para facilitar o uso de sequências ASN1 (SEQUENCE OF e SET OF)
// Definida como template pois o tipo do dado contido em sequências é genérico
template <typename T> class ASN1Sequence {
 private:
  struct GenSeq {
    A_SET_OF(T) list;
    asn_struct_ctx_t _asn_ctx;
  };
  GenSeq * seq;
 public:
  // Constructor: recebe um ponteiro para um SET OF ou SEQUENCE OF
  ASN1Sequence(void * a_seq);

  ~ASN1Sequence() {}

  // adiciona um dado à sequência
  void add(T val);

  // obtém o dado na posição "pos"
  T& get(int pos) const;

  // esvazia a sequência
  void do_empty();

  // remove o dado da posição "pos"
  void del(int pos);

  // remove o dado da posição "pos" e o destroi
  void del(int pos, bool do_free);

  // retorna o comprimento da sequência
  int len() const;

  // Iterador de sequência
  class iterator {
    private:
     int pos;
     ASN1Sequence<T> * seq;
    public:
      iterator(ASN1Sequence * ptr);
      ~iterator() {}
      iterator& operator++();
      iterator operator++(int);
      T& operator*() const;
      bool operator==(const iterator &it) const;
      bool operator!=(const iterator &it) const;
  };

  // retorna um iterador para o início da sequência
  iterator begin();

  // retorna um, iterador para o fim da sequência (após último dado)
  iterator end() const;
};

#include <asn1++/asn1-sequence-impl.h>

#endif
