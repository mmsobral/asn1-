#ifndef ASN1CODEC_IMPL_H
#define ASN1CODEC_IMPL_H

#include <errno.h>
 
template <typename T>  Serializer<T>::Serializer(asn_TYPE_descriptor_t * desc, ostream & arq) : DESC(desc), out(arq) {}

template <typename T> ssize_t Serializer<T>::serialize(ASN1DataType<T> & pkt) {
  asn_enc_rval_t er;  // Encoder return value

  er = encode(pkt);
  if(er.encoded == -1) {
      throw errno;
  } else {
      // Return the number of bytes 
      return er.encoded;
  }
}

/*template <typename T> static int Serializer<T>::write_stream(const void *buffer, size_t size,
        void * ptr) {

  ostream * arq = (ostream *)ptr;
  arq->write((char*)buffer, size);
  arq->flush();
  return size;
}*/

template <typename T>  Deserializer<T>::Deserializer(asn_TYPE_descriptor_t * desc, istream & arq) : DESC(desc), inp(arq) {
  buffer = new char[16];
  bufsize = 16;
  cnt = 0;
}

template <typename T> ASN1DataType<T> * Deserializer<T>::deserialize() {

  while (true) {
    int n = 0;
    if (not inp.eof()) {
      inp.read(buffer+cnt, bufsize-cnt);
      n = inp.gcount();
      cnt += n;
    }
    //cout << n << "," << cnt << "," << bufsize;
    //printf(" %02X %02X\n", (unsigned char)buffer[0], (unsigned char) buffer[1]);


    asn_dec_rval_t rval;

    T * pkt = decode(buffer, cnt, rval);
 
    if(rval.code == RC_OK) {
        ASN1DataType<T> * data = new ASN1DataType<T>(DESC, pkt);
        //cout << cnt << ": " << rval.consumed << endl;
        cnt -= rval.consumed;
        memmove(buffer, buffer+rval.consumed, cnt);
        return data;          /* Decoding succeeded */
    } else {
        /* Free partially decoded struct */
        DESC->free_struct(DESC, pkt, 0);
        pkt = 0;
        if ((rval.code == RC_WMORE) and not inp.eof()) {
          bufsize = bufsize << 1;
          buffer = (char*)realloc((void*)buffer, bufsize);
        } else return NULL;
    }
  }
  return NULL;
}

template <typename T> ASN1DataType<T> * Deserializer<T>::scan() {
  ASN1DataType<T> * data;

  while (true) {
    //cout << cnt << "," << bufsize << endl;
    data = deserialize();
    if (data) return data;
    if (cnt > 0) {
      cnt--;
      memmove(buffer, buffer+1, cnt);
    } else if (inp.eof()) break;
  }
  return NULL;
}

template <typename T>  DERSerializer<T>::DERSerializer(asn_TYPE_descriptor_t * desc, ostream & arq) : Serializer<T>(desc, arq) {}

template <typename T>  asn_enc_rval_t DERSerializer<T>::encode(ASN1DataType<T> & pkt) {
  return der_encode(pkt.get_desc(), pkt._get_data(), this->write_stream, &this->out);
}

template <typename T>  XERSerializer<T>::XERSerializer(asn_TYPE_descriptor_t * desc, ostream & arq) : Serializer<T>(desc, arq), mode(XER_F_BASIC) {}

template <typename T>  XERSerializer<T>::XERSerializer(asn_TYPE_descriptor_t * desc, ostream & arq, xer_encoder_flags_e amode) : Serializer<T>(desc, arq), 
    mode(amode) {}

template <typename T> asn_enc_rval_t XERSerializer<T>::encode(ASN1DataType<T> & pkt) {
  return xer_encode(this->DESC, pkt._get_data(), mode, this->write_stream, &this->out);
}

template <typename T>  DERDeserializer<T>::DERDeserializer(asn_TYPE_descriptor_t * desc, istream & arq) : Deserializer<T>(desc, arq) {}

template <typename T> T* DERDeserializer<T>::decode(const void *buffer, size_t buf_size, asn_dec_rval_t & rval) {
  T *pkt = 0;    /* Note this 0! */

  rval = ber_decode(0,
          this->DESC,
          (void **)&pkt,
          buffer, buf_size);

  return pkt;
} 

template <typename T>  XERDeserializer<T>::XERDeserializer(asn_TYPE_descriptor_t * desc, istream & arq) : Deserializer<T>(desc, arq) {}

template <typename T> T* XERDeserializer<T>::decode(const void *buffer, size_t buf_size, asn_dec_rval_t & rval) {
  T *pkt = 0;    /* Note this 0! */

  rval = xer_decode(0,
          this->DESC,
          (void **)&pkt,
          buffer, buf_size);

  return pkt;
} 

#endif
