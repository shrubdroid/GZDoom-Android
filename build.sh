#!/bin/bash

if [[ -e compile.log ]]; then
  printf '' > compile.log
fi

{
  if [[ $1 != 'noclean' ]]; then
    if [[ -e doom/.externalNativeBuild ]]; then
      echo "removing doom/.externalNativeBuild..."
      rm -r doom/.externalNativeBuild
    fi

    if [[ -e doom/build ]]; then
      echo "removing doom/build..."
      rm -r doom/build
    fi

    if [[ -e doom/src/main/obj ]]; then
      echo "removing doom/src/main/obj..."
      rm -r doom/src/main/obj
    fi

    if [[ -e doom/src/main/jni/gzdoom_android ]]; then
      echo "removing doom/src/main/jni/gzdoom_android..."
      rm -r doom/src/main/jni/gzdoom_android
    fi
    
    cp -r doom/src/main/jni/gzdoom doom/src/main/jni/gzdoom_android

    STAGEDIR=android_gzdoom/new
    WORKDIR=doom/src/main/jni/gzdoom_android
    find $STAGEDIR -type f | cut -c20- | while read line; do
      [ ! -d `dirname $WORKDIR/"$line"` ] && mkdir -p `dirname $WORKDIR/"$line"`
      cp -rv $STAGEDIR/"$line" $WORKDIR/"$line"
    done
  fi

  patches=$(find android_gzdoom/patches -type f)
  
  temp_file=/tmp/gzdoom_android_source
  while read -r line; do
    patch_file=$line
    relative_name=$(echo $line | cut -c24-)
    target_file="doom/src/main/jni/gzdoom_android/$relative_name"
    source_file="doom/src/main/jni/gzdoom/$relative_name"
    
    cp $source_file $temp_file
    
    patch -N -p1 -r - $temp_file < $patch_file > /dev/null
    
    new_hash=$(sha256sum $temp_file | awk '{print $1}')
    old_hash=$(sha256sum $target_file | awk '{print $1}')
    if [[ $new_hash != $old_hash ]]; then
      echo Patching $relative_name
      mv $temp_file $target_file
    else
      rm $temp_file
    fi
  done <<< $patches


  NDK_PROJECT_PATH=doom/src/main ndk-build
} 2>&1 | tee -a compile.log
