#!/bin/bash
set -euo pipefail

model=$(cat /sys/devices/soc0/soc_id)
if [[ "$model" = *r9a07g04* ]] || [[ "$model" = *r9a07g054* ]]; then
# List of valid resolutions
valid_resolutions=("2592x1944" "1920x1080" "1280x960")
elif [[ "$model" = *r9a09g057* ]] || [[ "$model" = *r9a09g047* ]]; then
valid_resolutions=("1920x1080" "1280x960")
fi

DEFAULT_RES="1280x960"
PIXFMT="UYVY8_1X16"
FIELD="none"

ALL=0
DEV=""
RES=""
LIST=0

usage() {
cat <<EOF
v4l2-init.sh - Initialize media links/formats for all CRU cameras (dynamic count)
             - Available resolutions for $model ov5645: ${valid_resolutions[@]}.
USAGE:
  Init all detected CRU cameras:
    $0 -a [-r WxH]

  Init a single camera by video node:
    $0 -d /dev/videoX [-r WxH]

  List detected CRU video nodes:
    $0 -l

OPTIONS:
  -a, --all             Init all detected CRU cameras
  -d, --device DEV      Init only one camera (/dev/videoX)
  -r, --res WxH         Resolution (default: ${DEFAULT_RES})
  -l, --list            List detected CRU video nodes
  -h, --help            Show help
EOF
}

# ---- Discover video devices whose name contains "CRU"
get_cru_video_devs() {
  local n
  for n in /sys/class/video4linux/video*; do
    [[ -e "$n/name" ]] || continue
    if grep -q "CRU" "$n/name"; then
      echo "/dev/$(basename "$n")"
    fi
  done | sort -V
}

# Map /dev/videoX -> X
video_dev_to_index() {
  local dev="$1"
  dev="${dev#/dev/video}"
  [[ "$dev" =~ ^[0-9]+$ ]] || return 1
  echo "$dev"
}

# Sort subdev names by v4l-subdev index
subdev_names_sorted() {
  local n idx name
  for n in /sys/class/video4linux/v4l-subdev*; do
    [[ -r "$n/name" ]] || continue
    idx="${n##*/v4l-subdev}"
    name="$(cat "$n/name")"
    printf "%04d %s\n" "$idx" "$name"
  done | sort -n | cut -d' ' -f2-
}

pick_nth_match() {
  local pattern="$1"
  local nth="$2"
  subdev_names_sorted | grep -i "$pattern" | sed -n "${nth}p"
}

init_one_cam_by_camidx() {
  local cam_idx="$1"   # 0..count-1
  local res="$2"
  local nth=$((cam_idx + 1))
  local media="/dev/media${cam_idx}"

  if [[ ! -e "$media" ]]; then
    echo "Camera idx ${cam_idx}: missing ${media} -> skip"
    return 0
  fi

  local csi2 ip ov5645
  csi2="$(pick_nth_match "csi2" "$nth" || true)"
  ip="$(pick_nth_match "cru-ip" "$nth" || true)"
  ov5645="$(pick_nth_match "ov5645" "$nth" || true)"

  if [[ ! " ${valid_resolutions[@]} " =~ " ${res} " ]]; then
	  echo "Invalid resolution $res for $ov5645. Using default resolution: 1280x960"
	  res="1280x960"
  fi

  if [[ -z "$csi2" || -z "$ip" || -z "$ov5645" ]]; then
    echo "Camera idx ${cam_idx}: subdev missing (csi2='$csi2' ip='$ip' ov5645='$ov5645') -> skip"
    return 0
  fi

  media-ctl -d $media -r
  media-ctl -d $media -V "'${csi2}':1 [fmt:${PIXFMT}/${res} field:${FIELD}]"
  media-ctl -d $media -V "'${ov5645}':0 [fmt:${PIXFMT}/${res} field:${FIELD}]"
  media-ctl -d $media -V "'${ip}':0 [fmt:${PIXFMT}/${res} field:${FIELD}]"
  media-ctl -d $media -V "'${ip}':1 [fmt:${PIXFMT}/${res} field:${FIELD}]"

  echo "Camera idx ${cam_idx} linked CRU/CSI2 to ${ov5645} with ${PIXFMT} ${res}"
}

# ---- Parse args (with missing-arg checks)
while [[ $# -gt 0 ]]; do
  case "$1" in
    -a|--all)
      ALL=1
      shift
      ;;

    -l|--list)
      LIST=1
      shift
      ;;

    -d|--device)
      if [[ $# -lt 2 || "$2" == -* ]]; then
        echo "Error: -d/--device requires an argument (e.g. /dev/video0)"
        usage
        exit 1
      fi
      DEV="$2"
      shift 2
      ;;

    -r|--res)
      if [[ $# -lt 2 || "$2" == -* ]]; then
        echo "Error: -r/--res requires an argument (e.g. 1920x1080)"
        usage
        exit 1
      fi
      RES="$2"
      shift 2
      ;;

    -h|--help)
      usage
      exit 0
      ;;

    *)
      echo "Unknown option: $1"
      usage
      exit 1
      ;;
  esac
done

[[ "$LIST" -eq 0 && "$ALL" -eq 1 && -n "$DEV" ]] && { echo "Error: do not use -a with -d"; exit 1; }
[[ "$LIST" -eq 0 && "$ALL" -eq 0 && -z "$DEV" ]] && { echo "Error: must use -a or -d (or -l to list)"; usage; exit 1; }

# Default resolution
[[ -n "$RES" ]] || RES="$DEFAULT_RES"

# ---- Discover count
CRU_DEVS="$(get_cru_video_devs || true)"
if [[ -z "$CRU_DEVS" ]]; then
  echo "No CRU cameras detected (no /sys/class/video4linux/video*/name contains 'CRU')."
  exit 0
fi

if [[ "$LIST" -eq 1 ]]; then
  count="$(printf "%s\n" "$CRU_DEVS" | wc -l | tr -d ' ')"
  echo "Detected $count CRU video node(s):"
  printf "  %s\n" $CRU_DEVS
  exit 0
fi

# ---- Execute
if [[ "$ALL" -eq 1 ]]; then
  count="$(printf "%s\n" "$CRU_DEVS" | wc -l | tr -d ' ')"
  echo "Detected $count CRU camera(s):"

  cam_idx=0
  while [[ $cam_idx -lt $count ]]; do
    init_one_cam_by_camidx "$cam_idx" "$RES"
    cam_idx=$((cam_idx + 1))
  done
else
  # Find DEV position in detected list -> cam_idx
  cam_idx=-1
  idx=0

  for d in $CRU_DEVS; do
    if [[ "$d" == "$DEV" ]]; then
      cam_idx="$idx"
      break
    fi
    idx=$((idx + 1))
  done

  if [[ "$cam_idx" -lt 0 ]]; then
    echo "Device '$DEV' is not a detected CRU camera."
    exit 1
  fi

  init_one_cam_by_camidx "$cam_idx" "$RES"
fi
