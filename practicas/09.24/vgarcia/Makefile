PKG = mipaquete
VERSION = 0.3.1
PKGDIR = ipk
IPKDEST = $(PKGDIR)/$(PKG)_$(VERSION).ipk

ipk:
	mkdir -p $(PKGDIR)/build/$(PKG)
	cp principal $(PKGDIR)/build/$(PKG)
	tar czvf control.tar.gz control
	cd $(PKGDIR); tar czvf ../data.tar.gz .; cd ..
	echo 2.0 > debian-binary
	ar r $(PKG).ipk control.tar.gz data.tar.gz debian-binary

clean-ipk:
	rm -f control.tar.gz data.tar.gz


