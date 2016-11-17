#ifndef ASN1_PARSER_ATIVO_H
#define ASN1_PARSER_ATIVO_H

#include <asn1++/asn1++.h>

#include<BoolList.h>
#include<Tipo2.h>
#include<Tipo1.h>
#include<Ativo.h>
#include<IntList.h>

class TTipo2 : public ASN1DataType<Tipo2_t> {
 public:
 private:
  ASN1Sequence<BOOLEAN_t> * m_id;
  ASN1String * m_nome;
 public:
  TTipo2() : ASN1DataType<Tipo2_t>(&asn_DEF_Tipo2) {
    init();
  }
  TTipo2(Tipo2_t * ptr) : ASN1DataType<Tipo2_t>(&asn_DEF_Tipo2, ptr) {
    destroy = false;
    init();
  }
  TTipo2(const TTipo2 & o) : ASN1DataType<Tipo2_t>(&asn_DEF_Tipo2, o.pkt) {
    init();
    destroy = false;
  }
  void init() {
    m_id = new ASN1Sequence<BOOLEAN_t>(&pkt->id);
    m_nome = new ASN1String(pkt->nome);
  }
  virtual ~TTipo2() {
    delete m_id;
    delete m_nome;
  }
  void get_id(vector<bool> & v) {
    for (ASN1Sequence<BOOLEAN_t>::iterator it=m_id->begin(); it != m_id->end(); it++) {
      v.push_back(*it);
    }
  }
  void set_id(vector<bool> & v) {
    m_id->do_empty();
    for (vector<bool>::iterator it=v.begin(); it != v.end(); it++) m_id->add(*it);
  }
  string get_nome() { return m_nome->str();}
  void set_nome(const string & arg) { *m_nome = arg;}
  class DerSerializer : public DERSerializer<Tipo2_t> {
  public:
    DerSerializer(ostream & out) : DERSerializer<Tipo2_t>(&asn_DEF_Tipo2, out) {}
    ~DerSerializer() {}
    ssize_t serialize(TTipo2 & pkt) {DERSerializer<Tipo2_t>::serialize(pkt);}
  };
  class DerDeserializer : public DERDeserializer<Tipo2_t> {
  public:
    DerDeserializer(istream & inp) : DERDeserializer<Tipo2_t>(&asn_DEF_Tipo2, inp) {}
    ~DerDeserializer() {}
    TTipo2 * deserialize() {
      ASN1DataType<Tipo2> * p = DERDeserializer<Tipo2_t>::deserialize();
      return get_obj(p);
    }
    TTipo2 * scan() {
      ASN1DataType<Tipo2> * p = DERDeserializer<Tipo2_t>::scan();
      return get_obj(p);
    }
 private:
  TTipo2 * get_obj(ASN1DataType<Tipo2_t> * p) {
      TTipo2 * obj = new TTipo2(p->_get_data());
      p->set_destroy(false);
      obj->set_destroy(true);
      delete p;
      return obj;
    }
  };
  class XerSerializer : public XERSerializer<Tipo2_t> {
  public:
    XerSerializer(ostream & out) : XERSerializer<Tipo2_t>(&asn_DEF_Tipo2, out) {}
    ~XerSerializer() {}
    ssize_t serialize(TTipo2 & pkt) {XERSerializer<Tipo2_t>::serialize(pkt);}
  };
  class XerDeserializer : public XERDeserializer<Tipo2_t> {
  public:
    XerDeserializer(istream & inp) : XERDeserializer<Tipo2_t>(&asn_DEF_Tipo2, inp) {}
    ~XerDeserializer() {}
    TTipo2 * deserialize() {
      ASN1DataType<Tipo2> * p = XERDeserializer<Tipo2_t>::deserialize();
      return get_obj(p);
    }
    TTipo2 * scan() {
      ASN1DataType<Tipo2> * p = XERDeserializer<Tipo2_t>::scan();
      return get_obj(p);
    }
 private:
  TTipo2 * get_obj(ASN1DataType<Tipo2_t> * p) {
      TTipo2 * obj = new TTipo2(p->_get_data());
      p->set_destroy(false);
      obj->set_destroy(true);
      delete p;
      return obj;
    }
  };
};

