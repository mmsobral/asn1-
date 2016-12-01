#ifndef ASN1DATATYPE_IMPL_H
#define ASN1DATATYPE_IMPL_H

#include <strings.h>

template <typename T>  ASN1DataType<T>::ASN1DataType(asn_TYPE_descriptor_t * desc) : DESC(desc) {
  pkt = new T;
  bzero(pkt, sizeof(*pkt));
  destroy = true;
}

template <typename T>  ASN1DataType<T>::ASN1DataType(asn_TYPE_descriptor_t * desc, T * apkt) : DESC(desc), pkt(apkt) { destroy = true; }

template <typename T>  ASN1DataType<T>::~ASN1DataType() {
  if (destroy) DESC->free_struct(DESC, pkt, 0);
}

template <typename T> void ASN1DataType<T>::set_destroy(bool val) {
  destroy = val;
}

template <typename T> T * ASN1DataType<T>::_get_data() { return pkt;}

template <typename T>  asn_TYPE_descriptor_t * ASN1DataType<T>::get_desc() { return DESC;}

template <typename T> void ASN1DataType<T>::show() const {
  asn_fprint(stdout, DESC, (void*)pkt);
}

template <typename T> void ASN1DataType<T>::check_constraints() {
  char errbuf[128];
  size_t len = sizeof(errbuf);
  if (asn_check_constraints(DESC,pkt, errbuf, &len)) throw -1;
}
  
#endif
