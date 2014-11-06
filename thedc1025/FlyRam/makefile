################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/ti/ccsv6/tools/compiler/c2000_6.2.7

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
-l"rts2800_fpu32_fast_supplement.lib" \
-l"rts2800_fpu32.lib" \
"./calculate/AHRS.obj" \
"./calculate/car_control.obj" \
"./calculate/gjc_decoders.obj" \
"./calculate/gjc_engineDrive.obj" \
"./calculate/main.obj" \
"./calculate/mhc_GlobalVariables.obj" \
"./calculate/mhc_I2C.obj" \
"./calculate/mhc_SCIA.obj" \
"./calculate/mhc_SCIB_S_BUS.obj" \
"./calculate/mhc_control.obj" \
"./calculate/mhc_cpuTimer.obj" \
"./calculate/mhc_doData.obj" \
"./calculate/mhc_eCap.obj" \
"./calculate/mhc_ePWM.obj" \
"./calculate/mhc_initDSP.obj" \
"./calculate/num2string.obj" \
"./calculate/utilities.obj" \
"./TiLibrary/F2806x_CodeStartBranch.obj" \
"./TiLibrary/F2806x_CpuTimers.obj" \
"./TiLibrary/F2806x_DefaultIsr.obj" \
"./TiLibrary/F2806x_ECap.obj" \
"./TiLibrary/F2806x_EPwm.obj" \
"./TiLibrary/F2806x_GlobalVariableDefs.obj" \
"./TiLibrary/F2806x_Gpio.obj" \
"./TiLibrary/F2806x_HRCap.obj" \
"./TiLibrary/F2806x_I2C.obj" \
"./TiLibrary/F2806x_PieCtrl.obj" \
"./TiLibrary/F2806x_PieVect.obj" \
"./TiLibrary/F2806x_Sci.obj" \
"./TiLibrary/F2806x_SysCtrl.obj" \
"./TiLibrary/F2806x_usDelay.obj" \
"../28069_RAM_lnk.cmd" \
"../F2806x_Headers_nonBIOS.cmd" \
-l"IQmath_fpu32.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include calculate/subdir_vars.mk
-include TiLibrary/subdir_vars.mk
-include subdir_rules.mk
-include calculate/subdir_rules.mk
-include TiLibrary/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Example_2806xEPwmDeadBand.out \

EXE_OUTPUTS__QUOTED += \
"Example_2806xEPwmDeadBand.out" \

BIN_OUTPUTS += \
Example_2806xEPwmDeadBand.hex \

BIN_OUTPUTS__QUOTED += \
"Example_2806xEPwmDeadBand.hex" \


# All Target
all: Example_2806xEPwmDeadBand.out

# Tool invocations
Example_2806xEPwmDeadBand.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data -z -m"Example_2806xEPwmDeadBand.map" --stack_size=0x200 --warn_sections -i"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/lib" -i"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" -i"D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/lib" -i"D:/ti/controlSUITE/libs/math/IQmath/v160/lib" -i"D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/lib" --reread_libs --priority --verbose_diagnostics --issue_remarks --xml_link_info="Example_2806xEPwmDeadBand_linkInfo.xml" --entry_point=code_start --rom_model -o "Example_2806xEPwmDeadBand.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

Example_2806xEPwmDeadBand.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/hex2000"  -o "Example_2806xEPwmDeadBand.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "calculate\AHRS.pp" "calculate\car_control.pp" "calculate\gjc_decoders.pp" "calculate\gjc_engineDrive.pp" "calculate\main.pp" "calculate\mhc_GlobalVariables.pp" "calculate\mhc_I2C.pp" "calculate\mhc_SCIA.pp" "calculate\mhc_SCIB_S_BUS.pp" "calculate\mhc_control.pp" "calculate\mhc_cpuTimer.pp" "calculate\mhc_doData.pp" "calculate\mhc_eCap.pp" "calculate\mhc_ePWM.pp" "calculate\mhc_initDSP.pp" "calculate\num2string.pp" "calculate\utilities.pp" "TiLibrary\F2806x_CpuTimers.pp" "TiLibrary\F2806x_DefaultIsr.pp" "TiLibrary\F2806x_ECap.pp" "TiLibrary\F2806x_EPwm.pp" "TiLibrary\F2806x_GlobalVariableDefs.pp" "TiLibrary\F2806x_Gpio.pp" "TiLibrary\F2806x_HRCap.pp" "TiLibrary\F2806x_I2C.pp" "TiLibrary\F2806x_PieCtrl.pp" "TiLibrary\F2806x_PieVect.pp" "TiLibrary\F2806x_Sci.pp" "TiLibrary\F2806x_SysCtrl.pp" 
	-$(RM) "calculate\AHRS.obj" "calculate\car_control.obj" "calculate\gjc_decoders.obj" "calculate\gjc_engineDrive.obj" "calculate\main.obj" "calculate\mhc_GlobalVariables.obj" "calculate\mhc_I2C.obj" "calculate\mhc_SCIA.obj" "calculate\mhc_SCIB_S_BUS.obj" "calculate\mhc_control.obj" "calculate\mhc_cpuTimer.obj" "calculate\mhc_doData.obj" "calculate\mhc_eCap.obj" "calculate\mhc_ePWM.obj" "calculate\mhc_initDSP.obj" "calculate\num2string.obj" "calculate\utilities.obj" "TiLibrary\F2806x_CodeStartBranch.obj" "TiLibrary\F2806x_CpuTimers.obj" "TiLibrary\F2806x_DefaultIsr.obj" "TiLibrary\F2806x_ECap.obj" "TiLibrary\F2806x_EPwm.obj" "TiLibrary\F2806x_GlobalVariableDefs.obj" "TiLibrary\F2806x_Gpio.obj" "TiLibrary\F2806x_HRCap.obj" "TiLibrary\F2806x_I2C.obj" "TiLibrary\F2806x_PieCtrl.obj" "TiLibrary\F2806x_PieVect.obj" "TiLibrary\F2806x_Sci.obj" "TiLibrary\F2806x_SysCtrl.obj" "TiLibrary\F2806x_usDelay.obj" 
	-$(RM) "TiLibrary\F2806x_CodeStartBranch.pp" "TiLibrary\F2806x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

