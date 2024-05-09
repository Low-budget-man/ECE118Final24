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
SOURCEFILES_QUOTED_IF_SPACED="C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Ours/SensorEventChecker.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Ours/BattService.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/AD.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/BOARD.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_CheckEvents.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Framework.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_KeyboardInput.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_PostList.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Queue.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_TattleTale.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Timers.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/IO_Ports.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/LED.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/pwm.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/RC_Servo.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/roach.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/serial.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/timers.c"

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/2070106491/SensorEventChecker.o ${OBJECTDIR}/_ext/2070106491/BattService.o ${OBJECTDIR}/_ext/1384354487/AD.o ${OBJECTDIR}/_ext/1384354487/BOARD.o ${OBJECTDIR}/_ext/1384354487/ES_CheckEvents.o ${OBJECTDIR}/_ext/1384354487/ES_Framework.o ${OBJECTDIR}/_ext/1384354487/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1384354487/ES_PostList.o ${OBJECTDIR}/_ext/1384354487/ES_Queue.o ${OBJECTDIR}/_ext/1384354487/ES_TattleTale.o ${OBJECTDIR}/_ext/1384354487/ES_Timers.o ${OBJECTDIR}/_ext/1384354487/IO_Ports.o ${OBJECTDIR}/_ext/1384354487/LED.o ${OBJECTDIR}/_ext/1384354487/pwm.o ${OBJECTDIR}/_ext/1384354487/RC_Servo.o ${OBJECTDIR}/_ext/1384354487/roach.o ${OBJECTDIR}/_ext/1384354487/serial.o ${OBJECTDIR}/_ext/1384354487/timers.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/2070106491/SensorEventChecker.o.d ${OBJECTDIR}/_ext/2070106491/BattService.o.d ${OBJECTDIR}/_ext/1384354487/AD.o.d ${OBJECTDIR}/_ext/1384354487/BOARD.o.d ${OBJECTDIR}/_ext/1384354487/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/1384354487/ES_Framework.o.d ${OBJECTDIR}/_ext/1384354487/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/1384354487/ES_PostList.o.d ${OBJECTDIR}/_ext/1384354487/ES_Queue.o.d ${OBJECTDIR}/_ext/1384354487/ES_TattleTale.o.d ${OBJECTDIR}/_ext/1384354487/ES_Timers.o.d ${OBJECTDIR}/_ext/1384354487/IO_Ports.o.d ${OBJECTDIR}/_ext/1384354487/LED.o.d ${OBJECTDIR}/_ext/1384354487/pwm.o.d ${OBJECTDIR}/_ext/1384354487/RC_Servo.o.d ${OBJECTDIR}/_ext/1384354487/roach.o.d ${OBJECTDIR}/_ext/1384354487/serial.o.d ${OBJECTDIR}/_ext/1384354487/timers.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/2070106491/SensorEventChecker.o ${OBJECTDIR}/_ext/2070106491/BattService.o ${OBJECTDIR}/_ext/1384354487/AD.o ${OBJECTDIR}/_ext/1384354487/BOARD.o ${OBJECTDIR}/_ext/1384354487/ES_CheckEvents.o ${OBJECTDIR}/_ext/1384354487/ES_Framework.o ${OBJECTDIR}/_ext/1384354487/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1384354487/ES_PostList.o ${OBJECTDIR}/_ext/1384354487/ES_Queue.o ${OBJECTDIR}/_ext/1384354487/ES_TattleTale.o ${OBJECTDIR}/_ext/1384354487/ES_Timers.o ${OBJECTDIR}/_ext/1384354487/IO_Ports.o ${OBJECTDIR}/_ext/1384354487/LED.o ${OBJECTDIR}/_ext/1384354487/pwm.o ${OBJECTDIR}/_ext/1384354487/RC_Servo.o ${OBJECTDIR}/_ext/1384354487/roach.o ${OBJECTDIR}/_ext/1384354487/serial.o ${OBJECTDIR}/_ext/1384354487/timers.o

