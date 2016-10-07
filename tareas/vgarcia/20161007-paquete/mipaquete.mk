################################################################################
#
#  MI PAQUETE
#
################################################################################

MIPAQUETE_VERSION = 1.0
MIPAQUETE_SOURCE = mipaquete-$(MIPAQUETE_VERSION).tar.gz
MIPAQUETE_SITE = https://www.dropbox.com/sh/vo66hnsfo7fo3u2/AAB1Cy7m-sTAMXyni22xJRpHa?dl=0
MIPAQUETE_LICENSE = WTFPL

define MIPAQUETE_BUILD_CMDS
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D) all
endef

define MIPAQUETE_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/calculadora $(TARGET_DIR)/usr/bin/calculadora
endef

$(eval $(generic-package))
