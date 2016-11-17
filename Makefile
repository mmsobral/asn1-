all:
	make -C build all

%:
	make -C build $@

build: Makefile.build
	@if [ ! -d build ]; then mkdir -p build; cp Makefile.build build/Makefile; touch build/Makefile.objs; fi
	@make -C build asn1
	@echo ""
	@echo Preparou para a compilação: compilou a especificação ASN1
	@echo ""
	@echo Para realizar a compilação do seu programa, execute \"make all\"
	@echo ""


