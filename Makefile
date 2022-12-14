#############################################################################
# Makefile for building: main
# Generated by qmake (3.1) (Qt 5.15.2)
# Project:  base_3d_modeling.pro
# Template: app
# Command: /usr/bin/qmake-qt5 -o Makefile base_3d_modeling.pro
#############################################################################

MAKEFILE      = Makefile

EQ            = =

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_OPENGL_LIB -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -O2 -Wall -Wextra -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -pipe -std=c++17 -O2 -Wall -Wextra -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I. -Iinclude -Iapv_mapping/include -Igeometry/include -Ithird_party/nlohmann -I/usr/include/qt5 -I/usr/include/qt5/QtOpenGL -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -Imoc -I/../lib64/qt5/mkspecs/linux-g++
QMAKE         = /usr/bin/qmake-qt5
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
QINSTALL      = /usr/bin/qmake-qt5 -install qinstall
QINSTALL_PROGRAM = /usr/bin/qmake-qt5 -install qinstall -exe
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = main1.0.0
DISTDIR = /home/xinzhan/test/base_3d_modeling/obj/main1.0.0
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS) /usr/lib64/libQt5OpenGL.so /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so -lGL -lpthread   
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = obj/

####### Files

SOURCES       = src/main.cpp \
		src/Module.cpp \
		src/OpenGLView.cpp \
		src/GeometryView.cpp \
		src/GeometryManager.cpp \
		src/GeometryBuilder.cpp \
		src/UnitTest.cpp \
		geometry/src/Cube.cpp \
		geometry/src/Trapezoid.cpp \
		geometry/src/Sphere.cpp \
		geometry/src/Tube.cpp \
		apv_mapping/src/APVMapping.cpp \
		apv_mapping/src/APVStruct.cpp moc/moc_OpenGLView.cpp \
		moc/moc_GeometryView.cpp
OBJECTS       = obj/main.o \
		obj/Module.o \
		obj/OpenGLView.o \
		obj/GeometryView.o \
		obj/GeometryManager.o \
		obj/GeometryBuilder.o \
		obj/UnitTest.o \
		obj/Cube.o \
		obj/Trapezoid.o \
		obj/Sphere.o \
		obj/Tube.o \
		obj/APVMapping.o \
		obj/APVStruct.o \
		obj/moc_OpenGLView.o \
		obj/moc_GeometryView.o
DIST          = /../lib64/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib64/qt5/mkspecs/common/unix.conf \
		/usr/lib64/qt5/mkspecs/common/linux.conf \
		/usr/lib64/qt5/mkspecs/common/sanitize.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib64/qt5/mkspecs/common/g++-base.conf \
		/usr/lib64/qt5/mkspecs/common/g++-unix.conf \
		/../lib64/qt5/mkspecs/qconfig.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_core.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_edid_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_egl_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_fb_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_glx_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_gui.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_input_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_kms_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_network.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_service_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_sql.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_theme_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xkbcommon_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xml.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/../lib64/qt5/mkspecs/features/qt_functions.prf \
		/../lib64/qt5/mkspecs/features/qt_config.prf \
		/../lib64/qt5/mkspecs/linux-g++/qmake.conf \
		/../lib64/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/../lib64/qt5/mkspecs/features/exclusive_builds.prf \
		/../lib64/qt5/mkspecs/features/toolchain.prf \
		/../lib64/qt5/mkspecs/features/default_pre.prf \
		/../lib64/qt5/mkspecs/features/resolve_config.prf \
		/../lib64/qt5/mkspecs/features/default_post.prf \
		/../lib64/qt5/mkspecs/features/warn_on.prf \
		/../lib64/qt5/mkspecs/features/qt.prf \
		/../lib64/qt5/mkspecs/features/resources_functions.prf \
		/../lib64/qt5/mkspecs/features/resources.prf \
		/../lib64/qt5/mkspecs/features/moc.prf \
		/../lib64/qt5/mkspecs/features/unix/opengl.prf \
		/../lib64/qt5/mkspecs/features/uic.prf \
		/../lib64/qt5/mkspecs/features/unix/thread.prf \
		/../lib64/qt5/mkspecs/features/qmake_use.prf \
		/../lib64/qt5/mkspecs/features/file_copies.prf \
		/../lib64/qt5/mkspecs/features/testcase_targets.prf \
		/../lib64/qt5/mkspecs/features/exceptions.prf \
		/../lib64/qt5/mkspecs/features/yacc.prf \
		/../lib64/qt5/mkspecs/features/lex.prf \
		base_3d_modeling.pro include/Module.h \
		include/OpenGLView.h \
		include/GeometryView.h \
		include/GeometryManager.h \
		include/GeometryBuilder.h \
		include/Geometry.h \
		include/UnitTest.h \
		geometry/include/Cube.h \
		geometry/include/Trapezoid.h \
		geometry/include/Sphere.h \
		geometry/include/Tube.h \
		third_party/nlohmann/json.hpp \
		third_party/nlohmann/json_fwd.hpp \
		apv_mapping/include/APVMapping.h \
		apv_mapping/include/APVStruct.h src/main.cpp \
		src/Module.cpp \
		src/OpenGLView.cpp \
		src/GeometryView.cpp \
		src/GeometryManager.cpp \
		src/GeometryBuilder.cpp \
		src/UnitTest.cpp \
		geometry/src/Cube.cpp \
		geometry/src/Trapezoid.cpp \
		geometry/src/Sphere.cpp \
		geometry/src/Tube.cpp \
		apv_mapping/src/APVMapping.cpp \
		apv_mapping/src/APVStruct.cpp
