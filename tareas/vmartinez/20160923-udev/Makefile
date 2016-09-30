SCRIPT=mDevice.sh
DESTDIR=/root/scripts/
RULESDIR=/etc/udev/rules.d/
RULE=83-victormtz-usb.rules

all: install

install: $(SCRIPT)
	mkdir -p $(DESTDIR)
	cp $(SCRIPT) $(DESTDIR)
	cp $(RULE) $(RULESDIR)

uninstall:
	-rm $(DESTDIR)$(SCRIPT)
	-rm $(RULESDIR)$(RULE)
	-rmdir $(DESTDIR)
