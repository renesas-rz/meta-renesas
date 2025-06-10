#!/bin/sh

hostname=$(cat /etc/hostname 2>/dev/null)

case "$hostname" in
  smarc-rzg2ul | smarc-rzg2l | smarc-rzg2lc)
    amixer cset name='Left Input Mixer L2 Switch' on
    amixer cset name='Right Input Mixer R2 Switch' on
    amixer cset name='Headphone Playback Volume' 100
    amixer cset name='PCM Volume' 100%
    amixer cset name='Input PGA Volume' 25
    ;;
  smarc-rzg3e)
    amixer cset name='Aux Switch' on
    amixer cset name='Mixin Left Aux Left Switch' on
    amixer cset name='Mixin Right Aux Right Switch' on
    amixer cset name='ADC Switch' on
    amixer cset name='Mixout Right Mixin Right Switch' off
    amixer cset name='Mixout Left Mixin Left Switch' off
    amixer cset name='Headphone Volume' 100%
    amixer cset name='Headphone Switch' on
    amixer cset name='Mixout Left DAC Left Switch' on
    amixer cset name='Mixout Right DAC Right Switch' on
    amixer cset name='DAC Left Source MUX' 'DAI Input Left'
    amixer cset name='DAC Right Source MUX' 'DAI Input Right'
    amixer sset 'Mic 1 Amp Source MUX' 'MIC_P'
    amixer sset 'Mic 2 Amp Source MUX' 'MIC_P'
    amixer sset 'Mixin Left Mic 1' on
    amixer sset 'Mixin Left Mic 1' on
    amixer sset 'Mic 1' 100% on
    amixer sset 'Mic 2' 100% on
    amixer sset 'Lineout' 100% on
    amixer sset 'Headphone' 100% on
    amixer sset 'Mixin PGA' 40% on
    amixer sset 'DVC In',0 10%
    ;;
  *)
    ;;
esac
