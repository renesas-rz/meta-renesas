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
  smarc-rzg2ul | smarc-rzg2l | smarc-rzg2lc | smarc-rzv2l | smarc-rzfive)
    amixer cset name='Left Input Mixer L2 Switch' on
    amixer cset name='Right Input Mixer R2 Switch' on
    amixer cset name='Headphone Playback Volume' 100
    amixer cset name='PCM Volume' 100%
    amixer cset name='Input PGA Volume' 25
    ;;
  iwg20m-g1m | iwg20m-g1n | iwg21m | iwg22m)
  amixer set 'DVC In' 50%
  amixer set 'DVC Out' 50%
  amixer set 'PCM' 70%
  amixer set 'Headphone' 100%
  amixer set 'Mic' 50%
  ;;
  *)
    ;;
esac
