#!/usr/bin/python

from Asn1Parser import *

def tokenize(p):
  r = p.tokenize(open(p.conf).read())
  for tok in r:
    print tok.type, tok.value

try:
  arqs = sys.argv[1:]
except:
  print 'Uso: %s arq.asn1 [arq2.asn1 ...]' % sys.argv[0]
  sys.exit(0)

p = ASN1Parser(arq)
p.build()
#tokenize(p)

p.parse()
builder = p.get_builder()
path = builder.build()
print 'Gerou:', path

