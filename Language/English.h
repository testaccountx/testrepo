#define NUM_BUTTONWIDTH           60
#define NUM_LABELWIDTH            65
#define STR_ISRTL                 "0"

// ============================================================================
// Context menus
// ============================================================================

// Rainmeter menu
#define STR_UPDATEAVAILABLE       "Update available"
#define STR_MANAGE                "Manage"
#define STR_ABOUT                 "About"
#define STR_HELP                  "Help"
#define STR_SKINS                 "Skins"
#define STR_NOSKINS               "No skins available"
#define STR_OPENFOLDER            "Open folder"
#define STR_DISABLEDRAGGING       "Disable dragging"
#define STR_THEMES                "Themes"
#define STR_NOTHEMES              "No themes available"
#define STR_EDITSETTINGS          "Edit settings"
#define STR_REFRESHALL            "Refresh all"
#define STR_LOGGING               "Logging"
#define STR_SHOWLOGFILE           "Show log file"
#define STR_STARTLOGGING          "Start logging"
#define STR_STOPLOGGING           "Stop logging"
#define STR_DELETELOGFILE         "Delete log file"
#define STR_DEBUGMODE             "Debug mode"
#define STR_EXIT                  "Exit"

// Skin menu
#define STR_VARIANTS              "Variants"
#define STR_SETTINGS              "Settings"
#define STR_POSITION              "Position"
#define STR_DISPLAYMONITOR        "Display monitor"
#define STR_USEDEFAULTMONITOR     "Use default: Primary monitor"
#define STR_VIRTUALSCREEN         "@0: Virtual screen"
#define STR_AUTOSELECTMONITOR     "Auto-select based on window position"
#define STR_STAYTOPMOST           "Stay topmost"
#define STR_TOPMOST               "Topmost"
#define STR_NORMAL                "Normal"
#define STR_BOTTOM                "Bottom"
#define STR_ONDESKTOP             "On desktop"
#define STR_FROMRIGHT             "From right"
#define STR_FROMBOTTOM            "From bottom"
#define STR_XASPERCENTAGE         "X as percentage"
#define STR_YASPERCENTAGE         "Y as percentage"
#define STR_TRANSPARENCY          "Transparency"
#define STR_FADEIN                "Fade in"
#define STR_FADEOUT               "Fade out"
#define STR_HIDEONMOUSEOVER       "Hide on mouse over"
#define STR_DRAGGABLE             "Draggable"
#define STR_SAVEPOSITION          "Save position"
#define STR_SNAPTOEDGES           "Snap to edges"
#define STR_CLICKTHROUGH          "Click through"
#define STR_KEEPONSCREEN          "Keep on screen"
#define STR_MANAGESKIN            "Manage skin"
#define STR_EDITSKIN              "Edit skin"
#define STR_REFRESHSKIN           "Refresh skin"
#define STR_UNLOADSKIN            "Unload skin"

// ============================================================================
// Dialogs
// ============================================================================

#define STR_CLOSE                 "Close"

// About dialog
#define STR_ABOUTRAINMETER        "About Rainmeter"
#define STR_LOG                   "Log"
#define STR_MEASURES              "Measures"
#define STR_VARIABLES             "Variables"
#define STR_PLUGINS               "Plugins"
#define STR_VERSION               "Version"
#define STR_TYPE                  "Type"
#define STR_TIME                  "Time"
#define STR_MESSAGE               "Message"
#define STR_NAME                  "Name"
#define STR_RANGE                 "Range"
#define STR_VALUE                 "Value"
#define STR_AUTHOR                "Author"
#define STR_ERROR                 "Error"
#define STR_WARNING               "Warning"
#define STR_NOTICE                "Notice"
#define STR_DEBUG                 "Debug"
#define STR_GETLATESTVERSION      "Get the latest version at <a href=""http://rainmeter.net"">rainmeter.net</a>."
#define STR_COPYRIGHTNOTICE       "Distributed under the <a href=""http://www.gnu.org/licenses"">GNU GPL v2</a> license."
#define STR_COPYTOCLIPBOARD       "Copy to clipboard"

