# Top-level build Makefile

TOPTARGETS := all clean distclean

PROJ := glib_gio glibmm_giomm

$(TOPTARGETS): $(PROJ)
$(PROJ):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: all $(TOPTARGETS) $(PROJ)


