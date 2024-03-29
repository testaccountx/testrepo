#define NUM_BUTTONWIDTH           80
#define NUM_LABELWIDTH            65
#define STR_ISRTL                 "0"

// ============================================================================
// Context menus
// ============================================================================

// Rainmeter menu
#define STR_UPDATEAVAILABLE       "新しいバージョンが利用可能です"
#define STR_MANAGE                "管理ツール"
#define STR_ABOUT                 "詳細"
#define STR_HELP                  "ヘルプ"
#define STR_SKINS                 "スキン"
#define STR_NOSKINS               "利用可能なスキンが見つかりません"
#define STR_OPENFOLDER            "フォルダーを開く"
#define STR_DISABLEDRAGGING       "ドラッグを無効化"
#define STR_THEMES                "テーマ"
#define STR_NOTHEMES              "利用可能なテーマが見つかりません"
#define STR_EDITSETTINGS          "設定を編集"
#define STR_REFRESHALL            "すべて再読み込み"
#define STR_LOGGING               "ログ"
#define STR_SHOWLOGFILE           "ログファイルを表示"
#define STR_STARTLOGGING          "ログを開始"
#define STR_STOPLOGGING           "ログを停止"
#define STR_DELETELOGFILE         "ログを削除"
#define STR_DEBUGMODE             "デバッグモード"
#define STR_EXIT                  "終了"

// Skin menu
#define STR_VARIANTS              "スキンの切り替え"
#define STR_SETTINGS              "設定"
#define STR_POSITION              "位置"
#define STR_DISPLAYMONITOR        "表示するモニター"
#define STR_USEDEFAULTMONITOR     "既定の設定: プライマリモニター"
#define STR_VIRTUALSCREEN         "@0: 仮想スクリーン"
#define STR_AUTOSELECTMONITOR     "スキンの位置に応じて自動選択"
#define STR_STAYTOPMOST           "最前面に固定"
#define STR_TOPMOST               "前面へ"
#define STR_NORMAL                "通常"
#define STR_BOTTOM                "背面へ"
#define STR_ONDESKTOP             "デスクトップに固定"
#define STR_FROMRIGHT             "右端を基準にする"
#define STR_FROMBOTTOM            "下端を基準にする"
#define STR_XASPERCENTAGE         "X軸のパーセントで指定"
#define STR_YASPERCENTAGE         "Y軸のパーセントで指定"
#define STR_TRANSPARENCY          "透過率"
#define STR_FADEIN                "フェードイン"
#define STR_FADEOUT               "フェードアウト"
#define STR_HIDEONMOUSEOVER       "マウスオーバーで非表示"
#define STR_DRAGGABLE             "ドラッグを許可"
#define STR_SAVEPOSITION          "位置を記憶"
#define STR_SNAPTOEDGES           "端に合わせる"
#define STR_CLICKTHROUGH          "クリックをスルー"
#define STR_KEEPONSCREEN          "すべてを画面上に表示"
#define STR_MANAGESKIN            "スキンを管理"
#define STR_EDITSKIN              "スキンを編集"
#define STR_REFRESHSKIN           "スキンを再読み込み"
#define STR_UNLOADSKIN            "スキンを閉じる"

// ============================================================================
// Dialogs
// ============================================================================

#define STR_CLOSE                 "閉じる"

// About dialog
#define STR_ABOUTRAINMETER        "Rainmeterについて"
#define STR_LOG                   "ログ"
#define STR_MEASURES              "メジャー"
#define STR_VARIABLES             "変数"
#define STR_PLUGINS               "プラグイン"
#define STR_VERSION               "バージョン"
#define STR_TYPE                  "項目"
#define STR_TIME                  "時刻"
#define STR_MESSAGE               "メッセージ"
#define STR_NAME                  "名前"
#define STR_RANGE                 "範囲"
#define STR_VALUE                 "値"
#define STR_AUTHOR                "作者"
#define STR_ERROR                 "エラー"
#define STR_WARNING               "警告"
#define STR_NOTICE                "通知"
#define STR_DEBUG                 "デバッグ"
#define STR_GETLATESTVERSION      "最新版は<a href=""http://rainmeter.net"">rainmeter.net</a>から入手可能です。"
#define STR_COPYRIGHTNOTICE       "このアプリケーションは<a href=""http://www.gnu.org/licenses"">GNU GPL v2</a>に基づいて配布されています。"
#define STR_COPYTOCLIPBOARD       "クリップボードにコピー"

