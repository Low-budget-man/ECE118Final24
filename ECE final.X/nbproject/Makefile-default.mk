#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/ECE_final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/ECE_final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/Ours/BattService.c ../src/Ours/SensorEventChecker.c ../src/Ours/SensorService.c ../src/Ours/TemplateES_Main.c ../src/Ours/TemplateFSM.c ../src/Ours/TemplateHSM.c ../src/Ours/TemplateSubHSM.c ../src/Provided/AD.c ../src/Provided/BOARD.c ../src/Provided/ES_CheckEvents.c ../src/Provided/ES_Framework.c ../src/Provided/ES_KeyboardInput.c ../src/Provided/ES_PostList.c ../src/Provided/ES_Queue.c ../src/Provided/ES_TattleTale.c ../src/Provided/ES_Timers.c ../src/Provided/IO_Ports.c ../src/Provided/LED.c ../src/Provided/pwm.c ../src/Provided/RC_Servo.c ../src/Provided/roach.c ../src/Provided/serial.c ../src/Provided/timers.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1019993215/BattService.o ${OBJECTDIR}/_ext/1019993215/SensorEventChecker.o ${OBJECTDIR}/_ext/1019993215/SensorService.o ${OBJECTDIR}/_ext/1019993215/TemplateES_Main.o ${OBJECTDIR}/_ext/1019993215/TemplateFSM.o ${OBJECTDIR}/_ext/1019993215/TemplateHSM.o ${OBJECTDIR}/_ext/1019993215/TemplateSubHSM.o ${OBJECTDIR}/_ext/1041239619/AD.o ${OBJECTDIR}/_ext/1041239619/BOARD.o ${OBJECTDIR}/_ext/1041239619/ES_CheckEvents.o ${OBJECTDIR}/_ext/1041239619/ES_Framework.o ${OBJECTDIR}/_ext/1041239619/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1041239619/ES_PostList.o ${OBJECTDIR}/_ext/1041239619/ES_Queue.o ${OBJECTDIR}/_ext/1041239619/ES_TattleTale.o ${OBJECTDIR}/_ext/1041239619/ES_Timers.o ${OBJECTDIR}/_ext/1041239619/IO_Ports.o ${OBJECTDIR}/_ext/1041239619/LED.o ${OBJECTDIR}/_ext/1041239619/pwm.o ${OBJECTDIR}/_ext/1041239619/RC_Servo.o ${OBJECTDIR}/_ext/1041239619/roach.o ${OBJECTDIR}/_ext/1041239619/serial.o ${OBJECTDIR}/_ext/1041239619/timers.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1019993215/BattService.o.d ${OBJECTDIR}/_ext/1019993215/SensorEventChecker.o.d ${OBJECTDIR}/_ext/1019993215/SensorService.o.d ${OBJECTDIR}/_ext/1019993215/TemplateES_Main.o.d ${OBJECTDIR}/_ext/1019993215/TemplateFSM.o.d ${OBJECTDIR}/_ext/1019993215/TemplateHSM.o.d ${OBJECTDIR}/_ext/1019993215/TemplateSubHSM.o.d ${OBJECTDIR}/_ext/1041239619/AD.o.d ${OBJECTDIR}/_ext/1041239619/BOARD.o.d ${OBJECTDIR}/_ext/1041239619/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/1041239619/ES_Framework.o.d ${OBJECTDIR}/_ext/1041239619/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/1041239619/ES_PostList.o.d ${OBJECTDIR}/_ext/1041239619/ES_Queue.o.d ${OBJECTDIR}/_ext/1041239619/ES_TattleTale.o.d ${OBJECTDIR}/_ext/1041239619/ES_Timers.o.d ${OBJECTDIR}/_ext/1041239619/IO_Ports.o.d ${OBJECTDIR}/_ext/1041239619/LED.o.d ${OBJECTDIR}/_ext/1041239619/pwm.o.d ${OBJECTDIR}/_ext/1041239619/RC_Servo.o.d ${OBJECTDIR}/_ext/1041239619/roach.o.d ${OBJECTDIR}/_ext/1041239619/serial.o.d ${OBJECTDIR}/_ext/1041239619/timers.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1019993215/BattService.o ${OBJECTDIR}/_ext/1019993215/SensorEventChecker.o ${OBJECTDIR}/_ext/1019993215/SensorService.o ${OBJECTDIR}/_ext/1019993215/TemplateES_Main.o ${OBJECTDIR}/_ext/1019993215/TemplateFSM.o ${OBJECTDIR}/_ext/1019993215/TemplateHSM.o ${OBJECTDIR}/_ext/1019993215/TemplateSubHSM.o ${OBJECTDIR}/_ext/1041239619/AD.o ${OBJECTDIR}/_ext/1041239619/BOARD.o ${OBJECTDIR}/_ext/1041239619/ES_CheckEvents.o ${OBJECTDIR}/_ext/1041239619/ES_Framework.o ${OBJECTDIR}/_ext/1041239619/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1041239619/ES_PostList.o ${OBJECTDIR}/_ext/1041239619/ES_Queue.o ${OBJECTDIR}/_ext/1041239619/ES_TattleTale.o ${OBJECTDIR}/_ext/1041239619/ES_Timers.o ${OBJECTDIR}/_ext/1041239619/IO_Ports.o ${OBJECTDIR}/_ext/1041239619/LED.o ${OBJECTDIR}/_ext/1041239619/pwm.o ${OBJECTDIR}/_ext/1041239619/RC_Servo.o ${OBJECTDIR}/_ext/1041239619/roach.o ${OBJECTDIR}/_ext/1041239619/serial.o ${OBJECTDIR}/_ext/1041239619/timers.o

