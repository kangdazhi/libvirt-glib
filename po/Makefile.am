DOMAIN = $(PACKAGE_NAME)
COPYRIGHT_HOLDER = The Libvirt authors
MSGID_BUGS_ADDRESS = https://libvirt.org/bugs.html

LANGS := \
	ca cs de en_GB es fi \
	fr hi ja pl pt_BR ru \
	tr uk


POTFILE_DEPS := $(shell $(SED) 's,^,$(top_srcdir)/,' $(srcdir)/POTFILES)
POTFILE := $(srcdir)/$(DOMAIN).pot
POFILES := $(LANGS:%=$(srcdir)/%.po)
GMOFILES := $(LANGS:%=$(srcdir)/%.gmo)

MAINTAINERCLEANFILES = $(POTFILE) $(POFILES) $(GMOFILES)

EXTRA_DIST = \
	POTFILES \
	$(POTFILE) \
	$(POFILES) \
	$(GMOFILES)

if HAVE_GNU_GETTEXT_TOOLS

XGETTEXT_ARGS = \
	--default-domain=$(DOMAIN) \
	--from-code=utf-8 \
	--add-comments=TRANSLATORS: \
        --keyword=_ --keyword=N_ \
	--copyright-holder='$(COPYRIGHT_HOLDER)' \
	--package-name="$(PACKAGE_NAME)" \
	--package-version="$(PACKAGE_VERSION)" \
	--msgid-bugs-address="$(MSGID_BUGS_ADDRESS)" \
	--directory=$(top_srcdir) \
	$(NULL)

SED_PO_FIXUP_ARGS = \
       -e "s|text/plain; charset=CHARSET|text/plain; charset=UTF-8|g" \
       -e "s|SOME DESCRIPTIVE TITLE|Libvirt package strings|g" \
       -e "s|Copyright (C) YEAR|Copyright (C) $$(date +'%Y')|" \
       $(NULL)

update-po: $(POFILES)

update-gmo: $(GMOFILES)

update-mini-po: $(POTFILE)
	for lang in $(LANGS); do \
	  echo "Minimizing $$lang content" && \
	  $(MSGMERGE) --no-location --no-fuzzy-matching --sort-output \
	    $(srcdir)/$$lang.po $(POTFILE) | \
	  $(SED) $(SED_PO_FIXUP_ARGS) | \
	  $(PERL) $(top_srcdir)/build-aux/minimize-po.pl > \
	    $(srcdir)/$$lang.mini.po ; \
	done

push-pot: $(POTFILE)
	wlc upload --method replace -i libvirt-glib.pot libvirt/libvirt-glib/en

pull-po: $(POTFILE) check-new-langs
	@for lang in $(LANGS); do \
	  echo "Downloading $$lang" && \
	  wlc download -o  $$lang.po libvirt/libvirt-glib/$$lang ; \
	done
	$(MAKE) update-mini-po
	$(MAKE) update-gmo

check-new-langs:
	@for po in `wlc ls libvirt/libvirt-glib | \
	    grep filename | grep -v 'en.po' | \
	    sed -e 's/filename: //' -e 's/.po/.mini.po/'` ; \
	do \
	  if ! test -f "$$po" ; \
	  then \
	    echo "New language $$po in weblate" && exit 1; \
	  fi ; \
	done

$(POTFILE): POTFILES $(POTFILE_DEPS)
	$(XGETTEXT) -o $@-t $(XGETTEXT_ARGS) \
	  --files-from=$(abs_srcdir)/POTFILES
	$(SED) $(SED_PO_FIXUP_ARGS) < $@-t > $@
	rm -f $@-t

$(srcdir)/%.po: $(srcdir)/%.mini.po $(POTFILE)
	$(MSGMERGE) --no-fuzzy-matching $< $(POTFILE) | \
	  $(SED) $(SED_PO_FIXUP_ARGS) > $@

$(srcdir)/%.gmo: $(srcdir)/%.po
	rm -f $@ $@-t
	$(MSGFMT) -c -o $@-t $<
	mv $@-t $@

.PRECIOUS: $(POTFILE) $(POFILES)

endif HAVE_GNU_GETTEXT_TOOLS

if ENABLE_NLS

# Cannot use 'localedir' since this conflicts with autoconf.
langinstdir = $(datadir)/locale

install-data-hook: $(GMOFILES)
	mkdir -p $(DESTDIR)$(langinstdir)
	for lang in $(LANGS); do \
	  d=$(DESTDIR)$(langinstdir)/$$lang/LC_MESSAGES; \
	  mkdir -p $$d; \
	  install -m 0644 $(srcdir)/$$lang.gmo $$d/$(DOMAIN).mo; \
	done

uninstall-hook:
	for lang in $(LANGS); do \
	  d=$(DESTDIR)$(langinstdir)/$$lang/LC_MESSAGES; \
	  rm -f $$d/$(DOMAIN).mo; \
	done

endif ENABLE_NLS
