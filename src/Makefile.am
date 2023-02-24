## Process this file with automake to produce Makefile.in

## Created by Anjuta


uidir = $(pkgdatadir)/ui
ui_DATA = covcrav.ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(COVCRAV_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g -lm

bin_PROGRAMS = covcrav

covcrav_SOURCES = \
	main.c \
	rhw.c \
	rhw.h \
	link.c \
	link.h \
	list.h \
	itsnet_types.h \
	itsnet_header.h \
	its_btp_types.h \
	hmi.c \
	hmi.h \
	distance.c \
	distance.h \
	denm.c \
	denm.h \
	common.h \
	callbacks.c \
	callbacks.h \
	util.c \
	util.h


covcrav_LDFLAGS = \
	-Wl,--export-dynamic

covcrav_LDADD = $(COVCRAV_LIBS)




EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