QMAKE_TARGET  = main
DESTDIR       = 
TARGET        = main


first: all
####### Build rules

main:  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: base_3d_modeling.pro /../lib64/qt5/mkspecs/linux-g++/qmake.conf /../lib64/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib64/qt5/mkspecs/common/unix.conf \
		/usr/lib64/qt5/mkspecs/common/linux.conf \
		/usr/lib64/qt5/mkspecs/common/sanitize.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib64/qt5/mkspecs/common/g++-base.conf \
		/usr/lib64/qt5/mkspecs/common/g++-unix.conf \
		/../lib64/qt5/mkspecs/qconfig.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_core.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_edid_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_egl_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_fb_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_glx_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_gui.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_input_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_kms_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_network.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_service_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_sql.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_theme_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xkbcommon_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xml.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/../lib64/qt5/mkspecs/features/qt_functions.prf \
		/../lib64/qt5/mkspecs/features/qt_config.prf \
		/../lib64/qt5/mkspecs/linux-g++/qmake.conf \
		/../lib64/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/../lib64/qt5/mkspecs/features/exclusive_builds.prf \
		/../lib64/qt5/mkspecs/features/toolchain.prf \
		/../lib64/qt5/mkspecs/features/default_pre.prf \
		/../lib64/qt5/mkspecs/features/resolve_config.prf \
		/../lib64/qt5/mkspecs/features/default_post.prf \
		/../lib64/qt5/mkspecs/features/warn_on.prf \
		/../lib64/qt5/mkspecs/features/qt.prf \
		/../lib64/qt5/mkspecs/features/resources_functions.prf \
		/../lib64/qt5/mkspecs/features/resources.prf \
		/../lib64/qt5/mkspecs/features/moc.prf \
		/../lib64/qt5/mkspecs/features/unix/opengl.prf \
		/../lib64/qt5/mkspecs/features/uic.prf \
		/../lib64/qt5/mkspecs/features/unix/thread.prf \
		/../lib64/qt5/mkspecs/features/qmake_use.prf \
		/../lib64/qt5/mkspecs/features/file_copies.prf \
		/../lib64/qt5/mkspecs/features/testcase_targets.prf \
		/../lib64/qt5/mkspecs/features/exceptions.prf \
		/../lib64/qt5/mkspecs/features/yacc.prf \
		/../lib64/qt5/mkspecs/features/lex.prf \
		base_3d_modeling.pro
	$(QMAKE) -o Makefile base_3d_modeling.pro
