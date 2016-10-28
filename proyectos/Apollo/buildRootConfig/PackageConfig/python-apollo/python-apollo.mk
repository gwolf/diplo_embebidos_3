###############################################################################
#
# python-apollo
#
 ################################################################################

PYTHON_APOLLO_VERSION = 1.0
PYTHON_APOLLO_SOURCE = apollo-$(PYTHON_APOLLO_VERSION).tar.gz
PYTHON_APOLLO_SITE = https://github.com/squiroz91/Apollov1/files/545645
PYTHON_PIP_DEPENDENCIES = python python-setuptools 
PYTHON_APOLLO_LICENSE_FILES = MIT
PYTHON_APOLLO_ENV = SOME_VAR=1
PYTHON_APOLLO_SETUP_TYPE = distutils

$(eval $(python-package))
