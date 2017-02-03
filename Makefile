CXXFLAGS:= -O3

zeromemory:

install: zeromemory
	install -m 755 zeromemory /usr/sbin/
	-install -m 644 zeromemory-presleep.service /etc/systemd/system/
	-systemctl daemon-reload

uninstall:
	-systemctl disable zeromemory-presleep
	$(RM) /etc/systemd/system/zeromemory-presleep.service
	-systemctl daemon-reload
	$(RM) /usr/sbin/zeromemory

.DEFAULT_GOAL := zeromemory

clean:
	$(RM) zeromemory

.PHONY: clean install uninstall
