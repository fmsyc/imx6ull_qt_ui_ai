# ---------------------------------------------------------------------------
# TerminalApp - convenience wrapper around CMake.
#
#   make            host build (desktop Qt6)  -> build/TerminalApp
#   make run        host build + run it
#   make board      cross build for the i.MX6ULL board (Yocto/FSL SDK)
#                   -> build-board/TerminalApp   (ARM executable)
#   make deploy     push the board build to the board (BOARD=root@ip:/opt/..)
#   make assets     regenerate the placeholder artwork with PIL
#   make clean      remove both build directories
#
# Cross builds need NO environment at all (`make board` works from a plain
# shell).  Do NOT `source environment-setup-*` in the shell you run the *host*
# build in: that puts the SDK's cross qmake first in PATH and the host build
# would then silently target the BOARD Qt ("building against Qt 5.12.9",
# "Could not find moc executable target Qt5::moc").  `make board` is immune to
# this, and warns you instead of failing if the host build would be polluted.
# ---------------------------------------------------------------------------

BUILD_DIR  ?= build
BUILD_TYPE ?= Release
JOBS       ?= $(shell nproc 2>/dev/null || echo 4)

# --- host Qt: prefer qmake6, never accept a sysroot qmake ---------------------
QT_PREFIX ?= $(shell qmake6 -query QT_INSTALL_PREFIX 2>/dev/null)
ifeq ($(QT_PREFIX),)
  QT_PREFIX := $(shell qmake -query QT_INSTALL_PREFIX 2>/dev/null)
endif
CMAKE_QT  := $(if $(QT_PREFIX),-DCMAKE_PREFIX_PATH=$(QT_PREFIX),)

# The sysroot-qmake guard must only fire for host targets.  `make board` (and
# `make deploy`/`clean`/`assets`) are allowed to run in a shell where the SDK's
# qmake is the only one on PATH.
_host_goals := $(if $(MAKECMDGOALS),$(filter all build configure run,$(MAKECMDGOALS)),all)
ifneq (,$(_host_goals))
  ifneq (,$(findstring /sysroots/,$(QT_PREFIX)))
    $(error PATH 中的 qmake 属于交叉编译 SDK ($(QT_PREFIX))，host 构建会误用板端 Qt。请新开终端或从 PATH 移除该 SDK；交叉编译请用 `make board`)
  endif
endif

# --- cross build against the board SDK ---------------------------------------
BOARD_DIR  ?= build-board
SDK_ROOT   ?= /opt/fsl-imx-x11/4.1.15-2.1.0
BOARD      ?= root@192.168.1.10

.PHONY: all help configure build run board deploy assets clean

all: build

help:
	@echo "host  : $(BUILD_DIR)/TerminalApp     (Qt: $(if $(QT_PREFIX),$(QT_PREFIX),auto))"
	@echo "board : $(BOARD_DIR)/TerminalApp     (SDK: $(SDK_ROOT))"
	@echo "targets: all build configure run board deploy assets clean"

configure:
	@echo ">>> configure host build ($(BUILD_TYPE), Qt prefix: $(if $(QT_PREFIX),$(QT_PREFIX),auto))"
	@cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) $(CMAKE_QT)

build: configure
	@cmake --build $(BUILD_DIR) -j$(JOBS)
	@echo ">>> built: $(BUILD_DIR)/TerminalApp"

run: build
	@$(BUILD_DIR)/TerminalApp $(ARGS)

# --- cross compile (no environment-setup sourcing required) -------------------
board:
	@echo ">>> configure board build ($(BUILD_TYPE), SDK: $(SDK_ROOT))"
	@cmake -S . -B $(BOARD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-board.cmake \
		-DSDK_ROOT=$(SDK_ROOT)
	@cmake --build $(BOARD_DIR) -j$(JOBS)
	@echo ">>> built: $(BOARD_DIR)/TerminalApp"
	-@file $(BOARD_DIR)/TerminalApp

# --- ship to the board -------------------------------------------------------
deploy: board
	@BUILD_DIR=$(BOARD_DIR) sh deploy/sync_board.sh $(BOARD):/opt/terminalApp

assets:
	@python3 tools/gen_assets.py

clean:
	@rm -rf $(BUILD_DIR) $(BOARD_DIR)
	@echo ">>> cleaned $(BUILD_DIR) $(BOARD_DIR)"
