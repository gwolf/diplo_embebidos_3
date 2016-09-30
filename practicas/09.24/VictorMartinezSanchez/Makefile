FILE = userSearcher.sh
INSTALLDIR = /opt/user-searcher/
IPKNAME = user-searcher


all: clean package

t-control: control
	tar czvf control.tar.gz control

t-data:
	mkdir -p ipk$(INSTALLDIR)
	cp $(FILE) ipk$(INSTALLDIR)
	cd ipk; tar czvf ../data.tar.gz .; cd ..

debian-bin:
	echo 2.0 > debian-binary

package: t-control t-data debian-bin
	ar r $(IPKNAME).ipk control.tar.gz data.tar.gz debian-binary

clean:
	-rm -rf ipk
	-rm *.tar.gz
	-rm *.ipk
	-rm debian-binary



