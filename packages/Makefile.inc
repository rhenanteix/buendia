# The PACKAGE_VERSION environment variable must be set before running make.

# All paths are written as though the current directory is one level down,
# in one of the buendia-* subdirectories, because Makefile.inc is included
# by Makefiles in those subdirectories.

PACKAGE_NAME := $(shell basename $$(pwd))
TOP := $(shell cd ../.. && pwd)
TOOLS := $(TOP)/tools
FILES := $(shell find root)

# Everything under 'root' is automatically included in the package.  To add
# other files, write a rule to make each file (at a path under $(EXTRA_ROOT)
# and add a rule for $(EXTRA_ROOT): that depends on all of those files.
EXTRA_ROOT := /tmp/$(PACKAGE_NAME)
$(shell mkdir -p $(EXTRA_ROOT))

PACKAGE=$(PACKAGE_NAME)_$(PACKAGE_VERSION)_all.deb

all: $(PACKAGE)

clean:
	rm -rf $(EXTRA_ROOT) *.deb

$(PACKAGE): control/* $(FILES) $(EXTRA_ROOT)
	$(TOOLS)/mkdeb $@ control root $(EXTRA_ROOT)

.FORCE: