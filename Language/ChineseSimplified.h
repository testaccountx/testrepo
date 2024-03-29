#define NUM_BUTTONWIDTH           60
#define NUM_LABELWIDTH            50
#define STR_ISRTL                 "0"

// ============================================================================
// Context menus
// ============================================================================

// Rainmeter menu
#define STR_UPDATEAVAILABLE       "有可用更新"
#define STR_MANAGE                "管理"
#define STR_ABOUT                 "关于"
#define STR_HELP                  "帮助"
#define STR_SKINS                 "皮肤"
#define STR_NOSKINS               "无可用的皮肤"
#define STR_OPENFOLDER            "打开皮肤目录"
#define STR_DISABLEDRAGGING       "禁止拖动"
#define STR_THEMES                "主题"
#define STR_NOTHEMES              "无可用的主题"
#define STR_EDITSETTINGS          "编辑设置"
#define STR_REFRESHALL            "刷新全部"
#define STR_LOGGING               "日志记录"
#define STR_SHOWLOGFILE           "查看日志"
#define STR_STARTLOGGING          "开始记录"
#define STR_STOPLOGGING           "停止记录"
#define STR_DELETELOGFILE         "删除日志"
#define STR_DEBUGMODE             "调试模式"
#define STR_EXIT                  "退出"

// Skin menu
#define STR_VARIANTS              "切换"
#define STR_SETTINGS              "设置"
#define STR_POSITION              "位置"
#define STR_DISPLAYMONITOR        "显示器"
#define STR_USEDEFAULTMONITOR     "使用默认: 标准显示器"
#define STR_VIRTUALSCREEN         "@0: 虚拟显示器"
#define STR_AUTOSELECTMONITOR     "根据窗口位置自动选择"
#define STR_STAYTOPMOST           "总在顶层"
#define STR_TOPMOST               "顶层"
#define STR_NORMAL                "正常"
#define STR_BOTTOM                "底层"
#define STR_ONDESKTOP             "桌面"
#define STR_FROMRIGHT             "向右对齐"
#define STR_FROMBOTTOM            "向下对齐"
#define STR_XASPERCENTAGE         "横向比例"
#define STR_YASPERCENTAGE         "纵向比例"
#define STR_TRANSPARENCY          "透明"
#define STR_FADEIN                "淡入"
#define STR_FADEOUT               "淡出"
#define STR_HIDEONMOUSEOVER       "鼠标划入隐藏"
#define STR_DRAGGABLE             "允许拖动"
#define STR_SAVEPOSITION          "保存位置"
#define STR_SNAPTOEDGES           "边缘吸附"
#define STR_CLICKTHROUGH          "点击穿透"
#define STR_KEEPONSCREEN          "钉在桌面"
#define STR_MANAGESKIN            "管理皮肤"
#define STR_EDITSKIN              "编辑皮肤"
#define STR_REFRESHSKIN           "刷新皮肤"
#define STR_UNLOADSKIN            "关闭皮肤"

// ============================================================================
// Dialogs
// ============================================================================

#define STR_CLOSE                 "关闭"

// About dialog
#define STR_ABOUTRAINMETER        "关于 Rainmeter"
#define STR_LOG                   "日志"
#define STR_MEASURES              "监测"
#define STR_VARIABLES             "变量"
#define STR_PLUGINS               "插件"
#define STR_VERSION               "版本"
#define STR_TYPE                  "类型"
#define STR_TIME                  "时间"
#define STR_MESSAGE               "信息"
#define STR_NAME                  "名称"
#define STR_RANGE                 "范围"
#define STR_VALUE                 "数值"
#define STR_AUTHOR                "作者"
#define STR_ERROR                 "错误"
#define STR_WARNING               "警告"
#define STR_NOTICE                "通知"
#define STR_DEBUG                 "调试"
#define STR_GETLATESTVERSION      "获取最新版本 <a href=""http://rainmeter.net"">rainmeter.net</a>."
#define STR_COPYRIGHTNOTICE       "基于 <a href=""http://www.gnu.org/licenses"">GNU GPL v2</a> 许可证发布."
#define STR_COPYTOCLIPBOARD       "复制到剪贴板"

