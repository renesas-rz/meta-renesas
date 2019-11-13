QT5_BASE_INHERIT = '${@bb.utils.contains("ENABLE_QT_FRAMEWORK", "1", "populate_sdk_qt5_base", "", d)}'

