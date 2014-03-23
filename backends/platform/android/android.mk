# Android specific build targets

# These must be incremented for each market upload
ANDROID_VERSIONCODE = 1000

ANDROID_TARGET_VERSION = 10

NDK_BUILD = $(ANDROID_NDK)/ndk-build
SDK_ANDROID = $(ANDROID_SDK)/tools/android

PATH_DIST = $(srcdir)/dists/android
PATH_RESOURCES = $(PATH_DIST)/res

PORT_DISTFILES = $(PATH_DIST)/README.Android
DIST_ANDROID_CONTROLS = $(PATH_DIST)/assets/arrows.tga
DIST_JAVA_SRC_DIR = $(srcdir)/backends/platform/android/org

RESOURCES = \
	$(PATH_BUILD_RES)/values/strings.xml \
	$(PATH_BUILD_RES)/menu/game_menu.xml \
	$(PATH_BUILD_RES)/layout/main.xml \
	$(PATH_BUILD_RES)/drawable/residualvm.png \
	$(PATH_BUILD_RES)/drawable/residualvm_big.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_action.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_down.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_exit.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_hotspot.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_inventory.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_launcher.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_left.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_look_at.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_menu.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_ok.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_pickup.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_right.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_skip_dialog.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_touchmode2.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_touchmode.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_up.png \
	$(PATH_BUILD_RES)/drawable-hdpi/ic_use.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_action.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_down.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_exit.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_hotspot.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_inventory.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_launcher.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_left.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_look_at.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_menu.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_ok.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_pickup.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_right.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_skip_dialog.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_touchmode2.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_touchmode.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_up.png \
	$(PATH_BUILD_RES)/drawable-ldpi/ic_use.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_action.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_down.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_exit.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_hotspot.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_inventory.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_launcher.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_left.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_look_at.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_menu.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_ok.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_pickup.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_right.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_skip_dialog.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_touchmode2.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_touchmode.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_up.png \
	$(PATH_BUILD_RES)/drawable-mdpi/ic_use.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_action.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_down.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_exit.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_hotspot.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_inventory.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_launcher.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_left.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_look_at.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_menu.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_ok.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_pickup.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_right.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_skip_dialog.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_touchmode2.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_touchmode.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_up.png \
	$(PATH_BUILD_RES)/drawable-xhdpi/ic_use.png
	

#JAVA_EXTRA_LIBS = $(PATH_BUILD)/libs/ouya-sdk.jar

DIST_ANDROID_MK = $(PATH_DIST)/jni/Android.mk
DIST_BUILD_XML = $(PATH_DIST)/custom_rules.xml

PATH_BUILD = ./build.tmp
PATH_BUILD_ASSETS = $(PATH_BUILD)/assets
PATH_BUILD_RES = $(PATH_BUILD)/res
PATH_BUILD_LIBRESIDUALVM = $(PATH_BUILD)/libs/armeabi/libresidualvm.so

FILE_MANIFEST_SRC = $(srcdir)/dists/android/AndroidManifest.xml
FILE_MANIFEST = $(PATH_BUILD)/AndroidManifest.xml

APK_MAIN = ResidualVM-debug.apk
APK_MAIN_RELEASE = ResidualVM-release-unsigned.apk
APK_PLUGINS = $(patsubst plugins/lib%.so, residualvm-engine-%.apk, $(PLUGINS))

$(FILE_MANIFEST): $(FILE_MANIFEST_SRC) | $(PATH_BUILD)
	@$(MKDIR) -p $(@D)
	sed "s/@ANDROID_VERSIONCODE@/$(ANDROID_VERSIONCODE)/" < $< > $@

$(PATH_BUILD)/res/%: $(PATH_DIST)/res/% | $(PATH_BUILD)
	@$(MKDIR) -p $(@D)
	$(CP) $< $@

$(PATH_BUILD)/libs/%: $(PATH_DIST)/libs/% | $(PATH_BUILD)
	@$(MKDIR) -p $(@D)
	$(CP) $< $@