# Source Files
SOURCEFILES=../src/Ours/BattService.c ../src/Ours/SensorEventChecker.c ../src/Ours/SensorService.c ../src/Ours/TemplateES_Main.c ../src/Ours/TemplateFSM.c ../src/Ours/TemplateHSM.c ../src/Ours/TemplateSubHSM.c ../src/Provided/AD.c ../src/Provided/BOARD.c ../src/Provided/ES_CheckEvents.c ../src/Provided/ES_Framework.c ../src/Provided/ES_KeyboardInput.c ../src/Provided/ES_PostList.c ../src/Provided/ES_Queue.c ../src/Provided/ES_TattleTale.c ../src/Provided/ES_Timers.c ../src/Provided/IO_Ports.c ../src/Provided/LED.c ../src/Provided/pwm.c ../src/Provided/RC_Servo.c ../src/Provided/roach.c ../src/Provided/serial.c ../src/Provided/timers.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/ECE_final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1019993215/BattService.o: ../src/Ours/BattService.c  .generated_files/flags/default/4b47c2344e92db915246705b4f8b03f09dd9dd99 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1019993215" 
	@${RM} ${OBJECTDIR}/_ext/1019993215/BattService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019993215/BattService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1019993215/BattService.o.d" -o ${OBJECTDIR}/_ext/1019993215/BattService.o ../src/Ours/BattService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1019993215/SensorEventChecker.o: ../src/Ours/SensorEventChecker.c  .generated_files/flags/default/d5f5d27d76e77c144d6217c1000745552a3e28a0 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1019993215" 
	@${RM} ${OBJECTDIR}/_ext/1019993215/SensorEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019993215/SensorEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1019993215/SensorEventChecker.o.d" -o ${OBJECTDIR}/_ext/1019993215/SensorEventChecker.o ../src/Ours/SensorEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1019993215/SensorService.o: ../src/Ours/SensorService.c  .generated_files/flags/default/3af8e74354d9b81c7aad350b3fc84ed2204985dd .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1019993215" 
	@${RM} ${OBJECTDIR}/_ext/1019993215/SensorService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019993215/SensorService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1019993215/SensorService.o.d" -o ${OBJECTDIR}/_ext/1019993215/SensorService.o ../src/Ours/SensorService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1019993215/TemplateES_Main.o: ../src/Ours/TemplateES_Main.c  .generated_files/flags/default/1299c0581ae9bdd34903852744266f3d8690f724 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1019993215" 
	@${RM} ${OBJECTDIR}/_ext/1019993215/TemplateES_Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019993215/TemplateES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1019993215/TemplateES_Main.o.d" -o ${OBJECTDIR}/_ext/1019993215/TemplateES_Main.o ../src/Ours/TemplateES_Main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1019993215/TemplateFSM.o: ../src/Ours/TemplateFSM.c  .generated_files/flags/default/4b8d916035ce3ef81d7b1f50de56a5f5c672dba1 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1019993215" 
	@${RM} ${OBJECTDIR}/_ext/1019993215/TemplateFSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019993215/TemplateFSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1019993215/TemplateFSM.o.d" -o ${OBJECTDIR}/_ext/1019993215/TemplateFSM.o ../src/Ours/TemplateFSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1019993215/TemplateHSM.o: ../src/Ours/TemplateHSM.c  .generated_files/flags/default/c2f2fdbb1d99a00c34c146f42f02d5beb0587535 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1019993215" 
	@${RM} ${OBJECTDIR}/_ext/1019993215/TemplateHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019993215/TemplateHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1019993215/TemplateHSM.o.d" -o ${OBJECTDIR}/_ext/1019993215/TemplateHSM.o ../src/Ours/TemplateHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1019993215/TemplateSubHSM.o: ../src/Ours/TemplateSubHSM.c  .generated_files/flags/default/4db00759db0e5ad4766b34dce68ea525ca97524b .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1019993215" 
	@${RM} ${OBJECTDIR}/_ext/1019993215/TemplateSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019993215/TemplateSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1019993215/TemplateSubHSM.o.d" -o ${OBJECTDIR}/_ext/1019993215/TemplateSubHSM.o ../src/Ours/TemplateSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/AD.o: ../src/Provided/AD.c  .generated_files/flags/default/f19aa06fedf8191c40719f353792b1c02f8a4da4 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/AD.o.d" -o ${OBJECTDIR}/_ext/1041239619/AD.o ../src/Provided/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/BOARD.o: ../src/Provided/BOARD.c  .generated_files/flags/default/ca6e4776389c1b6631b61c6ef98c4c0a0153332e .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/BOARD.o.d" -o ${OBJECTDIR}/_ext/1041239619/BOARD.o ../src/Provided/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/ES_CheckEvents.o: ../src/Provided/ES_CheckEvents.c  .generated_files/flags/default/a9d32f8d5231e627e2c90a05fe49f16eef2bf9fe .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1041239619/ES_CheckEvents.o ../src/Provided/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/ES_Framework.o: ../src/Provided/ES_Framework.c  .generated_files/flags/default/a8199ff909db07d2d8d81212bfb7cf4315bea2c4 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1041239619/ES_Framework.o ../src/Provided/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/ES_KeyboardInput.o: ../src/Provided/ES_KeyboardInput.c  .generated_files/flags/default/b3f9086155023b7cb5282b708128dad11b3e9c33 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1041239619/ES_KeyboardInput.o ../src/Provided/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/ES_PostList.o: ../src/Provided/ES_PostList.c  .generated_files/flags/default/2f63e13a6406bdd62c55575eb178aa621ca8a1c0 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1041239619/ES_PostList.o ../src/Provided/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/ES_Queue.o: ../src/Provided/ES_Queue.c  .generated_files/flags/default/612b6d3abc8be9a27a734a6a4c7dcf54fe589287 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1041239619/ES_Queue.o ../src/Provided/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/ES_TattleTale.o: ../src/Provided/ES_TattleTale.c  .generated_files/flags/default/7b921a2b79f03d075302efc22aa4982c36db35da .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1041239619/ES_TattleTale.o ../src/Provided/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/ES_Timers.o: ../src/Provided/ES_Timers.c  .generated_files/flags/default/bf6592f06588b5781d1a1ce1b3a56a75e81c35f9 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1041239619/ES_Timers.o ../src/Provided/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/IO_Ports.o: ../src/Provided/IO_Ports.c  .generated_files/flags/default/578b9af2aafa5535c30c24ee4f2cd0c35c22a13 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1041239619/IO_Ports.o ../src/Provided/IO_Ports.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/LED.o: ../src/Provided/LED.c  .generated_files/flags/default/1b6a97e60f958b09bfc6efab4228e035109075b7 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/LED.o.d" -o ${OBJECTDIR}/_ext/1041239619/LED.o ../src/Provided/LED.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/pwm.o: ../src/Provided/pwm.c  .generated_files/flags/default/cb05110ee50da1fb37f80c8742368831f85d9333 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/pwm.o.d" -o ${OBJECTDIR}/_ext/1041239619/pwm.o ../src/Provided/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/RC_Servo.o: ../src/Provided/RC_Servo.c  .generated_files/flags/default/17b4215d6f5ab51a70bfe74d1728fdb518f1588a .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1041239619/RC_Servo.o ../src/Provided/RC_Servo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/roach.o: ../src/Provided/roach.c  .generated_files/flags/default/e18799388cce73b06c8b0eb5eb37da23bcf8808 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/roach.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/roach.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/roach.o.d" -o ${OBJECTDIR}/_ext/1041239619/roach.o ../src/Provided/roach.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/serial.o: ../src/Provided/serial.c  .generated_files/flags/default/137b08331f3647dce0a4f373ffca11e13abc2f80 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/serial.o.d" -o ${OBJECTDIR}/_ext/1041239619/serial.o ../src/Provided/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/timers.o: ../src/Provided/timers.c  .generated_files/flags/default/2bbff5ff94bcc78a77a898142906e9c5cf8d8e2e .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/timers.o.d" -o ${OBJECTDIR}/_ext/1041239619/timers.o ../src/Provided/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1019993215/BattService.o: ../src/Ours/BattService.c  .generated_files/flags/default/e1e5e536d869c712b2bf1d546e2820d2b41a2e88 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1019993215" 
	@${RM} ${OBJECTDIR}/_ext/1019993215/BattService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019993215/BattService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1019993215/BattService.o.d" -o ${OBJECTDIR}/_ext/1019993215/BattService.o ../src/Ours/BattService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1019993215/SensorEventChecker.o: ../src/Ours/SensorEventChecker.c  .generated_files/flags/default/aa8c337de07b54703a3f83ef0b9770216358e908 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1019993215" 
	@${RM} ${OBJECTDIR}/_ext/1019993215/SensorEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019993215/SensorEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1019993215/SensorEventChecker.o.d" -o ${OBJECTDIR}/_ext/1019993215/SensorEventChecker.o ../src/Ours/SensorEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1019993215/SensorService.o: ../src/Ours/SensorService.c  .generated_files/flags/default/7dd082607890c886e32d1da75a8fcfa4d1085f1c .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1019993215" 
	@${RM} ${OBJECTDIR}/_ext/1019993215/SensorService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019993215/SensorService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1019993215/SensorService.o.d" -o ${OBJECTDIR}/_ext/1019993215/SensorService.o ../src/Ours/SensorService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1019993215/TemplateES_Main.o: ../src/Ours/TemplateES_Main.c  .generated_files/flags/default/73c348620c8d8d80ccee3e8ce6db2482fb8d8be5 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1019993215" 
	@${RM} ${OBJECTDIR}/_ext/1019993215/TemplateES_Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019993215/TemplateES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1019993215/TemplateES_Main.o.d" -o ${OBJECTDIR}/_ext/1019993215/TemplateES_Main.o ../src/Ours/TemplateES_Main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1019993215/TemplateFSM.o: ../src/Ours/TemplateFSM.c  .generated_files/flags/default/50043efcfdb2f95ff183713416f51b7be8af7613 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1019993215" 
	@${RM} ${OBJECTDIR}/_ext/1019993215/TemplateFSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019993215/TemplateFSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1019993215/TemplateFSM.o.d" -o ${OBJECTDIR}/_ext/1019993215/TemplateFSM.o ../src/Ours/TemplateFSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1019993215/TemplateHSM.o: ../src/Ours/TemplateHSM.c  .generated_files/flags/default/cc916aaafd5ea26f7279a434b351e442ae50c823 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1019993215" 
	@${RM} ${OBJECTDIR}/_ext/1019993215/TemplateHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019993215/TemplateHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1019993215/TemplateHSM.o.d" -o ${OBJECTDIR}/_ext/1019993215/TemplateHSM.o ../src/Ours/TemplateHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1019993215/TemplateSubHSM.o: ../src/Ours/TemplateSubHSM.c  .generated_files/flags/default/3afaefae1b58e8e0232ebc74a668fb3a60e4db24 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1019993215" 
	@${RM} ${OBJECTDIR}/_ext/1019993215/TemplateSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1019993215/TemplateSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1019993215/TemplateSubHSM.o.d" -o ${OBJECTDIR}/_ext/1019993215/TemplateSubHSM.o ../src/Ours/TemplateSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/AD.o: ../src/Provided/AD.c  .generated_files/flags/default/51e7a90a1ad60e0e76750147cc5e1ccdf4b09e2f .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/AD.o.d" -o ${OBJECTDIR}/_ext/1041239619/AD.o ../src/Provided/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/BOARD.o: ../src/Provided/BOARD.c  .generated_files/flags/default/552db57e967073f9eee791d47295e522faf8b760 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/BOARD.o.d" -o ${OBJECTDIR}/_ext/1041239619/BOARD.o ../src/Provided/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/ES_CheckEvents.o: ../src/Provided/ES_CheckEvents.c  .generated_files/flags/default/8e0b050e8aa6ba2bb89fd78b27ba7d5a0b6e2708 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1041239619/ES_CheckEvents.o ../src/Provided/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/ES_Framework.o: ../src/Provided/ES_Framework.c  .generated_files/flags/default/8b507ad00cdb68f28de49d98190306ef58e8568a .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1041239619/ES_Framework.o ../src/Provided/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/ES_KeyboardInput.o: ../src/Provided/ES_KeyboardInput.c  .generated_files/flags/default/4bc869748f441f8dd1dd96c20a30f3ecd1271ee9 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1041239619/ES_KeyboardInput.o ../src/Provided/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/ES_PostList.o: ../src/Provided/ES_PostList.c  .generated_files/flags/default/91752186f85d45e3dd52584506c9a5c319392408 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1041239619/ES_PostList.o ../src/Provided/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/ES_Queue.o: ../src/Provided/ES_Queue.c  .generated_files/flags/default/173bdb9a58fdbdc7d08ccba88483c66c2d1a8074 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1041239619/ES_Queue.o ../src/Provided/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/ES_TattleTale.o: ../src/Provided/ES_TattleTale.c  .generated_files/flags/default/aa0ce7ea9518c7d9d65ddbbcbfb2825625351aa9 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1041239619/ES_TattleTale.o ../src/Provided/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/ES_Timers.o: ../src/Provided/ES_Timers.c  .generated_files/flags/default/f8afbf56f417102931cdc51582d2ac19c2b5b3f3 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1041239619/ES_Timers.o ../src/Provided/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/IO_Ports.o: ../src/Provided/IO_Ports.c  .generated_files/flags/default/b8ead8f76e39f7dcce22207ad9a330668cd66e95 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1041239619/IO_Ports.o ../src/Provided/IO_Ports.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/LED.o: ../src/Provided/LED.c  .generated_files/flags/default/a19d7139528f1ee6e1b057f068cca81c724f530f .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/LED.o.d" -o ${OBJECTDIR}/_ext/1041239619/LED.o ../src/Provided/LED.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/pwm.o: ../src/Provided/pwm.c  .generated_files/flags/default/2c42c1bf9d74c372997ed8dad33a3f6d03425c34 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/pwm.o.d" -o ${OBJECTDIR}/_ext/1041239619/pwm.o ../src/Provided/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/RC_Servo.o: ../src/Provided/RC_Servo.c  .generated_files/flags/default/47cb877fb830debc5db90a1f41288618cba4fca7 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1041239619/RC_Servo.o ../src/Provided/RC_Servo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/roach.o: ../src/Provided/roach.c  .generated_files/flags/default/f104efb970439d90571074840ea641664210d942 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/roach.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/roach.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/roach.o.d" -o ${OBJECTDIR}/_ext/1041239619/roach.o ../src/Provided/roach.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/serial.o: ../src/Provided/serial.c  .generated_files/flags/default/1898772eea878fea864701eb6d34235d9140498f .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/serial.o.d" -o ${OBJECTDIR}/_ext/1041239619/serial.o ../src/Provided/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1041239619/timers.o: ../src/Provided/timers.c  .generated_files/flags/default/8e49954745809ce64a72b8de50db6e4502fea592 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1041239619" 
	@${RM} ${OBJECTDIR}/_ext/1041239619/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1041239619/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1041239619/timers.o.d" -o ${OBJECTDIR}/_ext/1041239619/timers.o ../src/Provided/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/ECE_final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/ECE_final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=1024,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/ECE_final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/ECE_final.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=1024,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/ECE_final.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
