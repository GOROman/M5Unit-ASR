/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

/*
 * @概要: M5Stack用音声認識(ASR)ユニットのサンプルプログラム
 * @対応ハードウェア: Basic/Fire/Gray(PortA接続) + Unit ASR
 * @必要なライブラリ:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5Unit-ASR: https://github.com/m5stack/M5Unit-ASR
 * 
 * @機能説明:
 * - 音声コマンドの認識と処理
 * - ボタンAで登録済みコマンドの一覧表示
 * - ボタンBで新規コマンドの追加
 * - ボタンCでコマンドの削除
 * 
 * @使用方法:
 * 1. ASRユニットをPortAに接続
 * 2. プログラムを書き込み
 * 3. シリアルモニタで動作確認可能
 */

#include <M5Unified.h>
#include <unit_asr.hpp>
#include "unit_asr_commands.h"  // コマンド番号定義

// ASRユニットのインスタンスを作成
ASRUnit asr;

void setup()
{
    // M5Stackの初期化設定
    auto cfg            = M5.config();
    cfg.serial_baudrate = 115200;  // シリアル通信速度を設定
    M5.begin(cfg);

    // PortAのピン番号を取得
    int8_t port_a_pin1 = -1, port_a_pin2 = -1;
    port_a_pin1 = M5.getPin(m5::pin_name_t::port_a_pin1);  // RXピン
    port_a_pin2 = M5.getPin(m5::pin_name_t::port_a_pin2);  // TXピン
    Serial.printf("getPin: RX:%d TX:%d\n", port_a_pin1, port_a_pin2);

    // ASRユニットの初期化（Serial1を使用、ボーレート115200）
    asr.begin(&Serial1, 115200, port_a_pin1, port_a_pin2);
}

// 音声コマンド"hello"を受信した時のコールバック関数
void myCommandHandler()
{
    Serial.println("hello command received!");  // コマンド受信を通知
}

void loop()
{
    M5.update();  // ボタン状態の更新

    // ASRユニットからの新しいコマンドを確認
    if (asr.update()) {
        // 認識された音声コマンドの情報を表示
        Serial.printf("Command word: %s\n", asr.getCurrentCommandWord());      // コマンドワード
        Serial.printf("Command number: 0x%X\n", asr.getCurrentCommandNum());   // コマンド番号
        Serial.print("Raw message:");                                          // 生データ
        Serial.println(asr.getCurrentRawMessage());
        Serial.printf("Have command handler: %s\n",                           // ハンドラの有無
                     asr.checkCurrentCommandHandler() ? "Yes" : "No");
    }

    // ボタンA: コマンドリストの表示と検索機能のデモ
    if (M5.BtnA.wasPressed()) {
        asr.printCommandList();  // 登録済みコマンドの一覧を表示
        // コマンド番号0x32に対応する単語を検索
        Serial.printf("Search command word: %s\n", asr.searchCommandWord(CMD_HELLO));
        // "hello"コマンドに対応する番号を検索
        Serial.printf("Search command number: %d\n", asr.searchCommandNum("hello"));
    }
    // ボタンB: 新規コマンド"hello"の追加
    else if (M5.BtnB.wasPressed()) {
        // コマンド番号0x32、単語"hello"、ハンドラmyCommandHandlerを登録
        Serial.printf(asr.addCommandWord(CMD_HELLO, "hello", myCommandHandler) ? 
                     "Add Success\n" : "Add Fail\n");
    }
    // ボタンC: コマンド"hello"の削除
    else if (M5.BtnC.wasPressed()) {
        Serial.printf(asr.removeCommandWord("hello") ? 
                     "Remove Success\n" : "Remove Fail\n");
    }
}