# Source Files
SOURCEFILES=C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Ours/SensorEventChecker.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Ours/BattService.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/AD.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/BOARD.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_CheckEvents.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Framework.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_KeyboardInput.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_PostList.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Queue.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_TattleTale.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Timers.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/IO_Ports.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/LED.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/pwm.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/RC_Servo.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/roach.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/serial.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/timers.c



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
MP_LINKER_FILE_OPTION=,--script="C:\Users\coope\OneDrive\Documents\UCSC\Classes\UCSC 3nd quarter classes y3\ECE 118\FinalProject\ece118-final\otherfiles\bootloader320.ld"
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
${OBJECTDIR}/_ext/2070106491/SensorEventChecker.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Ours/SensorEventChecker.c  .generated_files/flags/default/f818a62fb0091f94cd6b03cfb6aaf455997e4ad3 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/2070106491" 
	@${RM} ${OBJECTDIR}/_ext/2070106491/SensorEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/2070106491/SensorEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/2070106491/SensorEventChecker.o.d" -o ${OBJECTDIR}/_ext/2070106491/SensorEventChecker.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Ours/SensorEventChecker.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2070106491/BattService.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Ours/BattService.c  .generated_files/flags/default/16f7a188f85dc5aed1a51f5467e6d6ee364cb5f3 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/2070106491" 
	@${RM} ${OBJECTDIR}/_ext/2070106491/BattService.o.d 
	@${RM} ${OBJECTDIR}/_ext/2070106491/BattService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/2070106491/BattService.o.d" -o ${OBJECTDIR}/_ext/2070106491/BattService.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Ours/BattService.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/AD.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/AD.c  .generated_files/flags/default/7d6c0c3826f88cc26decb474545f92ba5967f34e .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/AD.o.d" -o ${OBJECTDIR}/_ext/1384354487/AD.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/AD.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/BOARD.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/BOARD.c  .generated_files/flags/default/97801f35a6379332a988194ecfa2812497f055ac .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/BOARD.o.d" -o ${OBJECTDIR}/_ext/1384354487/BOARD.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/BOARD.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/ES_CheckEvents.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/ES_CheckEvents.c  .generated_files/flags/default/702bf3262dbe62b2a78a450228b9559e0fccb77 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1384354487/ES_CheckEvents.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_CheckEvents.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/ES_Framework.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/ES_Framework.c  .generated_files/flags/default/3b7501aa1838c7e8bdeb380f31e24f471dc3a03c .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1384354487/ES_Framework.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Framework.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/ES_KeyboardInput.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/ES_KeyboardInput.c  .generated_files/flags/default/a9878c1cd89dece4b16fac1fbbfbe462af7835ad .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1384354487/ES_KeyboardInput.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_KeyboardInput.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/ES_PostList.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/ES_PostList.c  .generated_files/flags/default/cc7a8b834625dcf2f62954e83acfdbc066cb0d5b .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1384354487/ES_PostList.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_PostList.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/ES_Queue.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/ES_Queue.c  .generated_files/flags/default/84a14b6563825a79261f6e1c4b5071f79b0d6737 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1384354487/ES_Queue.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Queue.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/ES_TattleTale.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/ES_TattleTale.c  .generated_files/flags/default/f45a51a0f436523db293fcc01130aeb89b4f727c .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1384354487/ES_TattleTale.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_TattleTale.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/ES_Timers.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/ES_Timers.c  .generated_files/flags/default/dd20112c0818f112d87001fa620200a77b865737 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1384354487/ES_Timers.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Timers.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/IO_Ports.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/IO_Ports.c  .generated_files/flags/default/36882931aca8b30dae8c938fbe79c8c009738f1d .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1384354487/IO_Ports.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/IO_Ports.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/LED.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/LED.c  .generated_files/flags/default/9e597eda91fbff7e2fcd025dd1e922e67215f2ef .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/LED.o.d" -o ${OBJECTDIR}/_ext/1384354487/LED.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/LED.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/pwm.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/pwm.c  .generated_files/flags/default/c7f8923c47cf11390856eed660fedb8a970e0eb4 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/pwm.o.d" -o ${OBJECTDIR}/_ext/1384354487/pwm.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/pwm.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/RC_Servo.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/RC_Servo.c  .generated_files/flags/default/b9d8d53cb86c9e13b2fc6f30dd5342b0a19c50fb .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1384354487/RC_Servo.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/RC_Servo.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/roach.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/roach.c  .generated_files/flags/default/acd11a3661565a047a590e3475c24adb6b3e3d92 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/roach.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/roach.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/roach.o.d" -o ${OBJECTDIR}/_ext/1384354487/roach.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/roach.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/serial.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/serial.c  .generated_files/flags/default/1f45f3a09cf665b26d5140386d910155b61b0efe .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/serial.o.d" -o ${OBJECTDIR}/_ext/1384354487/serial.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/serial.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/timers.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/timers.c  .generated_files/flags/default/b40ac6740db95f182214ff215b067943a7210162 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/timers.o.d" -o ${OBJECTDIR}/_ext/1384354487/timers.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/timers.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/2070106491/SensorEventChecker.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Ours/SensorEventChecker.c  .generated_files/flags/default/647254024eb7c7eaab5c3478392ccc30d097cb7f .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/2070106491" 
	@${RM} ${OBJECTDIR}/_ext/2070106491/SensorEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/2070106491/SensorEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/2070106491/SensorEventChecker.o.d" -o ${OBJECTDIR}/_ext/2070106491/SensorEventChecker.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Ours/SensorEventChecker.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2070106491/BattService.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Ours/BattService.c  .generated_files/flags/default/e2c80c08811c952fdbf9d3df1318f3e4d7fb1ab .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/2070106491" 
	@${RM} ${OBJECTDIR}/_ext/2070106491/BattService.o.d 
	@${RM} ${OBJECTDIR}/_ext/2070106491/BattService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/2070106491/BattService.o.d" -o ${OBJECTDIR}/_ext/2070106491/BattService.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Ours/BattService.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/AD.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/AD.c  .generated_files/flags/default/edf3820c67442987eb588119057941380578b58f .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/AD.o.d" -o ${OBJECTDIR}/_ext/1384354487/AD.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/AD.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/BOARD.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/BOARD.c  .generated_files/flags/default/9cc53e1cf7fa68a629297abb76eaea527623ab58 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/BOARD.o.d" -o ${OBJECTDIR}/_ext/1384354487/BOARD.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/BOARD.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/ES_CheckEvents.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/ES_CheckEvents.c  .generated_files/flags/default/2ee3bb07d5ab98bffd03b6e59cfeb3cea58790fd .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1384354487/ES_CheckEvents.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_CheckEvents.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/ES_Framework.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/ES_Framework.c  .generated_files/flags/default/80db391c730c1a6ce44962310823e211ae0cf0f5 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1384354487/ES_Framework.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Framework.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/ES_KeyboardInput.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/ES_KeyboardInput.c  .generated_files/flags/default/9e149b031e913ebffa8818e5307c614ca6a1644b .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1384354487/ES_KeyboardInput.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_KeyboardInput.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/ES_PostList.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/ES_PostList.c  .generated_files/flags/default/2aa032f47ecf48dbafff2c31b895bc8917cc7d7d .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1384354487/ES_PostList.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_PostList.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/ES_Queue.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/ES_Queue.c  .generated_files/flags/default/2800b6ed2843483e33e0e87fe894654a7b705cc1 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1384354487/ES_Queue.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Queue.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/ES_TattleTale.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/ES_TattleTale.c  .generated_files/flags/default/a1280ad6ea440af50e06a736c043d73fa6a0d88a .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1384354487/ES_TattleTale.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_TattleTale.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/ES_Timers.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/ES_Timers.c  .generated_files/flags/default/55125af9751924b7e8b0a9f436997ecd5024b997 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1384354487/ES_Timers.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Timers.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/IO_Ports.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/IO_Ports.c  .generated_files/flags/default/dce3eac7c204f86817d6b496d11efd2ce12a71bd .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1384354487/IO_Ports.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/IO_Ports.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/LED.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/LED.c  .generated_files/flags/default/d8354f02d5cacdf68e1bd4eb2c0640edab3d9b70 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/LED.o.d" -o ${OBJECTDIR}/_ext/1384354487/LED.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/LED.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/pwm.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/pwm.c  .generated_files/flags/default/64b888567ee880bbc9d9c0716e2fe280f5f2d212 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/pwm.o.d" -o ${OBJECTDIR}/_ext/1384354487/pwm.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/pwm.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/RC_Servo.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/RC_Servo.c  .generated_files/flags/default/c9a440ff715f97fb510c5615e20828c35e456e0f .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1384354487/RC_Servo.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/RC_Servo.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/roach.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/roach.c  .generated_files/flags/default/db848c21cf87fb5a56096bb72d32e97331b81eca .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/roach.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/roach.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/roach.o.d" -o ${OBJECTDIR}/_ext/1384354487/roach.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/roach.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/serial.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/serial.c  .generated_files/flags/default/ce1bb39a2c4d0f0e953cce735cf8704743f216db .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/serial.o.d" -o ${OBJECTDIR}/_ext/1384354487/serial.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/serial.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1384354487/timers.o: C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/src/Provided/timers.c  .generated_files/flags/default/e3e336dd69a6307592adfde6caa2410819b0fbf9 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}/_ext/1384354487" 
	@${RM} ${OBJECTDIR}/_ext/1384354487/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1384354487/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../include/Ours" -I"../include/Provided" -MP -MMD -MF "${OBJECTDIR}/_ext/1384354487/timers.o.d" -o ${OBJECTDIR}/_ext/1384354487/timers.o "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/timers.c"    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/ECE_final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/otherfiles/bootloader320.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/ECE_final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=1024,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/ECE_final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC\ 3nd\ quarter\ classes\ y3/ECE\ 118/FinalProject/ece118-final/otherfiles/bootloader320.ld
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
