LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := RushEngine


SRC_PHYS := $(wildcard $(LOCAL_PATH)/../RushEngine/Physics/*.cpp)
SRC_PHYS := $(SRC_PHYS:$(LOCAL_PATH)/%=%)

SRC_AU := $(wildcard $(LOCAL_PATH)/../RushEngine/Audio/*.cpp)
SRC_AU := $(SRC_AU:$(LOCAL_PATH)/%=%)

SRC_GR := $(wildcard $(LOCAL_PATH)/../RushEngine/Graphics/*.cpp)
SRC_GR := $(SRC_GR:$(LOCAL_PATH)/%=%)

SRC_EV := $(wildcard $(LOCAL_PATH)/../RushEngine/Eventing/*.cpp)
SRC_EV := $(SRC_EV:$(LOCAL_PATH)/%=%)

SRC_OB := $(wildcard $(LOCAL_PATH)/../RushEngine/Objects/*.cpp)
SRC_OB := $(SRC_OB:$(LOCAL_PATH)/%=%)
 
SRC_LIST := $(SRC_PHYS) $(SRC_AU) $(SRC_GR) $(SRC_EV) $(SRC_OB)
 
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../SDL/include $(LOCAL_PATH)/../SDLImage/ $(LOCAL_PATH)/../SDLttf/ $(LOCAL_PATH)/../SDLmixer/ $(LOCAL_PATH)/../

LOCAL_SRC_FILES := $(SRC_LIST)
LOCAL_STATIC_LIBRARIES := Box2D
LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer SDL2_ttf

include $(BUILD_STATIC_LIBRARY)
