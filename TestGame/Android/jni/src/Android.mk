LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL
SDL_INCLUDES := $(LOCAL_PATH)/../SDL_ttf $(LOCAL_PATH)/../SDL_image $(LOCAL_PATH)/../SDL_mixer
BOX2D_INCLUDES := $(LOCAL_PATH)/../Box2D/
RUSHENGINE_PATH := ../RushEngine

LOCAL_CFLAGS += -std=c++11
LOCAL_CPPLAGS += -std=c++11

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(LOCAL_PATH)/$(RUSHENGINE_PATH) $(SDL_INCLUDES) $(BOX2D_INCLUDES)

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

 

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	$(SRC_LIST)\
	main.cpp 

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf SDL2_mixer SDL2_image

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
