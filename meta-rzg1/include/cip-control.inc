BUSTER_LIMITED_OR_JESSIE="${@'buster-limited' if 'Buster-limited' in '${MACHINE_FEATURES}' else 'jessie'}"
CIP_MODE="${@'buster-full' if 'Buster-full' in '${MACHINE_FEATURES}' else '${BUSTER_LIMITED_OR_JESSIE}'}"
 
