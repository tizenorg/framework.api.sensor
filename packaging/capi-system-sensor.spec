Name:       capi-system-sensor
Summary:    A Sensor library in TIZEN C API
Version:    0.1.17
Release:    1
Group:      framework/system
License:    Apache 2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(sensor)
BuildRequires:  pkgconfig(capi-base-common)

%description


%package devel
Summary:  A Sensor library in TIZEN C API (Development)
Group:    framework/system
Requires: %{name} = %{version}-%{release}

%description devel



%prep
%setup -q


%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER}


make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

mkdir -p %{buildroot}/usr/share/license
cp LICENSE %{buildroot}/usr/share/license/%{name}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest capi-system-sensor.manifest
%{_libdir}/libcapi-system-sensor.so.*
%{_datadir}/license/%{name}

%files devel
%{_includedir}/system/sensors.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-system-sensor.so
