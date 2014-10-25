################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
AHRS/AHRS.obj: ../AHRS/AHRS.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo '正在调用： C2000 Compiler'
	"D:/ti/ccs6/ccsv6/tools/compiler/c2000_6.2.6/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="D:/ti/ccs6/ccsv6/tools/compiler/c2000_6.2.6/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" --include_path="D:/documents/ccs6/FLY_I2C_SKYAHRSv99/calculate" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="AHRS/AHRS.pp" --obj_directory="AHRS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

AHRS/MadgwickAHRS.obj: ../AHRS/MadgwickAHRS.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo '正在调用： C2000 Compiler'
	"D:/ti/ccs6/ccsv6/tools/compiler/c2000_6.2.6/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="D:/ti/ccs6/ccsv6/tools/compiler/c2000_6.2.6/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" --include_path="D:/documents/ccs6/FLY_I2C_SKYAHRSv99/calculate" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="AHRS/MadgwickAHRS.pp" --obj_directory="AHRS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

AHRS/filter.obj: ../AHRS/filter.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo '正在调用： C2000 Compiler'
	"D:/ti/ccs6/ccsv6/tools/compiler/c2000_6.2.6/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="D:/ti/ccs6/ccsv6/tools/compiler/c2000_6.2.6/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_headers/include" --include_path="D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/include" --include_path="D:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/include" --include_path="D:/documents/ccs6/FLY_I2C_SKYAHRSv99/calculate" -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data --preproc_with_compile --preproc_dependency="AHRS/filter.pp" --obj_directory="AHRS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