// Manage dialog
#define STR_MANAGERAINMETER       "Rainmeterの管理"
#define STR_ACTIVESKINS           "利用中のスキン"
#define STR_EXPAND                "展開"
#define STR_COLLAPSE              "折りたたみ"
#define STR_OPENLOG               "ログを開く"
#define STR_LOAD                  "読み込む"
#define STR_UNLOAD                "閉じる"
#define STR_REFRESH               "再読み込み"
#define STR_EDIT                  "編集"
#define STR_AUTHORSC              "作者:"
#define STR_VERSIONSC             "バージョン:"
#define STR_LICENSESC             "ライセンス:"
#define STR_INFORMATIONSC         "説明:"
#define STR_ADDMETADATA           "<a>メタデータを追加</a>"
#define STR_COORDINATESSC         "表示座標:"
#define STR_POSITIONSC            "表示位置:"
#define STR_LOADORDERSC           "読み込む順序:"
#define STR_TRANSPARENCYSC        "透過率:"
#define STR_ONHOVERSC             "ホバー時:"
#define STR_DONOTHING             "何もしない"
#define STR_HIDE                  "隠す"
#define STR_SAVENEWTHEME          "新しくテーマを保存"
#define STR_THEMEDESCRIPTION      "現在のスキンのレイアウトを保存、復元することができます。テーマからレイアウトを復元してもスキンの更新や編集内容は元に戻りません。"
#define STR_SAVEASEMPTYTHEME      "空のテーマとして保存"
#define STR_EXCLUDEUNUSEDSKINS    "使用していないスキンを取り除く"
#define STR_INCLUDEWALLPAPER      "現在の壁紙を保存"
#define STR_NAMESC                "名前:"
#define STR_SAVE                  "保存"
#define STR_SAVEDTHEMES           "保存されたテーマ"
#define STR_DELETE                "削除"
#define STR_BACKUP                "バックアップ"
#define STR_BACKUPDESCRIPTION     "スキン、テーマ、プラグイン、アドオンの状態を保存、復元することができます。テーマとは異なり、復元時にはスキンの更新や編集内容がバックアップ時の状態に置き換えられます。"
#define STR_BACKUPE               "バックアップ..."
#define STR_LANGUAGESC            "言語 (Language):"
#define STR_GENERAL               "共通の設定"
#define STR_CHECKFORUPDATES       "アップデートを自動的に確認"
#define STR_RESETSTATISTICS       "統計をリセットする"
#define STR_LOGTOFILE             "ログをファイルに保存"

// ============================================================================
// Messages
// ============================================================================

#define STR_SETTINGSNOTWRITABLE   "Rainmeter.iniへの書き込みに失敗しました。設定を保存することができません。"
#define STR_SETTINGSMOVEFILE      "Rainmeterを終了し、設定ファイルを\n%1\nから\n%2\nへ移動してください。\n\nファイルを削除した場合には次回の起動時に正しい場所に生成されますが、現在の設定はすべて失われます。"
#define STR_SETTINGSREADONLY      "設定ファイルおよび保存フォルダーへの書き込みを有効にしてください。\n%1"
#define STR_THEMEALREADYEXISTS    "テーマ「%1」は既に存在しています。\n\n上書きしてもよろしいですか?"
#define STR_THEMESAVEFAIL         "テーマの保存に失敗しました。\n%1"
#define STR_THEMEDELETE           "テーマ「%1」を削除してもよろしいですか?"
#define STR_LOGFILECREATEFAIL     "ログファイルの生成に失敗しました。\n%1"
#define STR_LOGFILEDELETE         "ログファイルを削除してもよろしいですか?\n%1"
#define STR_NOAVAILABLESKINS      "利用可能なスキンが存在しません。\n%1"
#define STR_UNABLETOACTIVATESKIN  "スキン「%1\\%2」の有効化に失敗しました。ファイルが見つかりません。"
#define STR_UNABLETOREFRESHSKIN   "スキン「%1\\%2」の再読み込みに失敗しました。ファイルが見つかりません。"
#define STR_NEWVERSIONREQUIRED    "スキン「%1\\%2」を利用するにはRainmeter %3以降が必要です。rainmeter.netより最新版をダウンロードしてください。"
#define STR_NOMETERSINSKIN        "スキン「%1\\%2」はメーターを一つも含んでいないため利用できません。\n\nファイルが破損しているかスキンの記述に誤りがある可能性があります。"
#define STR_INCLUDEINFINITELOOP   "[@include]に無限ループが存在しています。スキンの記述を確認してください。"

// ============================================================================
// Log strings
// ============================================================================

/* Not implemented yet */
