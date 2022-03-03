#!/bin/sh

hostname=$(cat /etc/hostname 2>/dev/null)

case "$hostname" in
  ek874)
    amixer set 'DVC In',0 20%
    amixer set 'DVC Out',0 20%
    amixer set 'DVC In',1 20%
    amixer set 'DVC Out',1 20%
    ;;
  hihope-rzg2m | hihope-rzg2n | hihope-rzg2h)
    amixer set 'DVC In',1 20%
    amixer set 'DVC Out',1 20%
    ;;
  *)
    ;;
esac
