#!/bin/sh
if [ "$#" -ne 1 ]; then
    echo "Usage : $0 <keyboards name>"
    exit 1
fi
SCRIPT_DIR=$(dirname "$(readlink -f $0)")
PARENT_DIR=$(builtin cd $SCRIPT_DIR/../; pwd)

KB_SRC_DIR=$PARENT_DIR/keyboards/$1

if [ ! -d $KB_SRC_DIR ]; then
    echo "[ERROR] Not Found keyboard src directory : $KB_SRC_DIR"
    exit 1
fi

VIAL_DIR=$(builtin cd $PARENT_DIR/../vial-qmk; pwd)
if [ ! -d $VIAL_DIR ]; then
    echo "[ERROR] Not Found vial-qmk directory : $VIAL_DIR"
    exit 1
fi

KB_DST_DIR=$VIAL_DIR/keyboards/$1
if [ -L $KB_DST_DIR ]; then
    echo "There is a symbolic link. Once remove it and re-create new one : $KB_DST_DIR"
    rm $KB_DST_DIR
elif [ -d $KB_DST_DIR ]; then
    echo "Rename current dst directory and create symbolic link : $KB_DST_DIR"
    if [ -d ${KB_DST_DIR}_bk ]; then
        mv $KB_DST_DIR ${KB_DST_DIR}_bk2
    else
        mv $KB_DST_DIR ${KB_DST_DIR}_bk
    fi
else
    echo "Create symbolic link on $KB_DST_DIR"
    mkdir -p $KB_DST_DIR
    rmdir $KB_DST_DIR
fi

ln -s $KB_SRC_DIR $KB_DST_DIR
echo "Finished."
