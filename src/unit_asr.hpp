/*
 *SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 *SPDX-License-Identifier: MIT
 */

#ifndef ASRUNIT_H
#define ASRUNIT_H

#include <Arduino.h>
#include <map>
#include <functional>
#include "driver/uart.h"

#define UNIT_ASR_BAUD 115200

// #define UNIT_ASR_DEBUG

class ASRUnit {
public:
    typedef std::function<void()> CommandHandler;

    /**
     * @brief ASRユニットのシリアル通信パラメータを初期化します。
     *
     * この関数は、指定されたハードウェアシリアルポートを設定し、
     * 指定されたボーレートとピン割り当てでASRユニットのシリアル通信を設定します。
     *
     * @param serial HardwareSerialオブジェクトへのポインタ、デフォルトはSerial1
     * @param baud シリアル通信のボーレート、デフォルトは115200
     * @param RX データ受信用のGPIOピン番号、デフォルトは16
     * @param TX データ送信用のGPIOピン番号、デフォルトは17
     */
    void begin(HardwareSerial *serial = &Serial1, int baud = UNIT_ASR_BAUD, uint8_t RX = 16, uint8_t TX = 17);

    /**
     * @brief ASRユニットにコマンド番号を送信します。
     *
     * 設定されたシリアル接続を通じて、指定されたコマンド番号を
     * ASRユニットに送信します。
     *
     * @param commandNum ASRユニットに送信するコマンド番号
     */
    void sendComandNum(uint8_t commandNum);

    /**
     * @brief ASRユニットから現在の生メッセージを取得します。
     *
     * @return ASRユニットから受信した生メッセージ文字列
     */
    String getCurrentRawMessage();

    /**
     * @brief 現在認識されているコマンドワードを取得します。
     *
     * @return 現在のコマンドワードの文字列表現
     */
    String getCurrentCommandWord();

    /**
     * @brief 現在のコマンド番号を取得します。
     *
     * @return 現在のコマンドの数値識別子
     */
    uint8_t getCurrentCommandNum();

    /**
     * @brief 現在のコマンドのハンドラーを確認して実行します。
     *
     * 現在のコマンドに関連付けられたハンドラー関数が存在する場合、
     * その実行を試みます。
     *
     * @return ハンドラーが存在し正常に実行された場合はtrue、それ以外はfalse
     */
    bool checkCurrentCommandHandler();

    /**
     * @brief 新しいコマンドワードとそれに関連するハンドラーをコマンドリストに追加します。
     *
     * この関数は、新しい音声コマンドをそれに対応するコマンド番号と
     * オプションのハンドラー関数とともに登録します。
     *
     * @param commandNum コマンドの数値識別子
     * @param commandWord 認識する音声コマンドワードまたはフレーズ
     * @param handler コマンドが認識された時に実行するオプションのコールバック関数
     * @return コマンドが正常に追加された場合はtrue、それ以外はfalse
     */
    bool addCommandWord(uint8_t commandNum, const String &commandWord, CommandHandler handler = nullptr);

    /**
     * @brief コマンドリストからコマンドワードを削除します。
     *
     * @param commandWord 認識リストから削除するコマンドワード
     * @return コマンドが正常に削除された場合はtrue、それ以外はfalse
     */
    bool removeCommandWord(const String &commandWord);

    /**
     * @brief コマンドワードに関連付けられたコマンド番号を検索します。
     *
     * @param commandWord 検索するコマンドワード
     * @return 関連付けられたコマンド番号が見つかった場合はその番号、見つからない場合は-1
     */
    int8_t searchCommandNum(const String &commandWord);

    /**
     * @brief コマンド番号に関連付けられたコマンドワードを検索します。
     *
     * @param commandNum 検索するコマンド番号
     * @return 関連付けられたコマンドワードが見つかった場合はそのワード、見つからない場合は空文字列
     */
    String searchCommandWord(uint8_t commandNum);

    /**
     * @brief 保留中のティックコールバックを処理します。
     *
     * ASRユニットのスケジュールされたティックベースの操作を確認して実行します。
     */
    void checkTickCallback();

    /**
     * @brief ASRユニットの状態を更新し、新しいコマンドを処理します。
     *
     * この関数は、新しい音声コマンドを処理し、ユニットの状態を更新するために
     * メインループで定期的に呼び出す必要があります。
     *
     * @return 新しいコマンドが処理された場合はtrue、それ以外はfalse
     */
    bool update();

    /**
     * @brief 登録されているコマンドワードの完全なリストを出力します。
     *
     * デバッグ目的で、登録されているすべてのコマンドワードと
     * それに関連付けられたコマンド番号をシリアルモニタに出力します。
     */
    void printCommandList();

private:
    HardwareSerial *_serial;
    String rawMessage;
    uint8_t commandNum;
    std::map<uint8_t, std::pair<String, CommandHandler>> commandList = {
        {0x00, {"Unknown command word", nullptr}},
        {0x01, {"up", nullptr}},
        {0x02, {"down", nullptr}},
        {0x03, {"left", nullptr}},
        {0x04, {"turn left", nullptr}},
        {0x05, {"right", nullptr}},
        {0x06, {"turn right", nullptr}},
        {0x07, {"forward", nullptr}},
        {0x08, {"front", nullptr}},
        {0x09, {"backward", nullptr}},
        {0x0A, {"back", nullptr}},
        {0x10, {"open", nullptr}},
        {0x11, {"close", nullptr}},
        {0x12, {"start", nullptr}},
        {0x13, {"stop", nullptr}},
        {0x14, {"turn on", nullptr}},
        {0x15, {"turn off", nullptr}},
        {0x16, {"play", nullptr}},
        {0x17, {"pause", nullptr}},
        {0x18, {"turn on the lights", nullptr}},
        {0x19, {"turn off the lights", nullptr}},
        {0x1A, {"previous", nullptr}},
        {0x1B, {"next", nullptr}},
        {0x20, {"zero", nullptr}},
        {0x21, {"one", nullptr}},
        {0x22, {"two", nullptr}},
        {0x23, {"three", nullptr}},
        {0x24, {"four", nullptr}},
        {0x25, {"five", nullptr}},
        {0x26, {"six", nullptr}},
        {0x27, {"seven", nullptr}},
        {0x28, {"eight", nullptr}},
        {0x29, {"nine", nullptr}},
        {0x30, {"ok", nullptr}},
        {0x31, {"hi, A S R", nullptr}},
        {0x32, {"hello", nullptr}},
        {0x40, {"increase volume", nullptr}},
        {0x41, {"decrease volume", nullptr}},
        {0x42, {"maximum volume", nullptr}},
        {0x43, {"medium volume", nullptr}},
        {0x44, {"minimum volume", nullptr}},
        {0x45, {"check firmware version", nullptr}},
        {0xFE, {"Announce", nullptr}},
        {0xFF, {"Hi,M Five", nullptr}},
    };
};

#endif  // ASRUNIT_H
