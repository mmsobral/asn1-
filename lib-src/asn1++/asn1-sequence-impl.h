#ifndef ASN1SEQUENCE_IMPL_H
#define ASN1SEQUENCE_IMPL_H

template <typename T>  ASN1Sequence<T>::ASN1Sequence(void * a_seq)  {
  seq = (GenSeq*)a_seq;
}

template <typename T> void ASN1Sequence<T>::add(T val) {
  T * ptr = new T;
  *ptr = val;
  asn_set_add((void*)seq, ptr);
}

template <typename T> T& ASN1Sequence<T>::get(int pos) const {
  int n;
     
  if (pos >= seq->list.count) throw -1;
  pos++;
  for (n=0; (pos > 0) && (n < seq->list.size);n++) {
    if (seq->list.array[n] != NULL) pos--; 
  }
  return *seq->list.array[n-1];
}

template <typename T> void ASN1Sequence<T>::do_empty() {
  asn_set_empty(seq);
}

template <typename T> void ASN1Sequence<T>::del(int pos) {
  asn_set_del(seq, pos, 0);
}

template <typename T> void ASN1Sequence<T>::del(int pos, bool do_free) {
  asn_set_del(seq, pos, do_free);
}

template <typename T> int ASN1Sequence<T>::len() const {
  return seq->list.count;
}

template <typename T> typename ASN1Sequence<T>::iterator ASN1Sequence<T>::begin() {
  ASN1Sequence<T>::iterator it(this);

  return it;
}

template <typename T> typename ASN1Sequence<T>::iterator ASN1Sequence<T>::end() const {
  ASN1Sequence<T>::iterator it(NULL);

  return it;
}

template <typename T> ASN1Sequence<T>::iterator::iterator(ASN1Sequence * ptr) : seq(ptr) {
  pos = 0;
}

template <typename T> bool ASN1Sequence<T>::iterator::operator!=(const iterator &it) const {
        return not (*this == it);
} 

template <typename T> T& ASN1Sequence<T>::iterator::operator*() const {
  if (not seq) throw -1;
  return seq->get(pos);
}

template <typename T> typename ASN1Sequence<T>::iterator ASN1Sequence<T>::iterator::operator++(int) {
  ASN1Sequence<T>::iterator novo = *this;
  ++(*this);
  return novo;
}

template <typename T> typename ASN1Sequence<T>::iterator& ASN1Sequence<T>::iterator::operator++() {        
  if (pos < seq->len()) pos++;
  else throw -1;
  if (pos == seq->len()) seq = NULL;
  return *this;
}

template <typename T> bool ASN1Sequence<T>::iterator::operator==(const iterator &it) const {
  if ((seq == NULL) and (it.seq == NULL)) return true;
  bool ok = (pos == it.pos);
  if (ok) ok = (seq == it.seq);
  return ok;
}

#endif
