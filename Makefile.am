
##
## Toplevel Makefile.am
##

ACLOCAL_AMFLAGS = -I m4

SUBDIRS		= m4 external doc include lib src test

EXTRA_DIST	= autogen.sh TODO

pkgconfigdir    = $(libdir)/pkgconfig
pkgconfig_DATA  = libbitc.pc

pkg-deb: dist
	- rm -rf $(distdir)
	$(MKDIR_P) $(distdir)
	mv $(distdir).tar.gz $(distdir)/$(PACKAGE)_$(VERSION).orig.tar.gz

	tar --directory $(distdir)/ \
         -xf $(distdir)/$(PACKAGE)_$(VERSION).orig.tar.gz

	cp -r $(top_srcdir)/contrib/debian $(distdir)/$(PACKAGE)-$(VERSION)/
	cd $(distdir)/$(PACKAGE)-$(VERSION)/; \
          ./configure; \
          dpkg-buildpackage -us -uc -rfakeroot; \
          mv $(abs_srcdir)/$(distdir)/*.deb $(abs_srcdir)

	$(am__post_remove_distdir)

pkg-rpm: dist
	- rm -rf $(distdir)
	$(MKDIR_P) $(distdir)/rpmbuild/{RPMS,SRPMS,BUILD,SOURCES,SPECS}

	cp -r $(top_srcdir)/contrib/rpmbuild $(distdir)
	mv $(distdir).tar.gz $(distdir)/rpmbuild/SOURCES/
	rpmbuild --nodeps --define="_topdir $(abs_srcdir)/$(distdir)/rpmbuild" -ba $(distdir)/rpmbuild/SPECS/libbitc.spec
	mv $(abs_srcdir)/$(distdir)/rpmbuild/RPMS/*/*.rpm $(abs_srcdir)

	$(am__post_remove_distdir)

pkg-bin:
	- rm -rf $(distdir)
	make DESTDIR=$(abs_srcdir)/$(distdir) install
	cd $(distdir); \
          tar zcvf $(abs_srcdir)/$(distdir)-$(tag_os).tar.gz `find . -type f -print`

	$(am__post_remove_distdir)