class TTipo1 : public ASN1DataType<Tipo1_t> {
 public:
 private:
  ASN1Sequence<long> * m_id;
  ASN1String * m_nome;
 public:
  TTipo1() : ASN1DataType<Tipo1_t>(&asn_DEF_Tipo1) {
    init();
  }
  TTipo1(Tipo1_t * ptr) : ASN1DataType<Tipo1_t>(&asn_DEF_Tipo1, ptr) {
    destroy = false;
    init();
  }
  TTipo1(const TTipo1 & o) : ASN1DataType<Tipo1_t>(&asn_DEF_Tipo1, o.pkt) {
    init();
    destroy = false;
  }
  void init() {
    m_id = new ASN1Sequence<long>(&pkt->id);
    m_nome = new ASN1String(pkt->nome);
  }
  virtual ~TTipo1() {
    delete m_id;
    delete m_nome;
  }
  void get_id(vector<long> & v) {
    for (ASN1Sequence<long>::iterator it=m_id->begin(); it != m_id->end(); it++) {
      v.push_back(*it);
    }
  }
  void set_id(vector<long> & v) {
    m_id->do_empty();
    for (vector<long>::iterator it=v.begin(); it != v.end(); it++) m_id->add(*it);
  }
  string get_nome() { return m_nome->str();}
  void set_nome(const string & arg) { *m_nome = arg;}
  class DerSerializer : public DERSerializer<Tipo1_t> {
  public:
    DerSerializer(ostream & out) : DERSerializer<Tipo1_t>(&asn_DEF_Tipo1, out) {}
    ~DerSerializer() {}
    ssize_t serialize(TTipo1 & pkt) {DERSerializer<Tipo1_t>::serialize(pkt);}
  };
  class DerDeserializer : public DERDeserializer<Tipo1_t> {
  public:
    DerDeserializer(istream & inp) : DERDeserializer<Tipo1_t>(&asn_DEF_Tipo1, inp) {}
    ~DerDeserializer() {}
    TTipo1 * deserialize() {
      ASN1DataType<Tipo1> * p = DERDeserializer<Tipo1_t>::deserialize();
      return get_obj(p);
    }
    TTipo1 * scan() {
      ASN1DataType<Tipo1> * p = DERDeserializer<Tipo1_t>::scan();
      return get_obj(p);
    }
 private:
  TTipo1 * get_obj(ASN1DataType<Tipo1_t> * p) {
      TTipo1 * obj = new TTipo1(p->_get_data());
      p->set_destroy(false);
      obj->set_destroy(true);
      delete p;
      return obj;
    }
  };
  class XerSerializer : public XERSerializer<Tipo1_t> {
  public:
    XerSerializer(ostream & out) : XERSerializer<Tipo1_t>(&asn_DEF_Tipo1, out) {}
    ~XerSerializer() {}
    ssize_t serialize(TTipo1 & pkt) {XERSerializer<Tipo1_t>::serialize(pkt);}
  };
  class XerDeserializer : public XERDeserializer<Tipo1_t> {
  public:
    XerDeserializer(istream & inp) : XERDeserializer<Tipo1_t>(&asn_DEF_Tipo1, inp) {}
    ~XerDeserializer() {}
    TTipo1 * deserialize() {
      ASN1DataType<Tipo1> * p = XERDeserializer<Tipo1_t>::deserialize();
      return get_obj(p);
    }
    TTipo1 * scan() {
      ASN1DataType<Tipo1> * p = XERDeserializer<Tipo1_t>::scan();
      return get_obj(p);
    }
 private:
  TTipo1 * get_obj(ASN1DataType<Tipo1_t> * p) {
      TTipo1 * obj = new TTipo1(p->_get_data());
      p->set_destroy(false);
      obj->set_destroy(true);
      delete p;
      return obj;
    }
  };
};

