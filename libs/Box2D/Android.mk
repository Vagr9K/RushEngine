LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Box2D


SRC_COL := $(wildcard $(LOCAL_PATH)/Collision/*.cpp)
SRC_SHAPE := $(wildcard $(LOCAL_PATH)/Collision/Shapes/*.cpp)
SRC_COL := $(SRC_COL:$(LOCAL_PATH)/%=%)
SRC_SHAPE := $(SRC_SHAPE:$(LOCAL_PATH)/%=%)

SRC_COM := $(wildcard $(LOCAL_PATH)/Common/*.cpp)
SRC_COM := $(SRC_COM:$(LOCAL_PATH)/%=%)

SRC_DYN := $(wildcard $(LOCAL_PATH)/Dynamics/*.cpp)
SRC_JOINT := $(wildcard $(LOCAL_PATH)/Dynamics/Joints/*.cpp)
SRC_CONT :=$(wildcard $(LOCAL_PATH)/Dynamics/Contacts/*.cpp)
SRC_DYN := $(SRC_DYN:$(LOCAL_PATH)/%=%)
SRC_JOINT := $(SRC_JOINT:$(LOCAL_PATH)/%=%)
SRC_CONT := $(SRC_CONT:$(LOCAL_PATH)/%=%)

SRC_ROPE := $(wildcard $(LOCAL_PATH)/../Rope/*.cpp)
SRC_ROPE := $(SRC_ROPE:$(LOCAL_PATH)/%=%)

SRC_LIST := $(SRC_COL) $(SRC_SHAPE) $(SRC_COM) $(SRC_DYN) $(SRC_JOINT) $(SRC_CONT) $(SRC_ROPE)
 
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../
LOCAL_SRC_FILES := $(SRC_LIST)

include $(BUILD_STATIC_LIBRARY)
