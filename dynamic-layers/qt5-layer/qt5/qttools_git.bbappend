#Revision to update qt5.6.3
require qt5.6.3_git.inc
SRCREV = "56dbabb7a64a4d416e8cf7b61e068208fd032355"

LIC_FILES_CHKSUM = " \
    file://LICENSE.LGPLv21;md5=fb91571854638f10b2e5f36562661a5a \
    file://LICENSE.LGPLv3;md5=a909b94c1c9674b2aa15ff03a86f518a \
    file://LICENSE.GPLv3;md5=bfdd8aa675169432d6d9b63d056de148 \
    file://LGPL_EXCEPTION.txt;md5=9625233da42f9e0ce9d63651a9d97654 \
    file://LICENSE.FDL;md5=6d9f2a9af4c8b8c3c769f6cc1b6aaf7e \
"

PACKAGECONFIG_class-native ??= ""
PACKAGECONFIG_class-nativesdk ??= ""
