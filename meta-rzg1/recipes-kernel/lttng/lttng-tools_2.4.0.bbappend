# This version of LTTng is not compatible with current system.
# Force system uses older version instead to prevent issue (by excluding arm
#     from compatble host)
COMPATIBLE_HOST = '(x86_64|i.86|powerpc|aarch64|mips).*-linux'
