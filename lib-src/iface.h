#include <stdio.h>
#include <errno.h>
#include <iostream>
#include <exception>
#include <cstdlib>
#include "Ativo.h"

using namespace std;

template <typename T> class ASN1Sequence {
 private:
  struct GenSeq {
    A_SET_OF(T) list;
    asn_struct_ctx_t _asn_ctx;
  };
  GenSeq * seq;
 public:
  ASN1Sequence(void * a_seq)  {
    seq = (GenSeq*)a_seq;
  }

  ~ASN1Sequence() {}

  void add(T val) {
    T * ptr = new T;
    *ptr = val;
    asn_set_add((void*)seq, ptr);
  }

  T& get(int pos) {
    int n;
     
    if (pos >= seq->list.count) throw -1;
    pos++;
    for (n=0; (pos > 0) && (n < seq->list.size);n++) {
      if (seq->list.array[n] != NULL) pos--; 
    }
    return *seq->list.array[n-1];
  }

  void do_empty() {
    asn_set_empty(seq);
  }

  void del(int pos) {
    asn_set_del(seq, pos, 0);
  }

  void del(int pos, bool do_free) {
    asn_set_del(seq, pos, do_free);
  }
};

template <typename T> class ASN1DataType  {
 private:
  T * pkt;
  asn_TYPE_descriptor_t * DESC;
 public:
  ASN1DataType(asn_TYPE_descriptor_t * desc) : DESC(desc) {
    pkt = new T;
  }
  ~ASN1DataType() {
    DESC->free_struct(DESC, pkt, 0);
  }
  T * get_data() { return pkt;}
  asn_TYPE_descriptor_t * get_desc() { return DESC;}
  /*T * operator->() {
    return pkt;
  }*/
  void set_string(OCTET_STRING_t * ptr, char * val) {
    OCTET_STRING_fromString(ptr, val);
  }
  char* get_string(OCTET_STRING_t * ptr) {
    char * buffer;

    buffer = new char[ptr->size+1];
    memcpy(buffer, ptr->buf, ptr->size);
    buffer[ptr->size] = 0;
    return buffer;
  }
  void mostreSe() {
    asn_fprint(stdout, DESC, (void*)pkt);
  }
  void check_constraints() {
    char errbuf[128];
    size_t len = sizeof(errbuf);
    if (asn_check_constraints(DESC,pkt, errbuf, &len)) throw -1;
  }
  
  ssize_t der_serialize(FILE *ostream) {
    asn_enc_rval_t er;  // Encoder return value
 
    er = der_encode(DESC, pkt,
        write_stream, ostream);
    if(er.encoded == -1) {
        // Failed to encode the rectangle data.
        fprintf(stderr, "Cannot encode %s: %s\n",
            er.failed_type->name,
            strerror(errno));
        return -1;
    } else {
        // Return the number of bytes 
        return er.encoded;
    }
  }
 private:
  static int write_stream(const void *buffer, size_t size,
        void * ptr) {

    FILE * ostream = (FILE *)ptr;
    fwrite(buffer, size, 1, ostream);
    fflush(ostream);
  }
  
};

template <typename T> class Serializer {
 protected:
  ASN1DataType<T> & pkt;
 public:
  Serializer(ASN1DataType<T> & apkt) : pkt(apkt) {}
  virtual ~Serializer() {}
  virtual asn_enc_rval_t encode(FILE * ostream) = 0;
  ssize_t serialize(FILE *ostream) {
    asn_enc_rval_t er;  // Encoder return value
 
    er = encode(ostream);
    if(er.encoded == -1) {
        throw errno;
    } else {
        // Return the number of bytes 
        return er.encoded;
    }
  }
 protected:
  static int write_stream(const void *buffer, size_t size,
        void * ptr) {

    FILE * ostream = (FILE *)ptr;
    fwrite(buffer, size, 1, ostream);
    fflush(ostream);
  }
};

template <typename T> class DerSerializer : public Serializer<T> {
 public:
  DerSerializer(ASN1DataType<T> & pkt) : Serializer<T>(pkt) {}
  virtual asn_enc_rval_t encode(FILE * ostream) {
    return der_encode(this->pkt.get_desc(), this->pkt.get_data(), this->write_stream, ostream);
  }
};

template <typename T> class BerSerializer : public Serializer<T> {
 public:
  BerSerializer(ASN1DataType<T> & pkt) : Serializer<T>(pkt) {}
  virtual asn_enc_rval_t encode(FILE * ostream) {
    return ber_encode(this->pkt.get_desc(), this->pkt.get_data(), this->write_stream, ostream);
  }
};

template <typename T> class PerSerializer : public Serializer<T> {
 public:
  PerSerializer(ASN1DataType<T> & pkt) : Serializer<T>(pkt) {}
  virtual asn_enc_rval_t encode(FILE * ostream) {
    return per_encode(this->pkt.get_desc(), this->pkt.get_data(), this->write_stream, ostream);
  }
};

