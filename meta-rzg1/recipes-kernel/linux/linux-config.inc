configure_renesas_usbhs(){
    kernel_configure_variable USB_RENESAS_USBHS y
    kernel_configure_variable USB_RENESAS_USBHS_HCD y
    kernel_configure_variable USB_RENESAS_USBHS_UDC y
}

configure_usb_storage(){
	kernel_configure_variable USB_STORAGE y
}

configure_ext3(){
    kernel_configure_variable EXT3_FS y
}


configure_ext4(){
    kernel_configure_variable EXT4_FS y
    kernel_configure_variable EXT4_USE_FOR_EXT2 y
}

configure_touchscreen(){
    # Endable multitouch HID
    kernel_configure_variable HID_MULTITOUCH y
    kernel_configure_variable INPUT_TOUCHSCREEN y
}

configure_usb_cam(){
    #USB cameras
    kernel_configure_variable MEDIA_USB_SUPPORT y
    kernel_configure_variable USB_VIDEO_CLASS y
    kernel_configure_variable USB_VIDEO_CLASS_INPUT_EVDEV y
    kernel_configure_variable USB_GSPCA y
}


configure_usb_to_can(){
    kernel_configure_variable CAN y
    kernel_configure_variable CAN_RAW y
    kernel_configure_variable CAN_BCM y
    kernel_configure_variable CAN_GW y
    kernel_configure_variable CAN_CALC_BITTIMING y
    kernel_configure_variable CAN_DEV y
    kernel_configure_variable CAN_PEAK_USB y
    kernel_configure_variable CAN_KVASER_USB y
}

configure_usb_to_eth(){
    kernel_configure_variable USB_USBNET y
}


configure_rcar_can(){
    kernel_configure_variable CAN y
    kernel_configure_variable CAN_RAW y
    kernel_configure_variable CAN_BCM y
    kernel_configure_variable CAN_GW y
    kernel_configure_variable CAN_CALC_BITTIMING y
    kernel_configure_variable CAN_DEV y
    kernel_configure_variable CAN_RCAR y
}


configure_mtd(){
    #MTD
    kernel_configure_variable MTD_CFI y
    kernel_configure_variable MTD_CFI_ADV_OPTIONS y
    kernel_configure_variable MTD_CFI_INTELEXT y
    kernel_configure_variable MTD_PHYSMAP y
    kernel_configure_variable MTD_BLOCK2MTD y
}

configure_common(){
    # Enable debugfs
    kernel_configure_variable DEBUG_FS y

    #Enable bootargs
    kernel_configure_variable ARM_ATAG_DTB_COMPAT y
    kernel_configure_variable ARM_ATAG_DTB_COMPAT_CMDLINE_FROM_BOOTLOADER y
    kernel_configure_variable CMDLINE_FROM_BOOTLOADER y

    
    kernel_configure_variable VGA_ARB n
    kernel_configure_variable FB_SH_MOBILE_HDMI y
    kernel_configure_variable FRAMEBUFFER_CONSOLE y

    #Enable HR timer
    kernel_configure_variable HIGH_RES_TIMERS y

    #Enable modules
    kernel_configure_variable MODULES y
    kernel_configure_variable MODULE_UNLOAD y

    kernel_configure_variable VIDEO_RENESAS_VSP1 y
    kernel_configure_variable PREEMPT y
    kernel_configure_variable ARM_LPAE y
    
    # DA9063 RTC
    kernel_configure_variable RTC_DRV_DA9063 y

    #GPIO
    kernel_configure_variable GPIO_SYSFS y

    kernel_configure_variable SH_SCI_DMA y

    kernel_configure_variable DRM_RCAR_VSP y

    # Branch prediction
    kernel_configure_variable CPU_BPREDICT_DISABLE n
}


configure_unset(){

    #Disable rmobile
    kernel_configure_variable ARCH_EMEV2 n
    kernel_configure_variable ARCH_R7S72100 n
    kernel_configure_variable ARCH_R8A73A4 n
    kernel_configure_variable ARCH_R8A7740 n
    kernel_configure_variable ARCH_SH73A0 n

    kernel_configure_variable GPIO_PCF857X n

    #branch predict
    kernel_configure_variable CPU_BPREDICT_DISABLE n

    kernel_configure_variable MFD_AS3711 n

    kernel_configure_variable USB_R8A66597_HCD n

    kernel_configure_variable RTC_DRV_RS5C372 n
    kernel_configure_variable RTC_DRV_S35390A n
    kernel_configure_variable RTC_DRV_RX8581 n
}


configure_ravb(){
    #enable EthernetAVB
    kernel_configure_variable RAVB y
    kernel_configure_variable IP_MULTICAST y
}

configure_lvds_ov10635(){
    kernel_configure_variable SOC_CAMERA_MAX9272_OV10635 y
}

configure_direct_ov10635(){
    kernel_configure_variable SOC_CAMERA_OV10635 y
}

configure_jpu(){
    kernel_configure_variable V4L2_MEM2MEM_DEV y
    kernel_configure_variable VIDEO_RENESAS_JPU y
}

configure_DA9063(){
    kernel_configure_variable WATCHDOG y
    kernel_configure_variable WATCHDOG_CORE y
    kernel_configure_variable DA9063_WATCHDOG y
    kernel_configure_variable MFD_CORE y
    kernel_configure_variable MFD_DA9063 y
    kernel_configure_variable REGULATOR_DA9063 y
    kernel_configure_variable RTC_DRV_DA9063 y
}

configure_rcar_thermal(){
    kernel_configure_variable THERMAL y
    kernel_configure_variable CPU_THERMAL y
    kernel_configure_variable RCAR_THERMAL y
}

configure_drm(){
    if '${USE_MULTIMEDIA}' == '0' or '${USE_GLES_WAYLAND}' == '0' ; then
	kernel_configure_variable DRM_RCAR_DU_CONNECT_VSP n
    fi	
}

configure_rcar_pwm(){
    kernel_configure_variable PWM y
    kernel_configure_variable PWM_RCAR y

}

configure_LVDS_panel(){
    kernel_configure_variable DRM_PANEL_SIMPLE y
}

configure_cma_iwg20m(){
    #Enable continious allocator
    kernel_configure_variable CMA y
    kernel_configure_variable DMA_CMA y
    kernel_configure_variable_val CMA_SIZE_MBYTES 128
}

configure_cma_skrzg1m(){
    #Enable continious allocator
    kernel_configure_variable CMA y
    kernel_configure_variable DMA_CMA y
    kernel_configure_variable_val CMA_SIZE_MBYTES 256
}
