#ifndef ASN1CODEC_H
#define ASN1CODEC_H

#include <iostream>

using namespace std;

#include <asn_application.h>
#include <asn1++/asn1-datatype.h>

// Serializador para codificar uma estrutura de dados
template <typename T> class Serializer {
 protected:
  asn_TYPE_descriptor_t * DESC;
  ostream & out;
 public:
  // Construtor: parâmetro "desc" é um descritor de tipo de dados e "arq" é uma stream
  // de saída
  Serializer(asn_TYPE_descriptor_t * desc, ostream & arq);
  virtual ~Serializer() {}

  // codifica a estrutura de dados "pkt"
  virtual ssize_t serialize(ASN1DataType<T> & pkt);
 protected:
  virtual asn_enc_rval_t encode(ASN1DataType<T> & pkt) = 0;
  static int write_stream(const void *buffer, size_t size, void * ptr) {

    ostream * arq = (ostream *)ptr;
    arq->write((char*)buffer, size);
    arq->flush();
    return size;
  }
};

// Decodificador genérico de estrutura de dados ASN1
template <typename T> class Deserializer {
 protected:
  asn_TYPE_descriptor_t * DESC;
  istream & inp;
 public:
  // Construtor: parâmetro "desc" é um descritor de tipo de dados e "arq" é uma stream
  // de entrada  
  Deserializer(asn_TYPE_descriptor_t * desc, istream & arq);
  virtual ~Deserializer() {}

  // Decodifica uma estrutura de dados, retornando um ponteiro para estrutura extraída.
  // Se não conseguir decodificar, retorna NULL
  virtual ASN1DataType<T> * deserialize();

  // Percorre a stream de entrada até conseguir decodificar uma estrututura de dados. Se
  // chegar ao fim da stream e não conseguir decodificar, retorna NULL
  ASN1DataType<T> * scan();

  protected:
    char * buffer;
    int bufsize;
    int cnt;

    virtual T * decode(const void *buffer, size_t buf_size, asn_dec_rval_t & rval) = 0;
};

// Codificador DER ... segue mesma interface de Serializer
template <typename T> class DERSerializer : public Serializer<T> {
 public:
  DERSerializer(asn_TYPE_descriptor_t * desc, ostream & arq);
 protected:
  virtual asn_enc_rval_t encode(ASN1DataType<T> & pkt);
};

// Codificador XER (XML) ... segue mesma interface de Serializer
template <typename T> class XERSerializer : public Serializer<T> {
 private:
  xer_encoder_flags_e mode;
 public:
  XERSerializer(asn_TYPE_descriptor_t * desc, ostream & arq);

  // Construtor em que se pode escolher o modo de codificação XER:
  //   XER_F_BASIC
  //   XER_F_CANONICAL
  XERSerializer(asn_TYPE_descriptor_t * desc, ostream & arq, xer_encoder_flags_e amode);
 protected:
  virtual asn_enc_rval_t encode(ASN1DataType<T> & pkt);
};

// Decodificador DER
template <typename T> class DERDeserializer : public Deserializer<T> {
 public:
  DERDeserializer(asn_TYPE_descriptor_t * desc, istream & arq);
 protected:
  virtual T * decode(const void *buffer, size_t buf_size, asn_dec_rval_t & rval);
};

// Decodificador XER
template <typename T> class XERDeserializer : public Deserializer<T> {
 public:
  XERDeserializer(asn_TYPE_descriptor_t * desc, istream & arq);
 protected:
  virtual T * decode(const void *buffer, size_t buf_size, asn_dec_rval_t & rval);
};

#include <asn1++/asn1-codec-impl.h>

#endif