$(PATH_BUILD_ASSETS): $(DIST_FILES_THEMES) $(DIST_FILES_ENGINEDATA) $(DIST_FILES_SHADERS) $(DIST_ANDROID_CONTROLS) $(DIST_BUILD_XML) | $(PATH_BUILD)
	$(INSTALL) -d $(PATH_BUILD_ASSETS)
	$(INSTALL) -c -m 644 $(DIST_FILES_THEMES) $(DIST_FILES_ENGINEDATA)  $(DIST_ANDROID_CONTROLS) $(PATH_BUILD_ASSETS)/
	$(INSTALL) -d $(PATH_BUILD)/jni
	$(INSTALL) -c -m 644 $(DIST_ANDROID_MK) $(PATH_BUILD)/jni
	$(INSTALL) -c -m 644 $(DIST_BUILD_XML) $(PATH_BUILD)
ifdef USE_OPENGL_SHADERS
	$(INSTALL) -d $(PATH_BUILD_ASSETS)/shaders
	$(INSTALL) -c -m 644 $(DIST_FILES_SHADERS) $(PATH_BUILD_ASSETS)/shaders
endif

$(PATH_BUILD): $(DIST_ANDROID_MK)
	$(MKDIR) -p $(PATH_BUILD) $(PATH_BUILD)/res
	$(MKDIR) -p $(PATH_BUILD)/libs

$(PATH_BUILD_LIBRESIDUALVM): libresidualvm.so | $(PATH_BUILD)
	$(INSTALL) -c -m 644 libresidualvm.so $(PATH_BUILD)
	$(STRIP) $(PATH_BUILD)/libresidualvm.so
	cd $(PATH_BUILD); $(NDK_BUILD)

$(PATH_BUILD_RES): $(RESOURCES) | $(PATH_BUILD)

setupapk: $(FILE_MANIFEST) $(PATH_BUILD_RES) $(PATH_BUILD_ASSETS) $(JAVA_EXTRA_LIBS) $(PATH_BUILD_LIBRESIDUALVM) | $(PATH_BUILD) 
	$(SDK_ANDROID) update project -p $(PATH_BUILD) -t android-$(ANDROID_TARGET_VERSION) -n ResidualVM

$(APK_MAIN): setupapk | $(PATH_BUILD) 
	(cd $(PATH_BUILD); ant debug -Dsource.dir="$(realpath $(DIST_JAVA_SRC_DIR))")
	$(CP) $(PATH_BUILD)/bin/ResidualVM-debug.apk $@

$(APK_MAIN_RELEASE): setupapk | $(PATH_BUILD) 
	(cd $(PATH_BUILD); ant release -Dsource.dir="$(realpath $(DIST_JAVA_SRC_DIR))")
	$(CP) $(PATH_BUILD)/bin/ResidualVM-release-unsigned.apk $@

all: $(APK_MAIN)

clean: androidclean

androidclean:
	@$(RM) -rf $(PATH_BUILD) *.apk release

androidrelease: $(APK_MAIN_RELEASE)

androidtestmain: $(APK_MAIN)
	$(ADB) install -r $(APK_MAIN)
	$(ADB) shell am start -a android.intent.action.MAIN -c android.intent.category.LAUNCHER -n org.residualvm.residualvm/.Unpacker

androidtest: $(APK_MAIN) $(APK_PLUGINS)
	@set -e; for apk in $^; do \
		$(ADB) install -r $$apk; \
	done
	$(ADB) shell am start -a android.intent.action.MAIN -c android.intent.category.LAUNCHER -n org.residualvm.residualvm/.Unpacker

# used by buildbot!
androiddistdebug: all
	$(MKDIR) debug
	$(CP) $(APK_MAIN) $(APK_PLUGINS) debug/
	for i in $(DIST_FILES_DOCS) $(PORT_DISTFILES); do \
		sed 's/$$/\r/' < $$i > debug/`basename $$i`.txt; \
	done

.PHONY: androidrelease androidtest $(PATH_BUILD_SRC)
