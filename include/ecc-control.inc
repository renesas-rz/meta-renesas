def check_ecc_mode(d):
  soc = d.getVar("SOC_FAMILY")
  soc = soc.replace("rzg2:","")
  mode = d.getVar("ECC_MODE")
  if d.getVar("USE_ECC") == '1':
    if mode == 'Full' :
      if soc == 'r8a774c0' or soc == 'r8a774b1':
        return '2'
      if soc == 'r8a774a1' or soc == 'r8a774e1':
        return '1'
    if mode == 'Full Dual':
      if soc == 'r8a774a1' or soc == 'r8a774e1':
        return '1'
      bb.fatal("\nSelect wrong ECC Full Mode for ECC_MODE.\
                \nSoC %s not support 'Full Dual'" % soc);
    if mode == 'Full Single':
        return '2'
  return '0'

ECC="${@'1' if 'ecc' in '${MACHINE_FEATURES}' else '0'}"
USE_ECC="${@'1' if '${ECC}' == '1' else '0'}"

ECC_FULL="${@check_ecc_mode(d)}"