class TAtivo : public ASN1DataType<Ativo_t> {
 public:
  class Choice_id {
   private:
    typename Ativo_t::id * ptr;
    void check(id_PR attr) {
      if (ptr->present == id_PR_NOTHING) ptr->present = attr;
      if (ptr->present != attr) throw -1;
    }
   public:
    Choice_id(typename Ativo_t::id & rec) : ptr(&rec) {
    }
    ~Choice_id() {}
    id_PR get_choice() { return ptr->present;}
    void set_t2() { ptr->present = id_PR_t2; }
    void set_t2(const TTipo2 & arg) {
      ptr->present = id_PR_t2;
    }
    TTipo2 get_t2() {
      check(id_PR_t2);
      TTipo2 pld(&ptr->choice.t2);
      pld.set_destroy(false);
      return pld;
    }
    void set_t1() { ptr->present = id_PR_t1; }
    void set_t1(const TTipo1 & arg) {
      ptr->present = id_PR_t1;
    }
    TTipo1 get_t1() {
      check(id_PR_t1);
      TTipo1 pld(&ptr->choice.t1);
      pld.set_destroy(false);
      return pld;
    }
  };

 private:
  ASN1String * m_horario;
  ASN1String * m_data;
  Choice_id * m_id;
 public:
  TAtivo() : ASN1DataType<Ativo_t>(&asn_DEF_Ativo) {
    init();
  }
  TAtivo(Ativo_t * ptr) : ASN1DataType<Ativo_t>(&asn_DEF_Ativo, ptr) {
    destroy = false;
    init();
  }
  TAtivo(const TAtivo & o) : ASN1DataType<Ativo_t>(&asn_DEF_Ativo, o.pkt) {
    init();
    destroy = false;
  }
  void init() {
    m_horario = new ASN1String(pkt->horario);
    m_data = new ASN1String(pkt->data);
    m_id = new Choice_id(pkt->id);
  }
  virtual ~TAtivo() {
    delete m_horario;
    delete m_data;
    delete m_id;
  }
  string get_horario() { return m_horario->str();}
  void set_horario(const string & arg) { *m_horario = arg;}
  string get_data() { return m_data->str();}
  void set_data(const string & arg) { *m_data = arg;}
  Choice_id & get_id() { return *m_id;}
  long get_valor() { return pkt->valor;}
  void set_valor(long arg) { pkt->valor = arg;}
  class DerSerializer : public DERSerializer<Ativo_t> {
  public:
    DerSerializer(ostream & out) : DERSerializer<Ativo_t>(&asn_DEF_Ativo, out) {}
    ~DerSerializer() {}
    ssize_t serialize(TAtivo & pkt) {DERSerializer<Ativo_t>::serialize(pkt);}
  };
  class DerDeserializer : public DERDeserializer<Ativo_t> {
  public:
    DerDeserializer(istream & inp) : DERDeserializer<Ativo_t>(&asn_DEF_Ativo, inp) {}
    ~DerDeserializer() {}
    TAtivo * deserialize() {
      ASN1DataType<Ativo> * p = DERDeserializer<Ativo_t>::deserialize();
      return get_obj(p);
    }
    TAtivo * scan() {
      ASN1DataType<Ativo> * p = DERDeserializer<Ativo_t>::scan();
      return get_obj(p);
    }
 private:
  TAtivo * get_obj(ASN1DataType<Ativo_t> * p) {
      TAtivo * obj = new TAtivo(p->_get_data());
      p->set_destroy(false);
      obj->set_destroy(true);
      delete p;
      return obj;
    }
  };
  class XerSerializer : public XERSerializer<Ativo_t> {
  public:
    XerSerializer(ostream & out) : XERSerializer<Ativo_t>(&asn_DEF_Ativo, out) {}
    ~XerSerializer() {}
    ssize_t serialize(TAtivo & pkt) {XERSerializer<Ativo_t>::serialize(pkt);}
  };
  class XerDeserializer : public XERDeserializer<Ativo_t> {
  public:
    XerDeserializer(istream & inp) : XERDeserializer<Ativo_t>(&asn_DEF_Ativo, inp) {}
    ~XerDeserializer() {}
    TAtivo * deserialize() {
      ASN1DataType<Ativo> * p = XERDeserializer<Ativo_t>::deserialize();
      return get_obj(p);
    }
    TAtivo * scan() {
      ASN1DataType<Ativo> * p = XERDeserializer<Ativo_t>::scan();
      return get_obj(p);
    }
 private:
  TAtivo * get_obj(ASN1DataType<Ativo_t> * p) {
      TAtivo * obj = new TAtivo(p->_get_data());
      p->set_destroy(false);
      obj->set_destroy(true);
      delete p;
      return obj;
    }
  };
};

#endif
