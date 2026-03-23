# =========================================================
# ECC Control Configuration for Renesas RZ/G2 Series
# Support: G2N, G2H
# =========================================================

def machine_to_soc(machine):
    mapping = {
        'hihope-rzg2n': 'r8a774b1',
        'hihope-rzg2h': 'r8a774e1',
    }
    return mapping.get(machine, machine)

# =========================================================
# Function: Check ECC mode compatibility per SoC
# Return:
#   0 = disable / partial
#   1 = Full (Dual)
#   2 = Full (Single)
# =========================================================
def check_ecc_mode(d):
    machine = d.getVar("MACHINE")
    soc = machine_to_soc(machine)
    mode = d.getVar("ECC_MODE")

    if d.getVar("USE_ECC") == '1':
        if mode == 'Full':
            if soc in ['r8a774b1']:
                return '2'
            if soc in ['r8a774e1']:
                return '1'

        if mode == 'Full Dual':
            if soc in ['r8a774e1']:
                return '1'
            bb.fatal("\nSelect wrong ECC Full Mode for ECC_MODE.\
                      \nSoC %s not support 'Full Dual'" % soc)

        if mode == 'Full Single':
            return '2'

    return '0'

ECC="${@'1' if 'ecc' in '${MACHINE_FEATURES}' else '0'}"
USE_ECC="${@'1' if '${ECC}' == '1' else '0'}"

ECC_FULL="${@check_ecc_mode(d)}"
