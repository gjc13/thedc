################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
calculate/AHRS.obj: ../calculate/AHRS.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/AHRS.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/car_control.obj: ../calculate/car_control.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/car_control.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/gjc_decoders.obj: ../calculate/gjc_decoders.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/gjc_decoders.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/gjc_eQEP.obj: ../calculate/gjc_eQEP.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/gjc_eQEP.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/gjc_engineDrive.obj: ../calculate/gjc_engineDrive.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/gjc_engineDrive.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/main.obj: ../calculate/main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/main.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/mhc_GlobalVariables.obj: ../calculate/mhc_GlobalVariables.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/mhc_GlobalVariables.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/mhc_I2C.obj: ../calculate/mhc_I2C.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/mhc_I2C.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/mhc_SCIA.obj: ../calculate/mhc_SCIA.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/mhc_SCIA.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/mhc_SCIB_BT.obj: ../calculate/mhc_SCIB_BT.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/mhc_SCIB_BT.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/mhc_SPI.obj: ../calculate/mhc_SPI.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/mhc_SPI.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/mhc_control.obj: ../calculate/mhc_control.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/mhc_control.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/mhc_cpuTimer.obj: ../calculate/mhc_cpuTimer.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/mhc_cpuTimer.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/mhc_doData.obj: ../calculate/mhc_doData.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/mhc_doData.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/mhc_eCap.obj: ../calculate/mhc_eCap.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/mhc_eCap.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/mhc_ePWM.obj: ../calculate/mhc_ePWM.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/mhc_ePWM.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/mhc_initDSP.obj: ../calculate/mhc_initDSP.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/mhc_initDSP.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/num2string.obj: ../calculate/num2string.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/num2string.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

calculate/utilities.obj: ../calculate/utilities.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --fp_reassoc=off --include_path="D:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="calculate/utilities.pp" --obj_directory="calculate" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


