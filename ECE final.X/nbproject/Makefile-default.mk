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

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED="C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Ours/TemplateES_Main.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Ours/SensorEventChecker.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Ours/BattService.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Ours/SensorService.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/AD.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/BOARD.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_CheckEvents.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Framework.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_KeyboardInput.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_PostList.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Queue.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_TattleTale.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Timers.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/IO_Ports.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/LED.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/pwm.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/RC_Servo.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/roach.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/serial.c" "C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/timers.c"

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/2070106491/TemplateES_Main.o ${OBJECTDIR}/_ext/2070106491/SensorEventChecker.o ${OBJECTDIR}/_ext/2070106491/BattService.o ${OBJECTDIR}/_ext/2070106491/SensorService.o ${OBJECTDIR}/_ext/1384354487/AD.o ${OBJECTDIR}/_ext/1384354487/BOARD.o ${OBJECTDIR}/_ext/1384354487/ES_CheckEvents.o ${OBJECTDIR}/_ext/1384354487/ES_Framework.o ${OBJECTDIR}/_ext/1384354487/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1384354487/ES_PostList.o ${OBJECTDIR}/_ext/1384354487/ES_Queue.o ${OBJECTDIR}/_ext/1384354487/ES_TattleTale.o ${OBJECTDIR}/_ext/1384354487/ES_Timers.o ${OBJECTDIR}/_ext/1384354487/IO_Ports.o ${OBJECTDIR}/_ext/1384354487/LED.o ${OBJECTDIR}/_ext/1384354487/pwm.o ${OBJECTDIR}/_ext/1384354487/RC_Servo.o ${OBJECTDIR}/_ext/1384354487/roach.o ${OBJECTDIR}/_ext/1384354487/serial.o ${OBJECTDIR}/_ext/1384354487/timers.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/2070106491/TemplateES_Main.o.d ${OBJECTDIR}/_ext/2070106491/SensorEventChecker.o.d ${OBJECTDIR}/_ext/2070106491/BattService.o.d ${OBJECTDIR}/_ext/2070106491/SensorService.o.d ${OBJECTDIR}/_ext/1384354487/AD.o.d ${OBJECTDIR}/_ext/1384354487/BOARD.o.d ${OBJECTDIR}/_ext/1384354487/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/1384354487/ES_Framework.o.d ${OBJECTDIR}/_ext/1384354487/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/1384354487/ES_PostList.o.d ${OBJECTDIR}/_ext/1384354487/ES_Queue.o.d ${OBJECTDIR}/_ext/1384354487/ES_TattleTale.o.d ${OBJECTDIR}/_ext/1384354487/ES_Timers.o.d ${OBJECTDIR}/_ext/1384354487/IO_Ports.o.d ${OBJECTDIR}/_ext/1384354487/LED.o.d ${OBJECTDIR}/_ext/1384354487/pwm.o.d ${OBJECTDIR}/_ext/1384354487/RC_Servo.o.d ${OBJECTDIR}/_ext/1384354487/roach.o.d ${OBJECTDIR}/_ext/1384354487/serial.o.d ${OBJECTDIR}/_ext/1384354487/timers.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/2070106491/TemplateES_Main.o ${OBJECTDIR}/_ext/2070106491/SensorEventChecker.o ${OBJECTDIR}/_ext/2070106491/BattService.o ${OBJECTDIR}/_ext/2070106491/SensorService.o ${OBJECTDIR}/_ext/1384354487/AD.o ${OBJECTDIR}/_ext/1384354487/BOARD.o ${OBJECTDIR}/_ext/1384354487/ES_CheckEvents.o ${OBJECTDIR}/_ext/1384354487/ES_Framework.o ${OBJECTDIR}/_ext/1384354487/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1384354487/ES_PostList.o ${OBJECTDIR}/_ext/1384354487/ES_Queue.o ${OBJECTDIR}/_ext/1384354487/ES_TattleTale.o ${OBJECTDIR}/_ext/1384354487/ES_Timers.o ${OBJECTDIR}/_ext/1384354487/IO_Ports.o ${OBJECTDIR}/_ext/1384354487/LED.o ${OBJECTDIR}/_ext/1384354487/pwm.o ${OBJECTDIR}/_ext/1384354487/RC_Servo.o ${OBJECTDIR}/_ext/1384354487/roach.o ${OBJECTDIR}/_ext/1384354487/serial.o ${OBJECTDIR}/_ext/1384354487/timers.o

# Source Files
SOURCEFILES=C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Ours/TemplateES_Main.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Ours/SensorEventChecker.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Ours/BattService.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Ours/SensorService.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/AD.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/BOARD.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_CheckEvents.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Framework.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_KeyboardInput.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_PostList.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Queue.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_TattleTale.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/ES_Timers.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/IO_Ports.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/LED.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/pwm.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/RC_Servo.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/roach.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/serial.c C:/Users/coope/OneDrive/Documents/UCSC/Classes/UCSC 3nd quarter classes y3/ECE 118/FinalProject/ece118-final/src/Provided/timers.c



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

# The following macros may be used in the pre and post step lines
_/_=\\
ShExtension=.bat
Device=PIC32MX320F128H
ProjectDir="C:\Users\coope\OneDrive\Desktop\ece118-final\ECE final.X"
ProjectName=ECE_final
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\ECE_final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="ECE_final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  .pre ${BUILD_SUBPROJECTS}
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