/../lib64/qt5/mkspecs/features/spec_pre.prf:
/usr/lib64/qt5/mkspecs/common/unix.conf:
/usr/lib64/qt5/mkspecs/common/linux.conf:
/usr/lib64/qt5/mkspecs/common/sanitize.conf:
/usr/lib64/qt5/mkspecs/common/gcc-base.conf:
/usr/lib64/qt5/mkspecs/common/gcc-base-unix.conf:
/usr/lib64/qt5/mkspecs/common/g++-base.conf:
/usr/lib64/qt5/mkspecs/common/g++-unix.conf:
/../lib64/qt5/mkspecs/qconfig.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_concurrent.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_concurrent_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_core.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_core_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_dbus.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_dbus_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_edid_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_egl_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_fb_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_glx_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_gui.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_gui_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_input_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_kms_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_network.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_network_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_opengl.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_opengl_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_printsupport.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_printsupport_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_service_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_sql.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_sql_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_testlib.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_testlib_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_theme_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_widgets.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_widgets_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_xkbcommon_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_xml.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_xml_private.pri:
/../lib64/qt5/mkspecs/features/qt_functions.prf:
/../lib64/qt5/mkspecs/features/qt_config.prf:
/../lib64/qt5/mkspecs/linux-g++/qmake.conf:
/../lib64/qt5/mkspecs/features/spec_post.prf:
.qmake.stash:
/../lib64/qt5/mkspecs/features/exclusive_builds.prf:
/../lib64/qt5/mkspecs/features/toolchain.prf:
/../lib64/qt5/mkspecs/features/default_pre.prf:
/../lib64/qt5/mkspecs/features/resolve_config.prf:
/../lib64/qt5/mkspecs/features/default_post.prf:
/../lib64/qt5/mkspecs/features/warn_on.prf:
/../lib64/qt5/mkspecs/features/qt.prf:
/../lib64/qt5/mkspecs/features/resources_functions.prf:
/../lib64/qt5/mkspecs/features/resources.prf:
/../lib64/qt5/mkspecs/features/moc.prf:
/../lib64/qt5/mkspecs/features/unix/opengl.prf:
/../lib64/qt5/mkspecs/features/uic.prf:
/../lib64/qt5/mkspecs/features/unix/thread.prf:
/../lib64/qt5/mkspecs/features/qmake_use.prf:
/../lib64/qt5/mkspecs/features/file_copies.prf:
/../lib64/qt5/mkspecs/features/testcase_targets.prf:
/../lib64/qt5/mkspecs/features/exceptions.prf:
/../lib64/qt5/mkspecs/features/yacc.prf:
/../lib64/qt5/mkspecs/features/lex.prf:
base_3d_modeling.pro:
qmake: FORCE
	@$(QMAKE) -o Makefile base_3d_modeling.pro

qmake_all: FORCE


all: Makefile main

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/
	$(COPY_FILE) --parents /../lib64/qt5/mkspecs/features/data/dummy.cpp $(DISTDIR)/
	$(COPY_FILE) --parents include/Module.h include/OpenGLView.h include/GeometryView.h include/GeometryManager.h include/GeometryBuilder.h include/Geometry.h include/UnitTest.h geometry/include/Cube.h geometry/include/Trapezoid.h geometry/include/Sphere.h geometry/include/Tube.h third_party/nlohmann/json.hpp third_party/nlohmann/json_fwd.hpp apv_mapping/include/APVMapping.h apv_mapping/include/APVStruct.h $(DISTDIR)/
	$(COPY_FILE) --parents src/main.cpp src/Module.cpp src/OpenGLView.cpp src/GeometryView.cpp src/GeometryManager.cpp src/GeometryBuilder.cpp src/UnitTest.cpp geometry/src/Cube.cpp geometry/src/Trapezoid.cpp geometry/src/Sphere.cpp geometry/src/Tube.cpp apv_mapping/src/APVMapping.cpp apv_mapping/src/APVStruct.cpp $(DISTDIR)/


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) .qmake.stash
	-$(DEL_FILE) Makefile


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_objc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_objc_header_make_all compiler_moc_source_make_all

check: first

benchmark: first

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_moc_predefs_make_all: moc/moc_predefs.h
compiler_moc_predefs_clean:
	-$(DEL_FILE) moc/moc_predefs.h
moc/moc_predefs.h: /../lib64/qt5/mkspecs/features/data/dummy.cpp
	g++ -pipe -std=c++17 -O2 -Wall -Wextra -dM -E -o moc/moc_predefs.h /../lib64/qt5/mkspecs/features/data/dummy.cpp

compiler_moc_header_make_all: moc/moc_OpenGLView.cpp moc/moc_GeometryView.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc/moc_OpenGLView.cpp moc/moc_GeometryView.cpp
moc/moc_OpenGLView.cpp: include/OpenGLView.h \
		moc/moc_predefs.h \
		/../lib64/qt5/bin/moc
	/../lib64/qt5/bin/moc $(DEFINES) --include /home/xinzhan/test/base_3d_modeling/moc/moc_predefs.h -I/../lib64/qt5/mkspecs/linux-g++ -I/home/xinzhan/test/base_3d_modeling -I/home/xinzhan/test/base_3d_modeling/include -I/home/xinzhan/test/base_3d_modeling/apv_mapping/include -I/home/xinzhan/test/base_3d_modeling/geometry/include -I/home/xinzhan/test/base_3d_modeling/third_party/nlohmann -I/usr/include/qt5 -I/usr/include/qt5/QtOpenGL -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -I/usr/include/c++/8 -I/usr/include/c++/8/x86_64-redhat-linux -I/usr/include/c++/8/backward -I/usr/lib/gcc/x86_64-redhat-linux/8/include -I/usr/local/include -I/usr/include include/OpenGLView.h -o moc/moc_OpenGLView.cpp