// Manage dialog
#define STR_MANAGERAINMETER       "Manage Rainmeter"
#define STR_ACTIVESKINS           "Active skins"
#define STR_EXPAND                "Expand"
#define STR_COLLAPSE              "Collapse"
#define STR_OPENLOG               "Open log"
#define STR_LOAD                  "Load"
#define STR_UNLOAD                "Unload"
#define STR_REFRESH               "Refresh"
#define STR_EDIT                  "Edit"
#define STR_AUTHORSC              "Author:"
#define STR_VERSIONSC             "Version:"
#define STR_LICENSESC             "License:"
#define STR_INFORMATIONSC         "Information:"
#define STR_ADDMETADATA           "<a>Add metadata</a>"
#define STR_COORDINATESSC         "Coordinates:"
#define STR_POSITIONSC            "Position:"
#define STR_LOADORDERSC           "Load order:"
#define STR_TRANSPARENCYSC        "Transparency:"
#define STR_ONHOVERSC             "On hover:"
#define STR_DONOTHING             "Do nothing"
#define STR_HIDE                  "Hide"
#define STR_SAVENEWTHEME          "Save new theme"
#define STR_THEMEDESCRIPTION      "A theme allows you to save the current layout of your Rainmeter skins and restore it at a later time. Restoring a theme will restore the layout, but will not undo edits or updates to your skins."
#define STR_SAVEASEMPTYTHEME      "Save as empty theme"
#define STR_EXCLUDEUNUSEDSKINS    "Exclude unused skins"
#define STR_INCLUDEWALLPAPER      "Include current wallpaper"
#define STR_NAMESC                "Name:"
#define STR_SAVE                  "Save"
#define STR_SAVEDTHEMES           "Saved themes"
#define STR_DELETE                "Delete"
#define STR_BACKUP                "Backup"
#define STR_BACKUPDESCRIPTION     "A backup allows you to save a complete copy of your setup, including skins and statistics. Unlike a theme, restoring a backup will replace all edits and updates to your skins since the backup was saved."
#define STR_BACKUPE               "Backup..."
#define STR_LANGUAGESC            "Language:"
#define STR_GENERAL               "General"
#define STR_CHECKFORUPDATES       "Check for updates"
#define STR_RESETSTATISTICS       "Reset statistics"
#define STR_LOGTOFILE             "Log to file"

// ============================================================================
// Messages
// ============================================================================

#define STR_SETTINGSNOTWRITABLE   "Rainmeter.ini is not writable. Settings will not be saved."
#define STR_SETTINGSMOVEFILE      "Quit Rainmeter and move the settings file from:\n%1\n\nto:\n%2\n\nAlternatively, simply remove the file (settings will be lost) and it will be automatically recreated on next launch."
#define STR_SETTINGSREADONLY      "Make sure that the file is not set as read-only and that the folder is writable. The file is located at:\n%1"
#define STR_THEMEALREADYEXISTS    "The theme ""%1"" already exists.\n\nDo you want to replace it?"
#define STR_THEMESAVEFAIL         "Unable to save theme:\n%1"
#define STR_THEMEDELETE           "Are you sure you want to delete the theme ""%1""?"
#define STR_LOGFILECREATEFAIL     "Unable to create log file:\n%1"
#define STR_LOGFILEDELETE         "Are you sure you delete the log file?\n%1"
#define STR_NOAVAILABLESKINS      "There are no available skins at:\n%1"
#define STR_UNABLETOACTIVATESKIN  "Unable to activate skin ""%1\\%2"": File not found."
#define STR_UNABLETOREFRESHSKIN   "Unable to refresh skin ""%1\\%2"": File not found."
#define STR_NEWVERSIONREQUIRED    "The skin ""%1\\%2"" requires Rainmeter %3 or higher. Download the latest version from rainmeter.net."
#define STR_NOMETERSINSKIN        "The skin ""%1\\%2"" does not contain any meters and will be deactivated.\n\nThe file may be damaged or it may not be a valid skin."
#define STR_INCLUDEINFINITELOOP   "You have created an infinite loop with @include. Please check your skin."

// ============================================================================
// Log strings
// ============================================================================

/* Not implemented yet */
