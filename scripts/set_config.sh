#!/bin/bash
SCRIPT_DIR=$(dirname "$(readlink -f $0)")
PARENT_DIR=$(builtin cd $SCRIPT_DIR/../; pwd)
qmk config user.overlay_dir="$PARENT_DIR"
