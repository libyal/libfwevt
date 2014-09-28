Name: libfwevt
Version: 20140928
Release: 1
Summary: Library to support the Object Linking and Embedding (OLE) data types
Group: System Environment/Libraries
License: LGPL
Source: %{name}-%{version}.tar.gz
URL: https://github.com/libyal/libfwevt/
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
         
         

%description
libfwevt is a library to support the Object Linking and Embedding (OLE) data types

%package devel
Summary: Header files and libraries for developing applications for libfwevt
Group: Development/Libraries
Requires: libfwevt = %{version}-%{release}

%description devel
Header files and libraries for developing applications for libfwevt.

%prep
%setup -q

%build
%configure --prefix=/usr --libdir=%{_libdir} --mandir=%{_mandir}
make %{?_smp_mflags}

%install
rm -rf ${RPM_BUILD_ROOT}
make DESTDIR=${RPM_BUILD_ROOT} install

%clean
rm -rf ${RPM_BUILD_ROOT}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(644,root,root,755)
%doc AUTHORS COPYING NEWS README
%attr(755,root,root) %{_libdir}/*.so.*

%files devel
%defattr(644,root,root,755)
%doc AUTHORS COPYING NEWS README ChangeLog
%{_libdir}/*.a
%{_libdir}/*.la
%{_libdir}/*.so
%{_libdir}/pkgconfig/libfwevt.pc
%{_includedir}/*
%{_mandir}/man3/*

%changelog
* Sun Sep 28 2014 Joachim Metz <joachim.metz@gmail.com> 20140928-1
- Auto-generated

