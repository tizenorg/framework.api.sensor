Name:       capi-system-sensor
Summary:    A Sensor library in TIZEN C API
Version:    0.2.0
Release:    10
Group:      TO_BE/FILLED_IN
License:    Apache-2.0 and PD
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(capi-base-common)

%define BUILD_PROFILE %{?profile}%{!?profile:%{?tizen_profile_name}}

%if "%{?BUILD_PROFILE}" != "tv"
##### Begin: Normal build spec #####


BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(sensor)
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
%if 0%{?tizen_build_binary_release_type_eng}
export CFLAGS+=" -DTIZEN_ENGINEER_MODE"
%endif

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
%{_includedir}/sensor/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-system-sensor.so


##### End: Normal build spec #####
%else
##### Begin: Dummy build spec #####


%description
Native Sensor API (dummy)

%package devel
Summary:  A Sensor library in TIZEN C API (Development)
Group:    System/API
Requires: %{name} = %{version}-%{release}

%description devel
Native Sensor API (dummy)

%prep
%setup -q

%build
cmake ./dummy -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version}

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install
mkdir -p %{buildroot}/%{_datadir}/license
cp LICENSE %{buildroot}/%{_datadir}/license/%{name}

%files
%manifest capi-system-sensor.manifest
%{_datadir}/license/%{name}

%files devel
%manifest capi-system-sensor.manifest
%{_includedir}/sensor/*.h
%{_libdir}/pkgconfig/*.pc


##### End: Dummy build spec #####
%endif
