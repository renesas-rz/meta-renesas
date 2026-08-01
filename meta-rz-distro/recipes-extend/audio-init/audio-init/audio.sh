#!/bin/sh

if ! grep -qE '^[[:space:]]*[0-9]+' /proc/asound/cards 2>/dev/null; then
  echo "No soundcard detected."
  exit 0
fi

hostname=$(cat /etc/hostname 2>/dev/null)

is_codec_present() {
  if aplay -l 2>/dev/null | grep -iq "$1" || \
     arecord -l 2>/dev/null | grep -iq "$1"; then
       return 0
  fi
  echo "Codec $1 not enabled on $hostname. Skip codec settings."
  return 1
}

set_common_g3e_g3s_v2h_v2n() {
    # SSI-DA7212
    # These commands are required when Playback/Capture
    amixer cset name='Aux Switch' on
    amixer cset name='Mixin Left Aux Left Switch' on
    amixer cset name='Mixin Right Aux Right Switch' on
    amixer cset name='ADC Switch' on
    amixer cset name='Mixout Right Mixin Right Switch' off
    amixer cset name='Mixout Left Mixin Left Switch' off
    amixer cset name='Headphone Volume' 80%
    amixer cset name='Headphone Switch' on
    amixer cset name='Mixout Left DAC Left Switch' on
    amixer cset name='Mixout Right DAC Right Switch' on
    amixer cset name='DAC Left Source MUX' 'DAI Input Left'
    amixer cset name='DAC Right Source MUX' 'DAI Input Right'

    amixer sset 'Mic 1 Amp Source MUX' 'MIC_P'
    amixer sset 'Mic 2 Amp Source MUX' 'MIC_P'
    amixer sset 'Mixin Left Mic 1' on
    amixer sset 'Mixin Right Mic 2' on
    amixer sset 'Mic 1' 80% on
    amixer sset 'Mic 2' 80% on
    amixer sset 'Lineout' 80% on
    amixer sset 'Mixin PGA' 40% on
}

case "$hostname" in
  smarc-rzg2ul | smarc-rzg2l | smarc-rzg2lc | smarc-rzv2l)
    codec_name="wm8978"
    if is_codec_present "$codec_name"; then
      amixer cset name='Left Input Mixer L2 Switch' on
      amixer cset name='Right Input Mixer R2 Switch' on
      amixer cset name='Headphone Playback Volume' 100
      amixer cset name='PCM Volume' 100%
      amixer cset name='Input PGA Volume' 25
    fi
    ;;

  smarc-rzg3s | smarc-rzg3l)
    codec_name="da7213"
    if is_codec_present "$codec_name"; then
      set_common_g3e_g3s_v2h_v2n
      amixer sset 'ADC' 100%
      amixer sset 'ADC HPF' off
    fi
    ;;

  smarc-rzg3e | rzv2h-evk | rzv2n-evk)
    codec_name="da7213"
    if is_codec_present "$codec_name"; then
      set_common_g3e_g3s_v2h_v2n
    fi
    amixer sset 'DVC In',0 10%
    amixer sset 'DVC Out',0 20%
    ;;

  *)
    ;;
esac
