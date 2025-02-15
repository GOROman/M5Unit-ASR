#ifndef UNIT_ASR_COMMANDS_H
#define UNIT_ASR_COMMANDS_H

// 方向制御（Direction Control）
#define CMD_UP             0x01
#define CMD_DOWN           0x02
#define CMD_LEFT           0x03
#define CMD_TURN_LEFT      0x04
#define CMD_RIGHT          0x05
#define CMD_TURN_RIGHT     0x06
#define CMD_FORWARD        0x07
#define CMD_FRONT          0x08
#define CMD_BACKWARD       0x09
#define CMD_BACK           0x0A

// 操作コマンド（Operation Commands）
#define CMD_OPEN           0x10
#define CMD_CLOSE          0x11
#define CMD_START          0x12
#define CMD_STOP           0x13
#define CMD_TURN_ON        0x14
#define CMD_TURN_OFF       0x15
#define CMD_PLAY           0x16
#define CMD_PAUSE          0x17
#define CMD_TURN_ON_LIGHTS 0x18
#define CMD_TURN_OFF_LIGHTS 0x19
#define CMD_PREVIOUS       0x1A
#define CMD_NEXT           0x1B

// 数字（Numbers）
#define CMD_ZERO           0x20
#define CMD_ONE            0x21
#define CMD_TWO            0x22
#define CMD_THREE          0x23
#define CMD_FOUR           0x24
#define CMD_FIVE           0x25
#define CMD_SIX            0x26
#define CMD_SEVEN          0x27
#define CMD_EIGHT          0x28
#define CMD_NINE           0x29

// 确认与问候（Acknowledgment & Greetings）
#define CMD_OK             0x30
#define CMD_HI_ASR         0x31
#define CMD_HELLO          0x32

// システム制御
#define CMD_INCREASE_VOLUME 0x40
#define CMD_DECREASE_VOLUME 0x41
#define CMD_MAXIMUM_VOLUME 0x42
#define CMD_MEDIUM_VOLUME  0x43
#define CMD_MINIMUM_VOLUME 0x44
#define CMD_CHECK_FIRMWARE_VERSION 0x45

#endif