// Manage dialog
#define STR_MANAGERAINMETER       "Rainmeter 管理器"
#define STR_ACTIVESKINS           "已激活的皮肤"
#define STR_EXPAND                "展开"
#define STR_COLLAPSE              "关闭"
#define STR_OPENLOG               "查看日志"
#define STR_LOAD                  "加载"
#define STR_UNLOAD                "卸载"
#define STR_REFRESH               "刷新"
#define STR_EDIT                  "编辑"
#define STR_AUTHORSC              "作者:"
#define STR_VERSIONSC             "版本:"
#define STR_LICENSESC             "许可:"
#define STR_INFORMATIONSC         "信息:"
#define STR_ADDMETADATA           "<a>添加元数据</a>"
#define STR_COORDINATESSC         "坐标:"
#define STR_POSITIONSC            "位置:"
#define STR_LOADORDERSC           "加载顺序:"
#define STR_TRANSPARENCYSC        "透明:"
#define STR_ONHOVERSC             "悬停:"
#define STR_DONOTHING             "无动作"
#define STR_HIDE                  "隐藏"
#define STR_SAVENEWTHEME          "保存新主题"
#define STR_THEMEDESCRIPTION      "你可以将当前的Rainmeter皮肤布局保存为一个主题并在需要的时候恢复它。恢复Rainmeter主题时只会恢复皮肤的布局，不会修改或更新您的皮肤。"
#define STR_SAVEASEMPTYTHEME      "保存为空主题"
#define STR_EXCLUDEUNUSEDSKINS    "排除未使用的皮肤"
#define STR_INCLUDEWALLPAPER      "包含当前壁纸"
#define STR_NAMESC                "主题名称:"
#define STR_SAVE                  "保存"
#define STR_SAVEDTHEMES           "已存在的主题"
#define STR_DELETE                "删除"
#define STR_BACKUP                "备份"
#define STR_BACKUPDESCRIPTION     "您可以把当前的皮肤，主题，插件以及统计数据进行备份并在必要的时候恢复它们。和主题有所不同，恢复备份会覆盖您当前所使用的皮肤和设置。"
#define STR_BACKUPE               "备份..."
#define STR_LANGUAGESC            "Language:"
#define STR_GENERAL               "常规"
#define STR_CHECKFORUPDATES       "检查更新"
#define STR_RESETSTATISTICS       "重置统计数据"
#define STR_LOGTOFILE             "日志文件"

// ============================================================================
// Messages
// ============================================================================

#define STR_SETTINGSNOTWRITABLE   "Rainmeter.ini文件不可写。设置将不会被保存。"
#define STR_SETTINGSMOVEFILE      "退出Rainmeter并移动设置文件：\n%1\n\n到：\n%2\n\n或者删除该文件（设置都将丢失），它会自动在下次启动时重新创建。"
#define STR_SETTINGSREADONLY      "请确保该文件未设置为只读并文件夹是可写的。该文件位于：\n%1"
#define STR_THEMEALREADYEXISTS    "这个主题 ""%1"" 已经存在。\n\n你确定要替换它吗？"
#define STR_THEMESAVEFAIL         "无法保存主题：\n%1"
#define STR_THEMEDELETE           "你确定要删除主题 ""%1""？"
#define STR_LOGFILECREATEFAIL     "无法创建日志文件:\n%1"
#define STR_LOGFILEDELETE         "你确定要删除日志文件吗？\n%1"
#define STR_NOAVAILABLESKINS      "没有可用的皮肤：\n%1"
#define STR_UNABLETOACTIVATESKIN  "无法激活皮肤 ""%1\\%2""：文件未找到。"
#define STR_UNABLETOREFRESHSKIN   "无法刷新皮肤 ""%1\\%2""：文件未找到。"
#define STR_NEWVERSIONREQUIRED    "这个皮肤 ""%1\\%2"" 需要Rainmeter %3 或更高版本，从rainmeter.net下载最新版本。"
#define STR_NOMETERSINSKIN        "这个皮肤 ""%1\\%2"" 不包含任何meters，将被停用。\n\n该文件可能已损坏或它可能不是一个有效的皮肤。"
#define STR_INCLUDEINFINITELOOP   "你用@include创建了一个无限循环，请检查你的皮肤。"

// ============================================================================
// Log strings
// ============================================================================

/* Not implemented yet */