moc/moc_GeometryView.cpp: include/GeometryView.h \
		moc/moc_predefs.h \
		/../lib64/qt5/bin/moc
	/../lib64/qt5/bin/moc $(DEFINES) --include /home/xinzhan/test/base_3d_modeling/moc/moc_predefs.h -I/../lib64/qt5/mkspecs/linux-g++ -I/home/xinzhan/test/base_3d_modeling -I/home/xinzhan/test/base_3d_modeling/include -I/home/xinzhan/test/base_3d_modeling/apv_mapping/include -I/home/xinzhan/test/base_3d_modeling/geometry/include -I/home/xinzhan/test/base_3d_modeling/third_party/nlohmann -I/usr/include/qt5 -I/usr/include/qt5/QtOpenGL -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -I/usr/include/c++/8 -I/usr/include/c++/8/x86_64-redhat-linux -I/usr/include/c++/8/backward -I/usr/lib/gcc/x86_64-redhat-linux/8/include -I/usr/local/include -I/usr/include include/GeometryView.h -o moc/moc_GeometryView.cpp

compiler_moc_objc_header_make_all:
compiler_moc_objc_header_clean:
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_predefs_clean compiler_moc_header_clean 

####### Compile

obj/main.o: src/main.cpp include/UnitTest.h \
		include/Module.h \
		geometry/include/Cube.h \
		include/GeometryView.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/main.o src/main.cpp

obj/Module.o: src/Module.cpp include/Module.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Module.o src/Module.cpp

obj/OpenGLView.o: src/OpenGLView.cpp include/OpenGLView.h \
		include/Module.h \
		include/GeometryManager.h \
		include/GeometryBuilder.h \
		geometry/include/Cube.h \
		apv_mapping/include/APVMapping.h \
		apv_mapping/include/APVStruct.h \
		third_party/nlohmann/json_fwd.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/OpenGLView.o src/OpenGLView.cpp

obj/GeometryView.o: src/GeometryView.cpp include/GeometryView.h \
		include/OpenGLView.h \
		include/GeometryManager.h \
		include/GeometryBuilder.h \
		include/Module.h \
		geometry/include/Cube.h \
		apv_mapping/include/APVMapping.h \
		apv_mapping/include/APVStruct.h \
		third_party/nlohmann/json_fwd.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/GeometryView.o src/GeometryView.cpp

obj/GeometryManager.o: src/GeometryManager.cpp include/GeometryManager.h \
		include/GeometryBuilder.h \
		include/Module.h \
		geometry/include/Cube.h \
		apv_mapping/include/APVMapping.h \
		apv_mapping/include/APVStruct.h \
		third_party/nlohmann/json_fwd.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/GeometryManager.o src/GeometryManager.cpp

obj/GeometryBuilder.o: src/GeometryBuilder.cpp third_party/nlohmann/json.hpp \
		include/GeometryBuilder.h \
		include/Module.h \
		geometry/include/Cube.h \
		apv_mapping/include/APVMapping.h \
		apv_mapping/include/APVStruct.h \
		third_party/nlohmann/json_fwd.hpp \
		include/Geometry.h \
		geometry/include/Sphere.h \
		geometry/include/Trapezoid.h \
		geometry/include/Tube.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/GeometryBuilder.o src/GeometryBuilder.cpp

obj/UnitTest.o: src/UnitTest.cpp include/UnitTest.h \
		include/Module.h \
		geometry/include/Cube.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/UnitTest.o src/UnitTest.cpp

obj/Cube.o: geometry/src/Cube.cpp geometry/include/Cube.h \
		include/Module.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Cube.o geometry/src/Cube.cpp

obj/Trapezoid.o: geometry/src/Trapezoid.cpp geometry/include/Trapezoid.h \
		include/Module.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Trapezoid.o geometry/src/Trapezoid.cpp

obj/Sphere.o: geometry/src/Sphere.cpp geometry/include/Sphere.h \
		include/Module.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Sphere.o geometry/src/Sphere.cpp

obj/Tube.o: geometry/src/Tube.cpp geometry/include/Tube.h \
		include/Module.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Tube.o geometry/src/Tube.cpp

obj/APVMapping.o: apv_mapping/src/APVMapping.cpp apv_mapping/include/APVMapping.h \
		apv_mapping/include/APVStruct.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/APVMapping.o apv_mapping/src/APVMapping.cpp

obj/APVStruct.o: apv_mapping/src/APVStruct.cpp apv_mapping/include/APVStruct.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/APVStruct.o apv_mapping/src/APVStruct.cpp

obj/moc_OpenGLView.o: moc/moc_OpenGLView.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_OpenGLView.o moc/moc_OpenGLView.cpp

obj/moc_GeometryView.o: moc/moc_GeometryView.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_GeometryView.o moc/moc_GeometryView.cpp

####### Install

install:  FORCE

uninstall:  FORCE

FORCE:

