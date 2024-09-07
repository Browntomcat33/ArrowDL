#!/bin/bash

install_manifest () {
    local TITLE=$1
    local SOURCE=$2
    local DESTINATION=$3
    local TARGET_NAME=$4

    echo "Copying Manifest.JSON to $TITLE directory..."

    mkdir -p $DESTINATION

    TARGET=$DESTINATION/$TARGET_NAME.json

    cp $SOURCE $TARGET

    REPLACE=/ABSOLUTE/PATH/TO/APP/DIRECTORY/launcher
    BY=$PWD/launcher

    REPLACE_escaped=$(echo $REPLACE | sed 's_/_\\/_g')
    BY_escaped=$(echo $BY | sed 's_/_\\/_g')

    sed -i 's/'"$REPLACE_escaped"'/'"$BY_escaped"'/g' $TARGET

    echo "Created: $TARGET"
    echo "Done."
    echo ""
}

TITLE='Mozilla Firefox' 
SOURCE=./launcher-manifest-firefox.json
DESTINATION=~/.mozilla/native-messaging-hosts
TARGET_NAME="com.arrowdl.extension"
install_manifest $TITLE $SOURCE $DESTINATION $TARGET_NAME 


TITLE='Chromium' 
SOURCE=./launcher-manifest-chrome.json
DESTINATION=~/.config/chromium/NativeMessagingHosts/
TARGET_NAME="com.arrowdl.extension"
install_manifest $TITLE $SOURCE $DESTINATION $TARGET_NAME 


TITLE='Google (Chromium) Chrome' 
SOURCE=./launcher-manifest-chrome.json
DESTINATION=~/.config/google-chrome/NativeMessagingHosts/
TARGET_NAME="com.arrowdl.extension"
install_manifest $TITLE $SOURCE $DESTINATION $TARGET_NAME 


TITLE='Microsoft (Chromium) Edge' 
SOURCE=./launcher-manifest-edge.json
DESTINATION=~/.config/microsoft-edge/NativeMessagingHosts/
TARGET_NAME="com.arrowdl.extension"
install_manifest $TITLE $SOURCE $DESTINATION $TARGET_NAME 
