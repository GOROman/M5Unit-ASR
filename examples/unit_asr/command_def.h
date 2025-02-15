/*
 * @概要: ASRユニット用コマンド番号定義
 */

#ifndef _COMMAND_DEF_H_
#define _COMMAND_DEF_H_

// コマンド番号の定義
enum ASR_COMMAND_NUM {
    CMD_HELLO     = 0x32,  // "hello"コマンド
    CMD_START     = 0x33,  // "start"コマンド
    CMD_STOP      = 0x34,  // "stop"コマンド
    CMD_NEXT      = 0x35,  // "next"コマンド
    CMD_PREVIOUS  = 0x36,  // "previous"コマンド
    CMD_UP        = 0x37,  // "up"コマンド
    CMD_DOWN      = 0x38,  // "down"コマンド
    CMD_LEFT      = 0x39,  // "left"コマンド
    CMD_RIGHT     = 0x3A,  // "right"コマンド
    CMD_OK        = 0x3B,  // "ok"コマンド
    CMD_CANCEL    = 0x3C,  // "cancel"コマンド
};

#endif // _COMMAND_DEF_H_
