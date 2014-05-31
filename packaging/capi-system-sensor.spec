Name:       capi-system-sensor
Summary:    A Sensor library in TIZEN C API
Version: 0.1.17
Release:    10
VCS:        framework/api/sensor#submit/master/20130801.121618-2-g869ffbd03f17e99a13d563b3504a92808213ba12
Group:      TO_BE/FILLED_IN
License:    Apache 2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(sensor)
BuildRequires:  pkgconfig(capi-base-common)
Requires(post): /sbin/ldconfig  
Requires(postun): /sbin/ldconfig

%description


%package devel
Summary:  A Sensor library in TIZEN C API (Development)
Group:    TO_BE/FILLED_IN
Requires: %{name} = %{version}-%{release}

%description devel



%prep
%setup -q


%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER}


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
/usr/share/license/%{name}

%files devel
%{_includedir}/system/sensors.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-system-sensor.so

