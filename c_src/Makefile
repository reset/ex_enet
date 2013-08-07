DEPS=../deps

ifndef ENET_VERSION
ENET_VERSION=1.3.8
endif

all: $(DEPS)/enet/.libs/libenet.a

clean:
	if test -e $(DEPS)/enet/Makefile; then \
		cd $(DEPS)/enet; make clean; \
	else \
		true; \
	fi

distclean:
	@rm -rf $(DEPS)

$(DEPS)/enet:
	@mkdir -p $(DEPS)
	@curl http://enet.bespin.org/download/enet-$(ENET_VERSION).tar.gz -o $(DEPS)/enet-$(ENET_VERSION).tar.gz
	@cd $(DEPS) && tar xzvfp enet-$(ENET_VERSION).tar.gz && mv enet-$(ENET_VERSION) enet

$(DEPS)/enet/.libs/libenet.a: $(DEPS)/enet
	@cd $(DEPS)/enet && ./configure && make
